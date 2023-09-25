#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include <avl.h>

#include "include_linux_list.h"

#include "project.h"
#include "tgt_memory.h"
#include "bitfield.h"
#include "ibitfields.h"

#include "instr.h"
#include "symbol_table.h"
#include "address_list.h"

extern avl_tree_t address_table;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// instruction set definitions
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "mcs-96.h"
#include "i8061.h"
#include "i8065.h"

#define INSTRUCTION_DEF(opcode, mnemonic, bitfields, flags) { mnemonic, bitfields, flags }
//
// invalid instruction definition
//
struct instr_def const mcs_96_invalid_instr_def = MCS_96_INVALID_INSTRUCTION;
struct instr_def const i8061_invalid_instr_def = I8061_INVALID_INSTRUCTION;
struct instr_def const i8065_invalid_instr_def = I8065_INVALID_INSTRUCTION;

//
// prefixed instruction definitions (index: opcode / 16 - 4)
//
struct instr_def const mcs_96_prefixed_instr_set_def[] =
{
    MCS_96_PREFIXED_INSTRUCTION_SET
};
struct instr_def const i8061_prefixed_instr_set_def[] =
{
    I8061_PREFIXED_INSTRUCTION_SET
};
struct instr_def const i8065_prefixed_instr_set_def[] =
{
    I8065_PREFIXED_INSTRUCTION_SET
};

//
// basic instruction definitions
//
struct instr_def const mcs_96_instr_set_def[] =
{
    MCS_96_INSTRUCTION_SET
};

struct instr_def const i8061_instr_set_def[] =
{
    I8061_INSTRUCTION_SET
};

struct instr_def const i8065_instr_set_def[] =
{
    I8065_INSTRUCTION_SET
};
#undef INSTRUCTION_DEF

// default to the mcs-96 instruction set
struct instr_def const * invalid_instr_def;
struct instr_def const * prefixed_instr_set_def;
struct instr_def const * instr_set_def;

