#ifndef _ADDRESS_LIST_H
#define _ADDRESS_LIST_H


#define INORDER_EXECUTION_ADDRESS
#define JUMP_DESTINATION_ADDRESS
#define CALL_DESTINATION_ADDRESS


struct address_table_entry
{
    // strcmp ordered list of symbols associated with address
    struct list_head symbol_head;

    // instruction associated with address
    struct instr_entry * instr;

    // data object associated with address
//    struct data_list_entry * data;

    // pre comment
    // post comment

    // comment
    char * comment;

    // this address requires a label for display
    uint32_t label : 1;

    // code flags
    uint32_t code : 1;
    uint32_t out_of_range : 1;
    uint32_t call_target : 1;
    uint32_t jump_target : 1;

    // data flags
    uint32_t data : 1;
    uint32_t byte : 1;
    uint32_t word : 1;
    uint32_t read : 1;
    uint32_t write : 1;

/*
    // flags
    uint32_t op_fetch : 1;
    uint32_t op_byteread : 1;
    uint32_t op_bytewrite : 1;
    uint32_t op_wordread : 1;
    uint32_t op_wordwrite : 1;

    uint32_t is_pointer : 1;
    uint32_t is_allocate : 1;
*/

    // number of references to this address
    uint_t reference_count;

    // address and size
    uint32_t address;
    uint32_t size;
};

struct symbol_table_entry;

void address_table_init(void);

void address_table_add_symbol(struct address_table_entry * const address_entry, struct symbol_table_entry * const symbol_entry);
struct address_table_entry * address_table_create(uint32_t const address);
struct address_table_entry * address_table_create_symbol(uint32_t const address, char const * symbol);
struct address_table_entry * address_table_create_code(uint32_t const address, char const * symbol);
struct address_table_entry * address_table_create_data(uint32_t const address, char const * symbol);
struct address_table_entry * address_table_create_byte_data(uint32_t const address, char const * symbol);
struct address_table_entry * address_table_create_word_data(uint32_t const address, char const * symbol);
struct address_table_entry * find_address(uint32_t const address);
struct address_table_entry * find_code_address(void);
void address_table_print(void);

//#define TEST_A_LIST
#ifdef TEST_A_LIST
void print_struct_address_list(struct address_table_entry * entry);
void address_table_test(void);
#endif

#endif // _ADDRESS_LIST_H
