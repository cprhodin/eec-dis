#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <argp.h>

#include <avl.h>

#include "include_linux_list.h"

#include "project.h"
#include "tgt_memory.h"
#include "bitfield.h"
#include "ibitfields.h"

#include "instr.h"
#include "symbol_table.h"
#include "address_list.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// display field columns
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define ADDRESS_COLUMN   0
//#define DUMP_COLUMN      0
//#define LABEL_COLUMN     0

#define DUMP_COLUMN      ADDRESS_COLUMN   + 10
#define LABEL_COLUMN     DUMP_COLUMN      + 26
#define MNEMONIC_COLUMN  LABEL_COLUMN     + 20
#define PARAMETER_COLUMN MNEMONIC_COLUMN  + 16
#define COMMENT_COLUMN   PARAMETER_COLUMN + 20
#define PAGE_WIDTH       COMMENT_COLUMN + 20

uint_t address_column   = ADDRESS_COLUMN;
uint_t dump_column      = DUMP_COLUMN;
uint_t label_column     = LABEL_COLUMN;
uint_t mnemonic_column  = MNEMONIC_COLUMN;
uint_t parameter_column = PARAMETER_COLUMN;

uint_t display_column;

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// register names
//
////////////////////////////////////////////////////////////////////////////////////////////////////

char const * byte_src_register_name[256];
char const * byte_dst_register_name[256];
char const * word_src_register_name[128];
char const * word_dst_register_name[128];
char const * long_src_register_name[64];
char const * long_dst_register_name[64];

char tmp_reg[16];


void init_register_names(void)
{
    char * register_name_string;
    int i;

    //
    // the default byte register names require 3 bytes each for the first 10, 4 bytes each for the
    // next 90, and 5 bytes each for the remaining 156
    //
    //  10 * 3 + 90 * 4 + 156 * 5 = 1170
    //
    register_name_string = (char *) calloc(1170, sizeof(char));

    for (i = 0; i < 256; i++)
    {
        byte_src_register_name[i] = NULL;
//        byte_src_register_name[i] = register_name_string;
//        register_name_string += sprintf(register_name_string, "R%d", i) + 1;
    }

    register_name_string = (char *) calloc(1170, sizeof(char));

    for (i = 0; i < 256; i++)
    {
        byte_dst_register_name[i] = NULL;
//        byte_dst_register_name[i] = register_name_string;
//        register_name_string += sprintf(register_name_string, "r%d", i) + 1;
    }

    //
    // the default word register names require 3 bytes each for the first 5, 4 bytes each for the
    // next 45, and 5 bytes each for the remaining 78
    //
    //  5 * 3 + 45 * 4 + 78 * 5 = 585
    //
    register_name_string = (char *) calloc(585, sizeof(char));

    for (i = 0; i < 128; i++)
    {
        word_src_register_name[i] = NULL;
//        word_src_register_name[i] = register_name_string;
//        register_name_string += sprintf(register_name_string, "R%d", i << 1) + 1;
    }

    register_name_string = (char *) calloc(585, sizeof(char));

    for (i = 0; i < 128; i++)
    {
        word_dst_register_name[i] = NULL;
//        word_dst_register_name[i] = register_name_string;
//        register_name_string += sprintf(register_name_string, "r%d", i << 1) + 1;
    }

    //
    // the default long register names require 3 bytes each for the first 3, 4 bytes each for the
    // next 22, and 5 bytes each for the remaining 39
    //
    //  3 * 3 + 22 * 4 + 39 * 5 = 292
    //
    register_name_string = (char *) calloc(292, sizeof(char));

    for (i = 0; i < 64; i++)
    {
        long_src_register_name[i] = NULL;
//        long_src_register_name[i] = register_name_string;
//        register_name_string += sprintf(register_name_string, "R%d", i << 2) + 1;
    }

    register_name_string = (char *) calloc(292, sizeof(char));

    for (i = 0; i < 64; i++)
    {
        long_dst_register_name[i] = NULL;
//        long_dst_register_name[i] = register_name_string;
//        register_name_string += sprintf(register_name_string, "r%d", i << 2) + 1;
    }
}


