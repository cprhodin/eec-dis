#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

struct symbol_table_entry
{
    // symbol address
    struct address_table_entry * address;

    // strcmp ordered list of symbols at same address
    struct list_head address_symbol_list;

    // symbol type information
    uint32_t type;

    // strlen symbol size
    size_t length;

    // null terminated symbol
    char symbol[0];
};

#define SYM_TYPE_NONE 0
#define SYM_TYPE_CODE 1
#define SYM_TYPE_DATA 2

void symbol_table_init(void);

struct symbol_table_entry * find_symbol(char const * symbol);
struct symbol_table_entry * create_symbol(char const * symbol);

struct symbol_table_entry * create_code_symbol(char const * symbol);
struct symbol_table_entry * create_data_symbol(char const * symbol);


void symbol_list_print(void);
void symbol_list_print_code(void);
void symbol_list_print_data(void);

//#define TEST_SYMBOL_LIST
#ifdef TEST_SYMBOL_LIST
void print_struct_symbol_list(struct symbol_table_entry * entry);
void symbol_list_test(void);
#endif

#endif // _SYMBOL_TABLE_H
