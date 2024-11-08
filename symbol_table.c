#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <avl.h>

#include "include_linux_list.h"

#include "project.h"
#include "symbol_table.h"
#include "address_list.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ordered list of symbols
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//
// the symbol table is stored in an AVL Tree
//
avl_tree_t symbol_table;

static void free_symbol_table_entry(void * symbol_entry)
{
    printf("\n\nFATAL ERROR: tried to free a symbol_table_entry\n");
    exit(1);
}


void symbol_table_init(void)
{
    avl_init_tree(&symbol_table, (avl_compare_t) strcmp, free_symbol_table_entry);
}


static inline struct symbol_table_entry * alloc_symbol_table_entry(size_t symbol_length)
{
    struct symbol_table_entry * entry;

    entry = (struct symbol_table_entry *) calloc(1, sizeof(struct symbol_table_entry) + symbol_length + 1);
    if (entry == NULL)
    {
        printf("\n\nFATAL ERROR: failed to allocate symbol_table_entry object\n");
        exit(1);
    }

    INIT_LIST_HEAD(&entry->address_symbol_list);
    entry->length = symbol_length;

    return entry;
}


struct symbol_table_entry * find_symbol(char const * symbol)
{
    avl_node_t * avl_node;

    if ((symbol == NULL) || (*symbol == '\0'))
        return NULL;

    avl_node = avl_search(&symbol_table, symbol);

    if (avl_node == NULL)
        return NULL;

    return container_of(avl_node->item, struct symbol_table_entry, symbol);
}


struct symbol_table_entry * create_symbol(char const * symbol)
{
    struct symbol_table_entry * entry;

    if ((symbol == NULL) || (*symbol == '\0'))
        return NULL;

    entry = find_symbol(symbol);

    if (entry == NULL)
    {
        entry = alloc_symbol_table_entry(strlen(symbol));
        strcpy(entry->symbol, symbol);

        avl_insert(&symbol_table, entry->symbol);
    }

    return entry;
}


struct symbol_table_entry * create_code_symbol(char const * symbol)
{
    struct symbol_table_entry * entry;

    entry = create_symbol(symbol);

    if (entry)
    {
        entry->type = SYM_TYPE_CODE;
    }

    return entry;
}


struct symbol_table_entry * create_data_symbol(char const * symbol)
{
    struct symbol_table_entry * entry;

    entry = create_symbol(symbol);

    if (entry)
    {
        entry->type = SYM_TYPE_DATA;
    }

    return entry;
}


void symbol_list_print(void)
{
    uint_t idx;

    for (idx = 0;; idx++)
    {
        struct symbol_table_entry * entry;
        avl_node_t * avl_node;

        avl_node = avl_at(&symbol_table, idx);

        if (avl_node == NULL) break;

        entry = container_of(avl_node->item, struct symbol_table_entry, symbol);

        display_column = 0;

        if (!entry->address)
            continue;

        //
        // print address
        //
        SET_DISPLAY_COLUMN(address_column);
        display_column += printf("%08x", entry->address->address);

        //
        // print symbol type
        //
        SET_DISPLAY_COLUMN(dump_column);
        if (entry->address->code)
            display_column += printf("CODE");
        if (entry->address->data)
            display_column += printf("DATA");

        //
        // print symbol
        //
        SET_DISPLAY_COLUMN(label_column);
        display_column += printf("%s", entry->symbol);

        if (entry->address)
        {
            //
            // print reference count
            //
            SET_DISPLAY_COLUMN(mnemonic_column);
            display_column += printf("%d", entry->address->reference_count);
        }

        printf("\n");
    }
}


#ifdef TEST_SYMBOL_LIST
void print_struct_symbol_list(struct symbol_table_entry * entry)
{
    printf("    address: %08X\n", entry);
//    printf("         list: next: %08X, prev: %08X\n", entry->list.next, entry->list.prev);
    printf("address_symbol_list: next: %08X, prev: %08X\n", entry->address_symbol_list.next, entry->address_symbol_list.prev);
    printf("       length: %08X\n", entry->length);
    printf("       symbol: %s\n", entry->symbol);
}

void symbol_list_test(void)
{
    struct symbol_table_entry * entry;

    entry = create_symbol("d");
    printf("%s", entry->symbol);
    entry = create_symbol("e");
    printf("%s", entry->symbol);
    entry = create_symbol("c");
    printf("%s", entry->symbol);
    entry = create_symbol("o");
    printf("%s", entry->symbol);
    entry = create_symbol("d");
    printf("%s", entry->symbol);
    entry = create_symbol("e");
    printf("%s", entry->symbol);
    entry = create_symbol("l");
    printf("%s", entry->symbol);
    entry = create_symbol("i");
    printf("%s", entry->symbol);
    entry = create_symbol("n");
    printf("%s", entry->symbol);
    entry = create_symbol("u");
    printf("%s", entry->symbol);
    entry = create_symbol("x");
    printf("%s", entry->symbol);
    printf("\n");
    symbol_list_print();
    exit(0);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