void set_instruction_set(enum instruction_set isa)
{
    switch (isa)
    {
    case ISA_MCS96:
        invalid_instr_def = &mcs_96_invalid_instr_def;
        prefixed_instr_set_def = mcs_96_prefixed_instr_set_def;
        instr_set_def = mcs_96_instr_set_def;
        break;
    case ISA_I8061:
        invalid_instr_def = &i8061_invalid_instr_def;
        prefixed_instr_set_def = i8061_prefixed_instr_set_def;
        instr_set_def = i8061_instr_set_def;
        break;
    case ISA_I8065:
        invalid_instr_def = &i8065_invalid_instr_def;
        prefixed_instr_set_def = i8065_prefixed_instr_set_def;
        instr_set_def = i8065_instr_set_def;
        break;
    default:
        printf("\n\nFATAL ERROR: invalid instruction set selected\n");
        exit(1);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// disassembled instructions
//
////////////////////////////////////////////////////////////////////////////////////////////////////

static inline struct instr_entry * alloc_instr_entry(void)
{
    struct instr_entry * entry;

    entry = (struct instr_entry *) calloc(1, sizeof(struct instr_entry));
    if (entry == NULL)
    {
        printf("\n\nFATAL ERROR: failed to allocate instr_entry object\n");
        exit(1);
    }

    return entry;
}


struct instr_entry * instr_entry_create(uint32_t const address)
{
    struct address_table_entry * address_entry;

    address_entry = address_table_create_code(address, NULL);

    if (!address_entry->instr)
    {
        address_entry->instr = alloc_instr_entry();
        address_entry->instr->address = address_entry;
    }

    return address_entry->instr;
}


struct instr_entry * find_instr(uint32_t address)
{
    struct address_table_entry * address_entry;
    struct instr_entry * instr;

    address_entry = find_address(address);
    instr = NULL;

    if (address_entry) instr = address_entry->instr;

    return instr;
}


void instr_list_print(void)
{
    struct address_table_entry * address_entry;

    uint_t idx;

    for (idx = 0;; idx++)
    {
        avl_node_t * avl_node;

        avl_node = avl_at(&address_table, idx);

        if (avl_node == NULL) break;

        address_entry = container_of(avl_node->item, struct address_table_entry, address);

        if (!address_entry->instr) continue;

        printf("%08x\n", address_entry->address);
    }
}


void get_instr_bitfields(struct instr_entry * const instr,
                         struct instr_bitfield_def const * bitfield_def,
                         uint_t * const offset)
{
    for (; bitfield_def->width != 0; bitfield_def++)
    {
        uint32_t bitfield;
        uint8_t width;
        uint8_t type;

        width = bitfield_def->width;
        type = bitfield_def->type;

        // extract bitfield from memory
        bitfield = get_bitfield(tgt_address(instr->address->address), *offset, width);

        // all 16-bit bitfields little-endian and need to be byte swapped
        if (width == 16) bitfield = swap16(bitfield);

        switch (type)
        {
        case IBF_SHIFT:
            if (bitfield >= 16) type++;
            break;

        case IBF_INDEXED:
        case IBF_AUTO_INCREMENT:
            type += bitfield;
            break;

        case IBF_IMMEDIATE:
            // sign extend immediate values
            bitfield = ((int32_t) bitfield << (32 - width)) >> (32 - width);

            // test for register zero based indexed addressing
            if (instr->zero) instr->target_address = bitfield;
            break;

        case IBF_DISPLACEMENT:
            // sign extend address displacements
            bitfield = ((int32_t) bitfield << (32 - width)) >> (32 - width);
            instr->target_address = bitfield;
            break;

        case IBF_OPCODE:
        case IBF_DST_BYTE_REGISTER:
        case IBF_DST_WORD_REGISTER:
        case IBF_DST_LONG_REGISTER:
            // left-justify in byte
            bitfield <<= 8 - width;
            break;

        case IBF_ADDRESS_REGISTER:
            // left-justify in byte
            bitfield <<= 8 - width;

            // test for register zero based indexed addressing
            if (bitfield == 0)
            {
                type = 'Z';
                instr->zero = 1;
            }
            break;
        }

        // check for access of unaligned word register
        if ((type == 'W') && (bitfield & 0x1))
        {
            instr->invalid = 1;
        }

        // check for access of unaligned long register
        if ((type == 'L') && (bitfield & 0x3))
        {
            instr->invalid = 1;
        }

        if (!isalpha(type))
        {
            printf("\n\nFATAL ERROR: bad type\n");
            exit(1);
        }

        if (instr->bitfield_count >= MAX_INSTR_FIELDS)
        {
            printf("\n\nFATAL ERROR: format identifier too long\n");
            exit(1);
        }

        instr->format_identifier[instr->bitfield_count] = type;
        instr->bitfield[instr->bitfield_count] = bitfield;
        instr->bitfield_count++;

        *offset += width;

        // handle recursive cases
        switch (type)
        {
        case IBF_BYTE_AOP:
            // byte addressing mode
            switch (bitfield)
            {
            case 0:
                // direct
                get_instr_bitfields(instr, flds_direct_byte, offset);
                break;

            case 1:
                // immediate
                get_instr_bitfields(instr, flds_immediate_byte, offset);
                break;

            case 2:
                // indirect
                get_instr_bitfields(instr, flds_indirect, offset);
                instr->byte = 1;
                break;

            case 3:
                // indexed
                get_instr_bitfields(instr, flds_indexed, offset);
                instr->byte = 1;
                break;
            }
            break;

        case IBF_WORD_AOP:
            // word addressing mode
            switch (bitfield)
            {
            case 0:
                // direct
                get_instr_bitfields(instr, flds_direct_word, offset);
                break;

            case 1:
                // immediate
                get_instr_bitfields(instr, flds_immediate_word, offset);
                break;

            case 2:
                // indirect
                get_instr_bitfields(instr, flds_indirect, offset);
                instr->word = 1;
                break;

            case 3:
                // indexed
                get_instr_bitfields(instr, flds_indexed, offset);
                instr->word = 1;
                break;
            }
            break;

        case IBF_SHORT_INDEX:
            get_instr_bitfields(instr, flds_immediate_byte, offset);
            break;

        case IBF_LONG_INDEX:
            get_instr_bitfields(instr, flds_immediate_word, offset);
            break;
        }
    }
}


struct instr_entry * decode_instr(uint32_t pc)
{
    struct instr_entry * instr;
    uint32_t opcode;
    uint_t offset;

    instr = instr_entry_create(pc);
    offset = 0;

    // fetch the first byte of the instruction, skipping and flagging the prefix byte if present
    opcode = tgt_byteread(pc);
    if (opcode == INSTR_PREFIX)
    {
        opcode = tgt_byteread(pc + 1);
        instr->prefix = 1;
        offset += 8;
    }

    // get the instruction definition from the first byte of the opcode
    instr->def = instr_set_def + opcode;

    // is instruction prefixed
    if (instr->prefix)
    {
        // can the opcode be prefixed
        if (instr->def->flags & TGT_PREFIX)
        {
            // get the prefixed instruction definition
            instr->def = prefixed_instr_set_def + XLATE_PREFIX_OPCODE(opcode);
        }
        else
        {
            instr->invalid = 1;
        }
    }
    else
    {
        // is instruction invalid
        if (instr->def->flags & TGT_INVALID)
        {
            instr->invalid = 1;
        }
    }

    if (instr->invalid)
    {
        instr->def = invalid_instr_def;
    }

    // disassemble instruction into bitfields
    get_instr_bitfields(instr, instr->def->bitfield_def, &offset);

    if ((offset % 8) != 0)
    {
        printf("\n\nFATAL ERROR: sum of bitfields is not divisible by 8\n");
        exit(1);
    }

    // target operation size in bytes
    instr->size = offset / 8;

    // set the instruction flags
    if (instr->def->flags & TGT_EXECUTION_JUMP) instr->jump = 1;
    if (instr->def->flags & TGT_EXECUTION_CALL) instr->call = 1;
    if (instr->def->flags & TGT_EXECUTION_BARRIER) instr->barrier = 1;

    // if this instruction is a jump or call fixup the target_address to real address
    if (instr->jump)
    {
        // fixup the jump target_address address
        instr->target_address = instr->address->address + instr->target_address + instr->size;
    }

    if (instr->byte || instr->word)
    {
        if (instr->def->flags & TGT_READ) instr->read = 1;
        if (instr->def->flags & TGT_WRITE) instr->write = 1;
    }

    return instr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
