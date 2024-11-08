#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <avl.h>

#include "include_linux_list.h"

#include "project.h"
#include "address_list.h"
#include "symbol_table.h"

avl_tree_t address_table;


static void free_address_table_entry(void * address_entry)
{
    printf("\n\nFATAL ERROR: tried to free an address_table_entry\n");
    exit(1);
}


static int address_table_compare(uint32_t const * p1, uint32_t  const * p2)
{
    if (*p1 == *p2)
        return 0;

    if (*p1 > *p2)
        return 1;
    else
        return -1;
}


void address_table_init(void)
{
    avl_init_tree(&address_table, (avl_compare_t) address_table_compare, free_address_table_entry);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ordered list of addresses
//
////////////////////////////////////////////////////////////////////////////////////////////////////

static inline struct address_table_entry * alloc_address_table_entry(void)
{
    struct address_table_entry * entry;

    entry = (struct address_table_entry *) calloc(1, sizeof(struct address_table_entry));
    if (entry == NULL)
    {
        printf("\n\nFATAL ERROR: failed to allocate address_table_entry object\n");
        exit(1);
    }

    INIT_LIST_HEAD(&entry->symbol_head);

    return entry;
}


struct address_table_entry * address_table_create(uint32_t const address)
{
    struct address_table_entry * entry;

    entry = find_address(address);

    if (entry == NULL)
    {
        entry = alloc_address_table_entry();
        entry->address = address;

        avl_insert(&address_table, &entry->address);
    }

    return entry;
}


static void address_table_add_symbol(struct address_table_entry * const address_entry,
                                     struct symbol_table_entry * const symbol_entry)
{
    if (address_entry && symbol_entry)
    {
        struct symbol_table_entry * entry;
        struct list_head * head;

        if (symbol_entry->address)
        {
            if (symbol_entry->address != address_entry)
            {
                printf("\n\nFATAL ERROR: attemping to link multiple addresses to one symbol\n");
                exit(1);
            }
            return;
        }
        symbol_entry->address = address_entry;

        list_for_each(head, &address_entry->symbol_head)
        {
            int rc;

            entry = list_entry(head, struct symbol_table_entry, address_symbol_list);
            rc = strcmp(entry->symbol, symbol_entry->symbol);

            if (rc == 0) return;

            if (rc > 0) break;
        }
        list_add_tail(&symbol_entry->address_symbol_list, head);
    }
}


struct address_table_entry * address_table_create_symbol(uint32_t const address, char const * symbol)
{
    struct address_table_entry * entry;
    struct symbol_table_entry * symbol_entry;
    struct list_head * head;

    entry = address_table_create(address);

    symbol_entry = create_symbol(symbol);

    address_table_add_symbol(entry, symbol_entry);

    return entry;
}


struct address_table_entry * address_table_create_code(uint32_t const address, char const * symbol)
{
    struct address_table_entry * entry;
    struct symbol_table_entry * symbol_entry;

    //printf("address_table_create_code(%08X, %s)\n", address, symbol);

    entry = address_table_create(address);
    entry->code = 1;

    if (symbol)
    {
        symbol_entry = create_code_symbol(symbol);
        address_table_add_symbol(entry, symbol_entry);
        entry->label = 1;
    }

    return entry;
}


struct address_table_entry * address_table_create_data(uint32_t const address, char const * symbol)
{
    struct address_table_entry * entry;
    struct symbol_table_entry * symbol_entry;

    entry = address_table_create(address);
    entry->data = 1;

    symbol_entry = create_data_symbol(symbol);

    address_table_add_symbol(entry, symbol_entry);

    return entry;
}


struct address_table_entry * address_table_create_byte_data(uint32_t const address, char const * symbol)
{
    struct address_table_entry * entry;
    struct symbol_table_entry * symbol_entry;

    entry = address_table_create_data(address, symbol);
    entry->byte = 1;

    return entry;
}


struct address_table_entry * address_table_create_word_data(uint32_t const address, char const * symbol)
{
    struct address_table_entry * entry;
    struct symbol_table_entry * symbol_entry;

    if (address & 0x1)
    {
        printf("\n\nFATAL ERROR: attempting to create word data object on byte boundary\n");
        exit(1);
    }

    entry = address_table_create_data(address, symbol);
    entry->word = 1;

    return entry;
}

struct address_table_entry * find_address(uint32_t const address)
{
    avl_node_t * avl_node;

    avl_node = avl_search(&address_table, &address);

    if (avl_node == NULL)
        return NULL;

    return container_of(avl_node->item, struct address_table_entry, address);
}

struct address_table_entry * find_code_address(void)
{
    uint_t idx;

    for (idx = 0;; idx++)
    {
        struct address_table_entry * entry;
        avl_node_t * avl_node;

        avl_node = avl_at(&address_table, idx);

        if (avl_node == NULL) break;

        entry = container_of(avl_node->item, struct address_table_entry, address);

        if (entry->code && !entry->instr && !entry->out_of_range) return entry;
    }

    return NULL;
}


void address_table_print(void)
{
    uint_t idx;

    for (idx = 0;; idx++)
    {
        struct address_table_entry * entry;
        struct symbol_table_entry * symbol_entry;
        avl_node_t * avl_node;

        avl_node = avl_at(&address_table, idx);

        if (avl_node == NULL) break;

        entry = container_of(avl_node->item, struct address_table_entry, address);

        printf("address: %08X", entry->address);
        if (entry->code) printf(" CODE");
        if (entry->data) printf(" DATA");
        printf("\n");

        list_for_each_entry(symbol_entry, &entry->symbol_head, address_symbol_list)
        {
            printf("    %s\n", symbol_entry->symbol);
        }
    }
}


#ifdef TEST_A_LIST
void print_struct_address_list(struct address_table_entry * entry)
{
    printf("    address: %08X\n", entry);
    printf("         list: next: %08X, prev: %08X\n", entry->list.next, entry->list.prev);
    printf("  symbol_head: next: %08X, prev: %08X\n", entry->symbol_head.next, entry->symbol_head.prev);
    printf("      address: %08X\n", entry->address);
}

void address_table_test(void)
{
    address_table_create(0x2002);
    address_table_create(0x2020);
    address_table_create_symbol(0x2000, "ROM_BASE");
    address_table_create(0x4132);
    address_table_create(0x2000);
    address_table_create_symbol(0x2000, "RESET");
    address_table_create_symbol(0xa000, "ROM_END");
    address_table_create_symbol(0x2020, "VECTORS");
    address_table_create_symbol(0x4132, "JUMP_TABLE");
    address_table_print();
    symbol_list_print();
    exit(0);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