void printf_register_names(void)
{
    int i;

    printf("\n");

    for (i = 0; i < 256; i++)
    {
        if (byte_src_register_name[i])
        {
            display_column = printf("%s", byte_src_register_name[i]);
            SET_DISPLAY_COLUMN(mnemonic_column);
            printf(".equ            %d\n", i);
        }
        if (byte_dst_register_name[i] && strcmp(byte_src_register_name[i], byte_dst_register_name[i]))
        {
            display_column = printf("%s", byte_dst_register_name[i]);
            SET_DISPLAY_COLUMN(mnemonic_column);
            printf(".equ            %d\n", i);
        }
    }

    for (i = 0; i < 128; i++)
    {
        if (word_src_register_name[i])
        {
            display_column = printf("%s", word_src_register_name[i]);
            SET_DISPLAY_COLUMN(mnemonic_column);
            printf(".equ            %d\n", i << 1);
        }
        if (word_dst_register_name[i] && strcmp(word_src_register_name[i], word_dst_register_name[i]))
        {
            display_column = printf("%s", word_dst_register_name[i]);
            SET_DISPLAY_COLUMN(mnemonic_column);
            printf(".equ            %d\n", i << 1);
        }
    }

    for (i = 0; i < 64; i++)
    {
        if (long_src_register_name[i])
        {
            display_column = printf("%s", long_src_register_name[i]);
            SET_DISPLAY_COLUMN(mnemonic_column);
            printf(".equ            %d\n", i << 2);
        }
        if (long_dst_register_name[i] && strcmp(long_src_register_name[i], long_dst_register_name[i]))
        {
            display_column = printf("%s", long_dst_register_name[i]);
            SET_DISPLAY_COLUMN(mnemonic_column);
            printf(".equ            %d\n", i << 2);
        }
    }
}


void set_byte_src_register_name(uint_t byte_register, char const * name)
{
    char * register_name_string;

    if (byte_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to set the name of an invalid register: %d\n", byte_register);
        exit(1);
    }

    register_name_string = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(register_name_string, name);

    byte_src_register_name[byte_register] = register_name_string;
}


void set_byte_dst_register_name(uint_t byte_register, char const * name)
{
    char * register_name_string;

    if (byte_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to set the name of an invalid register: %d\n", byte_register);
        exit(1);
    }

    register_name_string = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(register_name_string, name);

    byte_dst_register_name[byte_register] = register_name_string;
}


void set_word_src_register_name(uint_t word_register, char const * name)
{
    char * register_name_string;

    if ((word_register > 255) || (word_register & 0x1))
    {
        printf("\n\nFATAL ERROR: attempting to set the name of an invalid register: %d\n", word_register);
        exit(1);
    }

    register_name_string = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(register_name_string, name);

    word_src_register_name[word_register >> 1] = register_name_string;
}


void set_word_dst_register_name(uint_t word_register, char const * name)
{
    char * register_name_string;

    if ((word_register > 255) || (word_register & 0x1))
    {
        printf("\n\nFATAL ERROR: attempting to set the name of an invalid register: %d\n", word_register);
        exit(1);
    }

    register_name_string = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(register_name_string, name);

    word_dst_register_name[word_register >> 1] = register_name_string;
}


void set_long_src_register_name(uint_t long_register, char const * name)
{
    char * register_name_string;

    if ((long_register > 255) || (long_register & 0x3))
    {
        printf("\n\nFATAL ERROR: attempting to set the name of an invalid register: %d\n", long_register);
        exit(1);
    }

    register_name_string = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(register_name_string, name);

    long_src_register_name[long_register >> 2] = register_name_string;
}


void set_long_dst_register_name(uint_t long_register, char const * name)
{
    char * register_name_string;

    if ((long_register > 255) || (long_register & 0x3))
    {
        printf("\n\nFATAL ERROR: attempting to set the name of an invalid register: %d\n", long_register);
        exit(1);
    }

    register_name_string = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(register_name_string, name);

    long_dst_register_name[long_register >> 2] = register_name_string;
}


