#ifndef _INSTR_H
#define _INSTR_H

//
// instruction definition
//
struct instr_def
{
    char const * mnemonic;
    struct instr_bitfield_def const * bitfield_def;
    uint_t flags;
};

#define TGT_PREFIX 0x1
#define TGT_INVALID 0x2
#define TGT_EXECUTION_JUMP 0x4
#define TGT_EXECUTION_CALL 0x8
#define TGT_EXECUTION_BARRIER 0x10
#define TGT_READ 0x20
#define TGT_WRITE 0x40

//
// things that affect the execution address
//
//  unconditional jumps barrier disp
//  conditional jumps           disp
//  calls                       disp call
//  returns             barrier
//  reset               barrier
//
// unconditional jumps are barriers and jumps
// conditional jumps are jumps
// return is a barrier
// calls are

//
// instruction prefix byte
//
#define INSTR_PREFIX 0xfe
#define XLATE_PREFIX_OPCODE(a) (((a) >> 4) - 4)


struct instr_entry
{
    // instruction definition
    struct instr_def const * def;

    // address of instruction
    struct address_table_entry * address;

    // number of bitfields in instruction
    uint_t bitfield_count;

    // instruction size in bytes
    uint_t size;

    // flags
    uint32_t prefix : 1;
    uint32_t invalid : 1;
    uint32_t jump : 1;
    uint32_t call : 1;
    uint32_t barrier : 1;
    uint32_t byte : 1;
    uint32_t word : 1;
    uint32_t read : 1;
    uint32_t write : 1;
    uint32_t zero : 1;

    // number of references to instruction (jump, call, ...)
//    uint_t reference_count;

    // for those cases where it can be determined this is the address referenced
    uint32_t target_address;

    // format identifier has one ASCII letter for each bitfield
    char format_identifier[MAX_INSTR_FIELDS + 1];

    // decoded instruction bitfields
    uint32_t bitfield[MAX_INSTR_FIELDS];
};

enum instruction_set
{
    ISA_MCS96 = 1,
    ISA_I8061,
    ISA_I8065,
};

void set_instruction_set(enum instruction_set isa);

struct instr_entry * instr_entry_create(uint32_t const address);
struct instr_entry * find_instr(uint32_t address);
void instr_list_print(void);
struct instr_entry * decode_instr(uint32_t pc);

#endif // _INSTR_H