char const * get_byte_src_register_name(uint_t byte_register)
{
    if (byte_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to get the name of an invalid register: %d\n", byte_register);
        exit(1);
    }

    if (byte_src_register_name[byte_register])
    {
        return byte_src_register_name[byte_register];
    }

    sprintf(tmp_reg, "R%d", byte_register);

    return tmp_reg;
}


char const * get_byte_dst_register_name(uint_t byte_register)
{
    if (byte_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to get the name of an invalid register: %d\n", byte_register);
        exit(1);
    }

    if (byte_dst_register_name[byte_register])
    {
        return byte_dst_register_name[byte_register];
    }

    sprintf(tmp_reg, "r%d", byte_register);

    return tmp_reg;
}


char const * get_word_src_register_name(uint_t word_register)
{
    if (word_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to get the name of an invalid register: %d\n", word_register);
        exit(1);
    }

    if (word_src_register_name[word_register >> 1])
    {
        return word_src_register_name[word_register >> 1];
    }

    sprintf(tmp_reg, "R%d:%d", word_register & 0xFE, word_register & 0x01);

    return tmp_reg;
}


char const * get_word_dst_register_name(uint_t word_register)
{
    if (word_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to get the name of an invalid register: %d\n", word_register);
        exit(1);
    }

    if (word_dst_register_name[word_register >> 1])
    {
        return word_dst_register_name[word_register >> 1];
    }

    sprintf(tmp_reg, "r%d:%d", word_register & 0xFE, word_register & 0x01);

    return tmp_reg;
}


char const * get_long_src_register_name(uint_t long_register)
{
    if (long_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to get the name of an invalid register: %d\n", long_register);
        exit(1);
    }

    if (long_src_register_name[long_register >> 2])
    {
        return long_src_register_name[long_register >> 2];
    }

    sprintf(tmp_reg, "R%d", long_register);

    return tmp_reg;

}


char const * get_long_dst_register_name(uint_t long_register)
{
    if (long_register > 255)
    {
        printf("\n\nFATAL ERROR: attempting to get the name of an invalid register: %d\n", long_register);
        exit(1);
    }

    if (long_dst_register_name[long_register >> 2])
    {
        return long_dst_register_name[long_register >> 2];
    }

    sprintf(tmp_reg, "r%d", long_register);

    return tmp_reg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////

void yyerror(char const * s)
{
    fprintf(stderr, "%s\n", s);
}


extern avl_tree_t address_table;


#include "eec-dis.tab.h"


void print_target_label(struct instr_entry * instr)
{
    struct address_table_entry * address_entry;
    struct symbol_table_entry * symbol_entry;

    address_entry = find_address(instr->target_address & 0x0000ffff);

    if (!address_entry)
    {
        printf("\n\nFATAL ERROR: missing address list entry, %08X\n", instr->target_address & 0x0000ffff);
        exit(1);
    }

    if (list_empty(&address_entry->symbol_head))
    {
        printf("\n\nFATAL ERROR: data target address is unlabeled, %08X\n", instr->target_address & 0x0000ffff);
        exit(1);
    }

    // print the first symbol
    list_for_each_entry(symbol_entry, &address_entry->symbol_head, address_symbol_list)
    {
        display_column += printf("%s", symbol_entry->symbol);
        break;
    }
}


void print_code_symbol(uint32_t address)
{
    struct address_table_entry * address_entry;
    struct symbol_table_entry * symbol_entry;

    address_entry = find_address(address);

    if (address_entry && address_entry->code && !list_empty(&address_entry->symbol_head))
    {
        // print the first symbol
        list_for_each_entry(symbol_entry, &address_entry->symbol_head, address_symbol_list)
        {
            display_column += printf("%s", symbol_entry->symbol);
            break;
        }
        symbol_entry->address->reference_count++;
    }
    else
    {
        display_column += printf("0x%04x", address);
    }
}


void print_data_symbol(uint32_t address)
{
    struct address_table_entry * address_entry;
    struct symbol_table_entry * symbol_entry;

    address_entry = find_address(address);

    if (address_entry && address_entry->data && !list_empty(&address_entry->symbol_head))
    {
        // print the first symbol
        list_for_each_entry(symbol_entry, &address_entry->symbol_head, address_symbol_list)
        {
            display_column += printf("%s", symbol_entry->symbol);
            break;
        }
        symbol_entry->address->reference_count++;
    }
    else
    {
        display_column += printf("0x%04X", address);
    }
}


const char *argp_program_version = "eec-dis 1.0";

const char *argp_program_bug_address = "<chris@notav8.com>";

// This structure is used by main to communicate with parse_opt.
struct arguments
{
    char *dscfile;            // Argument for -d
    char *romfile;            // Argument for -r
    char *outfile;            // Argument for -o
    enum instruction_set isa; // Argument for -I
};

//
// OPTIONS.  Field 1 in ARGP.
// Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
//
static struct argp_option options[] =
{
    {"description-file", 'd', "DSCFILE", 0, "Execute commands from DSCFILE"},
    {"rom-file",         'r', "ROMFILE", 0, "Process contents of ROMFILE"},
    {"output-file",      'o', "OUTFILE", 0, "Output result to OUTFILE"},
    {"instruction-set",  'i', "ISA",     0, "Instruction set; mcs-96, i8061, i8065"},
    {0}
};


//
// PARSER. Field 2 in ARGP.
// Order of parameters: KEY, ARG, STATE.
//
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
    case 'd':
        arguments->dscfile = arg;
        break;
    case 'r':
        arguments->romfile = arg;
        break;
    case 'o':
        arguments->outfile = arg;
        break;
    case 'i':
        if (strncmp(arg, "mcs-96", 6) == 0)
            arguments->isa = ISA_MCS96;
        else if (strncmp(arg, "i8061", 5) == 0)
            arguments->isa = ISA_I8061;
        else if (strncmp(arg, "i8065", 5) == 0)
            arguments->isa = ISA_I8065;
        else
            arguments->isa = 0;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

//
// ARGS_DOC. Field 3 in ARGP.
// A description of the non-option command-line arguments
//   that we accept.
//
static char args_doc[] = "";

//
//  DOC.  Field 4 in ARGP.
//  Program documentation.
//
static char doc[] =
"eec-dis -- A program to disassemble EEC-IV binaries.";

//
// The ARGP structure itself.
//
static struct argp argp = { options, parse_opt, args_doc, doc };


extern FILE *yyin;


int main(int argc, char **argv)
{
    struct arguments arguments;
    struct address_table_entry * address_entry;
    struct symbol_table_entry * symbol_entry;
    FILE * romfile;
    uint32_t rom_start;
    uint32_t rom_limit;
    uint32_t address;
    int idx;
    int i;

    symbol_table_init();
    address_table_init();

    arguments.dscfile = NULL;
    arguments.romfile = NULL;
    arguments.outfile = NULL;
    arguments.isa = ISA_MCS96;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.dscfile) printf("Description file: %s\n", arguments.dscfile);

    if (arguments.romfile) printf("ROM file:  %s\n", arguments.romfile);

    if (arguments.outfile) printf("Output file:  %s\n", arguments.outfile);

    set_instruction_set(arguments.isa);

    init_register_names();

    //
    // load ROM image file
    //
    rom_start = 0x2000;

    if (arguments.romfile)
    {
        long num_bytes;

        romfile = fopen(arguments.romfile, "r");
        if (!romfile)
        {
            printf("\n\nFATAL ERROR: could not open ROM file\n");
            exit(1);
        }

        fseek(romfile, 0L, SEEK_END);
        num_bytes = ftell(romfile);

        fseek(romfile, 0L, SEEK_SET);

        num_bytes = 32768;

        rom_limit = num_bytes + rom_start;

        if (rom_limit > 0x00100000)
        {
            rom_limit = 0x00100000;
            num_bytes = rom_limit - rom_start;
        }

        tgt_memory = malloc(rom_limit);

        num_bytes = fread(&tgt_memory[rom_start], sizeof(uint8_t), num_bytes, romfile);
        printf("Read %d bytes from ROM file: %s\n", num_bytes, arguments.romfile);
    }

    //
    // parse the symbol declarations
    //
    if (arguments.dscfile)
    {
        if (strcmp(arguments.dscfile, "-"))
        {
            yyin = fopen(arguments.dscfile, "r");
        }

        printf("yyparse %s\n", arguments.dscfile);

        yyparse();
    }

    //
    // set the output file
    //
    if (arguments.outfile)
    {
        freopen(arguments.outfile, "w", stdout);
    }

    //
    // set the limits of the disassembled region
    //
    symbol_entry = find_symbol("ROM_START");
    if (symbol_entry && symbol_entry->address)
    {
        rom_start = symbol_entry->address->address;
    }

    symbol_entry = find_symbol("ROM_LIMIT");
    if (symbol_entry && symbol_entry->address)
    {
        rom_limit = symbol_entry->address->address;
    }

#ifdef TEST_SYMBOL_LIST
    symbol_list_test();
#endif

#ifdef TEST_A_LIST
    address_table_test();
#endif

    //
    // build the address and instruction lists
    //
    for (;;)
    {
        struct address_table_entry * code_address_entry;
        uint32_t code_address;

        // find a code address that needs disassembly
        code_address_entry = find_code_address();

        // done when all code addresses have been disassembled
        if (!code_address_entry) break;

        // get the actual address
        code_address = code_address_entry->address;

        // check if address is in range
        if ((code_address < rom_start) || (code_address >= rom_limit))
        {
            code_address_entry->out_of_range = 1;
            continue;
        }

        for (;;)
        {
            struct address_table_entry * target_address_entry;
            struct instr_entry * instr;
            uint32_t target_address;

            instr = decode_instr(code_address);

            target_address = instr->target_address & 0x0000ffff;

            if (instr->call)
            {
                // this is a call instruction, add a call target to the address list
                target_address_entry = address_table_create(target_address);
                target_address_entry->code = 1;
                target_address_entry->call_target = 1;
                target_address_entry->label = 1;
                target_address_entry->reference_count++;
            }
            else if (instr->jump)
            {
                // this is a jump instruction, add a jump target to the address list
                target_address_entry = address_table_create(target_address);
                target_address_entry->code = 1;
                target_address_entry->jump_target = 1;
                target_address_entry->label = 1;
                target_address_entry->reference_count++;
            }
            else if (instr->zero)
            {
                // this is an absolute address data access instruction, add a data target to the address list
                target_address_entry = address_table_create(target_address);
                target_address_entry->data = 1;
                if (instr->byte) target_address_entry->byte = 1;
                if (instr->word) target_address_entry->word = 1;
                if (instr->read) target_address_entry->read = 1;
                if (instr->write) target_address_entry->write = 1;
                target_address_entry->label = 1;
                target_address_entry->reference_count++;
            }

            // test if execution doesn't move past this instruction (ret, sjmp, ...)
            if (instr->barrier) break;

            // advance address past current instruction
            code_address += instr->size;

            // check if address is in range
            if ((code_address < rom_start) || (code_address >= rom_limit)) break;

            // check if address has already been disassembled
            if (find_instr(code_address)) break;
        }
    }

    for (idx = 0;; idx++)
    {
        avl_node_t * avl_node;

        avl_node = avl_at(&address_table, idx);

        if (avl_node == NULL) break;

        address_entry = container_of(avl_node->item, struct address_table_entry, address);

        // auto-generate required labels
        if (list_empty(&address_entry->symbol_head) && address_entry->label)
        {
            char buffer[32];

            // give code labels priority over data labels
            if (address_entry->code)
            {
                // call targets have priority over jump targets
                if (address_entry->call_target)
                    sprintf(buffer, "func%04X", address_entry->address);
                else
                    sprintf(buffer, "L%04X", address_entry->address);

                address_table_create_code(address_entry->address, buffer);
            }
            else
            {
                if (address_entry->word)
                    sprintf(buffer, "WORD%04X", address_entry->address);
                else
                    sprintf(buffer, "BYTE%04X", address_entry->address);

                address_table_create_data(address_entry->address, buffer);
            }
        }

        // gernerate equates for symbols outside of the bounds of the ROM
        if ((address_entry->address < rom_start) ||
            (address_entry->address >= rom_limit))
        {
            list_for_each_entry(symbol_entry, &address_entry->symbol_head, address_symbol_list)
            {
                display_column = printf("%s", symbol_entry->symbol);
                SET_DISPLAY_COLUMN(mnemonic_column);
                printf(".equ            0x%08x\n", address_entry->address);
            }
        }
    }

    printf_register_names();

//    if (address_entry = find_address(0x2000))
//        address_entry->comment = "\n\nComment on code!\nAnd another line.\n\n";

//    if (address_entry = find_address(0x200e))
//        address_entry->comment = "\n\nThis is a comment!\nAnd another line.\n\n";

    address = rom_start;

    printf("\n                    .org            0x%08x\n", rom_start);
    printf("ROM_START:\n");

    for (idx = 0;; idx++)
    {
        avl_node_t * avl_node;

        avl_node = avl_at(&address_table, idx);

        if (avl_node == NULL) break;

        address_entry = container_of(avl_node->item, struct address_table_entry, address);

        struct instr_entry * instr;
        uint32_t limit_address;
        char const * fmt;
        char * label;

        if (   !address_entry->code
            || !address_entry->instr
            ||  address_entry->out_of_range) continue;

        instr = address_entry->instr;

        //
        // dump the data found in gaps between instructions
        //
        limit_address = instr->address->address;

        if (address < limit_address)
        {
            struct address_table_entry * data_address_entry;
            uint32_t size = 0;
            int word = 0;

            for (; address < limit_address; limit_address = instr->address->address)
            {
                display_column = 0;
                label = NULL;

                data_address_entry = find_address(address);

                if (data_address_entry)
                {
                    size = data_address_entry->size;

                    if (data_address_entry->comment)
                    {
                        char * comment;

                        //
                        // print comment
                        //
                        for (comment = data_address_entry->comment; *comment != '\0';)
                        {
                            int line_length;
                            char * line_end;

                            SET_DISPLAY_COLUMN(label_column);

                            line_end = strchr(comment, '\n');

                            if (line_end)
                            {
                                line_length = (line_end - comment) + 1;
                                comment += printf("%.*s", line_length, comment);
                            }
                            else
                            {
                                comment += printf("%s", comment);
                                printf("\n", comment);
                            }

                            display_column = 0;
                        }
                    }

                    if (data_address_entry->word) word = 1;
                    if (data_address_entry->byte) word = 0;

                    // display the first through n - 1 of n data labels
                    list_for_each_entry(symbol_entry, &data_address_entry->symbol_head, address_symbol_list)
                    {
                        if (symbol_entry->type != SYM_TYPE_DATA) continue;

                        // display the previous label
                        if (label)
                        {
                            SET_DISPLAY_COLUMN(label_column);
                            printf("%s:\n", label);
                            display_column = 0;
                        }

                        // get the next label
                        label = symbol_entry->symbol;
                    }
                }

                if (size) limit_address = address + size;

                //
                // print address
                //
                SET_DISPLAY_COLUMN(address_column);
                display_column += printf("%08x", address);

                //
                // print hex bytes
                //
                SET_DISPLAY_COLUMN(dump_column);
                for (i = 0; i < 8; i++)
                {
                    uint32_t this_address = address + i;

                    if (this_address >= limit_address) break;

                    display_column += printf("%02x ", tgt_byteread(this_address));

                    if (find_address(this_address + 1)) limit_address = this_address + 1;
                }

                //
                // print last symbol
                //
                if (label)
                {
                    SET_DISPLAY_COLUMN(label_column);
                    display_column += printf("%s:", label);
                }

                //
                // print pseudo-op
                //
                SET_DISPLAY_COLUMN(mnemonic_column);

                if (word)
                {
                    display_column += printf(".dcw ");
                    print_code_symbol(tgt_wordread(address));
                    for (i = 2; i < 8; i += 2)
                    {
                        uint32_t this_address = address + i;

                        if (this_address >= limit_address) break;

                        display_column += printf(",");
                        print_code_symbol(tgt_wordread(this_address));
                    }
                }
                else
                {
                    display_column += printf(".dcb %3d", tgt_byteread(address));
                    for (i = 1; i < 8; i++)
                    {
                        uint32_t this_address = address + i;

                        if (this_address >= limit_address) break;

                        display_column += printf(", %3d", tgt_byteread(this_address));
                    }
                }

                address += i;

                printf("\n");
            }
        }

        display_column = 0;

        address = instr->address->address;

        if (instr->address->comment)
        {
            char * comment;

            //
            // print comment
            //
            for (comment = instr->address->comment; *comment != '\0';)
            {
                int line_length;
                char * line_end;

                SET_DISPLAY_COLUMN(label_column);

                line_end = strchr(comment, '\n');

                if (line_end)
                {
                    line_length = (line_end - comment) + 1;
                    comment += printf("%.*s", line_length, comment);
                }
                else
                {
                    comment += printf("%s", comment);
                    printf("\n", comment);
                }

                display_column = 0;
            }
        }

        label = NULL;

        // display the first through n - 1 of n labels
        list_for_each_entry(symbol_entry, &instr->address->symbol_head, address_symbol_list)
        {
            if (symbol_entry->type != SYM_TYPE_CODE) continue;

            // display the previous label
            if (label)
            {
                SET_DISPLAY_COLUMN(label_column);
                printf("%s:\n", label);
                display_column = 0;
            }

            // get the next label
            label = symbol_entry->symbol;
        }


        //
        // print address
        //
        SET_DISPLAY_COLUMN(address_column);
        display_column += printf("%08x", address);

        //
        // print hex bytes
        //
        SET_DISPLAY_COLUMN(dump_column);
        for (i = 0; i < instr->size; i++)
        {
            display_column += printf("%02x ", tgt_byteread(address));
            address++;
        }

        //
        // print last symbol
        //
        if (label)
        {
            SET_DISPLAY_COLUMN(label_column);
            display_column += printf("%s:", label);
        }

        //
        // print mnemonic
        //
        SET_DISPLAY_COLUMN(mnemonic_column);
        display_column += printf("%s", instr->def->mnemonic);

        fmt = get_iformat(instr->format_identifier);

        if (fmt == NULL)
        {
            printf("\n\nFATAL ERROR: no format specifier for %s", instr->format_identifier);
            exit(1);
        }

        //
        // print parameters
        //
        SET_DISPLAY_COLUMN(parameter_column);
        while (*fmt != '\0')
        {
            struct address_table_entry * address_entry;
            uint8_t id_index;
            char * id;

            id_index = *fmt - '0';

            id = instr->format_identifier + id_index;

            switch (*id)
            {
            case 'B':
            case 'T':
                display_column += printf("%s", get_byte_src_register_name(instr->bitfield[id_index]));
                break;

            case 'b':
                display_column += printf("%s", get_byte_dst_register_name(instr->bitfield[id_index]));
                break;

            case 'W':
                display_column += printf("%s", get_word_src_register_name(instr->bitfield[id_index]));
                break;

            case 'w':
                display_column += printf("%s", get_word_dst_register_name(instr->bitfield[id_index]));
                break;

            case 'L':
                display_column += printf("%s", get_long_src_register_name(instr->bitfield[id_index]));
                break;

            case 'l':
                display_column += printf("%s", get_long_dst_register_name(instr->bitfield[id_index]));
                break;

            case 'D':
                print_target_label(instr);
                break;

            case 'U':
                display_column += printf("%d", instr->bitfield[id_index]);
                break;

            case 'S':
                display_column += printf("#%d", instr->bitfield[id_index]);
                break;

            case 'I':
                if (strstr(id, "IAQ") == id)
                {
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "IAR") == id)
                {
                    display_column += printf("[%s]+", get_word_dst_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "IAX") == id)
                {
                    display_column += printf("%d[%s]", instr->bitfield[id_index + 3] /*& 0x000000ff*/, get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "IZX") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "IAY") == id)
                {
                    print_data_symbol(instr->bitfield[id_index + 3] & 0x0000ffff);
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "IZY") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "IB") == id)
                {
                    display_column += printf("%s", get_byte_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "IM") == id)
                {
                    display_column += printf("#0x%02X", instr->bitfield[id_index + 1] & 0x000000ff);
                }
                else
                {
                    display_column += printf("\n\nFATAL ERROR: unknown addressing mode, %s\n", instr->format_identifier);
                    exit(1);
                }
                break;

            case 'i':
                if (strstr(id, "iAQ") == id)
                {
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "iAR") == id)
                {
                    display_column += printf("[%s]+", get_word_dst_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "iAX") == id)
                {
                    display_column += printf("%d[%s]", instr->bitfield[id_index + 3] /*& 0x000000ff*/, get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "iZX") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "iAY") == id)
                {
                    print_data_symbol(instr->bitfield[id_index + 3] & 0x0000ffff);
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "iZY") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "iB") == id)
                {
                    display_column += printf("%s", get_byte_dst_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "iM") == id)
                {
                    display_column += printf("#0x%02X", instr->bitfield[id_index + 1] & 0x000000ff);
                }
                else
                {
                    display_column += printf("\n\nFATAL ERROR: unknown addressing mode, %s\n", instr->format_identifier);
                    exit(1);
                }
                break;

            case 'J':
                if (strstr(id, "JAQ") == id)
                {
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "JAR") == id)
                {
                    display_column += printf("[%s]+", get_word_dst_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "JAX") == id)
                {
                    display_column += printf("%d[%s]", instr->bitfield[id_index + 3] /*& 0x000000ff*/, get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "JZX") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "JAY") == id)
                {
                    print_data_symbol(instr->bitfield[id_index + 3] & 0x0000ffff);
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "JZY") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "JW") == id)
                {
                    display_column += printf("%s", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "JM") == id)
                {
                    display_column += printf("#");
                    print_data_symbol(instr->bitfield[id_index + 1] & 0x0000ffff);
                }
                else
                {
                    display_column += printf("\n\nFATAL ERROR: unknown addressing mode, %s\n", instr->format_identifier);
                    exit(1);
                }
                break;

            case 'j':
                if (strstr(id, "jAQ") == id)
                {
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "jAR") == id)
                {
                    display_column += printf("[%s]+", get_word_dst_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "jAX") == id)
                {
                    display_column += printf("%d[%s]", instr->bitfield[id_index + 3] /*& 0x000000ff*/, get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "jZX") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "jAY") == id)
                {
                    print_data_symbol(instr->bitfield[id_index + 3] & 0x0000ffff);
                    display_column += printf("[%s]", get_word_src_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "jZY") == id)
                {
                    print_target_label(instr);
                }
                else if (strstr(id, "jW") == id)
                {
                    display_column += printf("%s", get_word_dst_register_name(instr->bitfield[id_index + 1]));
                }
                else if (strstr(id, "jM") == id)
                {
                    display_column += printf("#");
                    print_data_symbol(instr->bitfield[id_index + 1] & 0x0000ffff);
                }
                else
                {
                    display_column += printf("\n\nFATAL ERROR: unknown addressing mode, %s\n", instr->format_identifier);
                    exit(1);
                }
                break;

            default:
                display_column += printf("%c", *id);
                break;
            }

            fmt++;
            if (*fmt != '\0')
                display_column += printf(", ");
        }

//        if (instr->barrier)
//            printf("\n");

        printf("\n");
    }

    //address_table_print();
    printf("\n");
//    data_list_print();
    symbol_list_print();

    return 0;
}
