%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "include_linux_list.h"

#include "project.h"

#include "tgt_memory.h"

#include "eec-dis.yy.h"

#include "address_list.h"
#include "symbol_table.h"

void set_byte_src_register_name(uint_t byte_register, char const * name);
void set_byte_dst_register_name(uint_t byte_register, char const * name);
void set_word_src_register_name(uint_t word_register, char const * name);
void set_word_dst_register_name(uint_t word_register, char const * name);

extern void yyerror(char const * s);
%}

%union
{
    uint32_t num;
    char *    str;
    struct symbol_table_entry * sym;
}

%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token STRUCT UNION ENUM ELLIPSIS


%token CODE BYTE WORD LONG REGISTER SRC DST

%token <num> CONSTANT
%token <sym> IDENTIFIER
%token <str> STRING_LITERAL

%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <num> expression

%%

declarations: /* empty */
    | declarations declaration
    ;

declaration:
      symbol
    | comment
    | code
    | code_ptr
    | code_ptr_array
    | deref_code_ptr
    | deref_code_ptr_array
    | byte
    | byte_array
    | byte_register
    | byte_src_register
    | byte_dst_register
    | word
    | word_array
    | word_register
    | word_src_register
    | word_dst_register
    ;

symbol:
    IDENTIFIER '@' expression ';'
    {
        address_table_create_symbol($3, $1->symbol);
    }
    ;

comment:
    STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create($3);

        address_entry->comment = $1;
    }
    ;

code:
    IDENTIFIER CODE '@' expression ';'
    {
        address_table_create_code($4, $1->symbol);
    }
    ;

code:
    CODE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_code($4, NULL);

        address_entry->comment = $2;
    }
    ;

code:
    IDENTIFIER CODE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_code($5, $1->symbol);

        address_entry->comment = $3;
    }
    ;

code_ptr:
    IDENTIFIER '*' CODE '@' expression ';'
    {
        address_table_create_word_data($5, $1->symbol);
    }
    ;

code_ptr_array:
    IDENTIFIER '[' ']' '*' CODE '@' expression ';'
    {
        address_table_create_word_data($7, $1->symbol);
    }
    ;

code_ptr_array:
    IDENTIFIER '[' expression ']' '*' CODE '@' expression ';'
    {
        address_table_create_word_data($8, $1->symbol);
    }
    ;

code_ptr_array:
    IDENTIFIER '[' expression ']' '*' CODE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_word_data($9, $1->symbol);

        address_entry->comment = $7;
    }
    ;

deref_code_ptr:
    IDENTIFIER CODE '@' '*' IDENTIFIER ';'
    {
        if ($5 && $5->address)
        {
            uint32_t address;

            address = tgt_wordread($5->address->address);
            address_table_create_code(address, $1->symbol);
        }
        else
        {
            printf("\n\nFATAL ERROR: deref_code_ptr_array\n");
            exit(1);
        }
    }
    ;

deref_code_ptr_array:
    IDENTIFIER CODE '@' '*' IDENTIFIER '[' expression ']' ';'
    {
        if ($5 && $5->address)
        {
            uint32_t address;

            address = tgt_wordread($5->address->address + (2 * $7));
            address_table_create_code(address, $1->symbol);
        }
        else
        {
            printf("\n\nFATAL ERROR: deref_code_ptr_array\n");
            exit(1);
        }
    }
    ;

deref_code_ptr_array:
    IDENTIFIER CODE STRING_LITERAL '@' '*' IDENTIFIER '[' expression ']' ';'
    {
        if ($6 && $6->address)
        {
            uint32_t address;

            address = tgt_wordread($6->address->address + (2 * $8));
            address_table_create_code(address, $1->symbol)->comment = $3;
        }
        else
        {
            printf("\n\nFATAL ERROR: deref_code_ptr_array\n");
            exit(1);
        }
    }
    ;

byte:
    BYTE '@' expression ';'
    {
        address_table_create_byte_data($3, NULL);
    }
    ;

byte:
    BYTE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_byte_data($4, NULL);

        address_entry->comment = $2;
    }
    ;

byte:
    IDENTIFIER BYTE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_byte_data($5, $1->symbol);

        address_entry->comment = $3;
    }
    ;

byte:
    IDENTIFIER BYTE '@' expression ';'
    {
        address_table_create_byte_data($4, $1->symbol);
    }
    ;

byte_array:
    IDENTIFIER '[' ']' BYTE '@' expression ';'
    {
        address_table_create_byte_data($6, $1->symbol);
    }
    ;

byte_array:
    IDENTIFIER '[' ']' BYTE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_byte_data($7, $1->symbol);

        address_entry->comment = $5;
    }
    ;

byte_array:
    IDENTIFIER '[' expression ']' BYTE '@' expression ';'
    {
        address_table_create_byte_data($7, $1->symbol);
    }
    ;

byte_array:
    IDENTIFIER '[' ']' '[' expression ']' BYTE '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_byte_data($9, $1->symbol);

        address_entry->size = $5;
    }
    ;

byte_array:
    IDENTIFIER '[' ']' '[' expression ']' BYTE STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_byte_data($10, $1->symbol);

        address_entry->comment = $8;
        address_entry->size = $5;
    }
    ;

byte_register:
    IDENTIFIER BYTE '@' REGISTER expression ';'
    {
        set_byte_src_register_name($5, $1->symbol);
        set_byte_dst_register_name($5, $1->symbol);
    }
    ;

byte_src_register:
    IDENTIFIER BYTE '@' SRC REGISTER expression ';'
    {
        set_byte_src_register_name($6, $1->symbol);
    }
    ;

byte_dst_register:
    IDENTIFIER BYTE '@' DST REGISTER expression ';'
    {
        set_byte_dst_register_name($6, $1->symbol);
    }
    ;

word:
    WORD '@' expression ';'
    {
        address_table_create_word_data($3, NULL);
    }
    ;

word:
    IDENTIFIER WORD STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_word_data($5, $1->symbol);

        address_entry->comment = $3;
    }
    ;

word:
    IDENTIFIER WORD '@' expression ';'
    {
        address_table_create_word_data($4, $1->symbol);
    }
    ;

word_array:
    IDENTIFIER '[' ']' WORD '@' expression ';'
    {
        address_table_create_word_data($6, $1->symbol);
    }
    ;

word_array:
    IDENTIFIER '[' ']' WORD STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_word_data($7, $1->symbol);

        address_entry->comment = $5;
    }
    ;

word_array:
    IDENTIFIER '[' expression ']' WORD '@' expression ';'
    {
        address_table_create_word_data($7, $1->symbol);
    }
    ;

word_array:
    IDENTIFIER '[' expression ']' WORD STRING_LITERAL '@' expression ';'
    {
        struct address_table_entry * address_entry;

        address_entry = address_table_create_word_data($8, $1->symbol);

        address_entry->comment = $6;
    }
    ;

word_register:
    IDENTIFIER WORD '@' REGISTER expression ';'
    {
        set_word_src_register_name($5, $1->symbol);
        set_word_dst_register_name($5, $1->symbol);
    }
    ;

word_src_register:
    IDENTIFIER WORD '@' SRC REGISTER expression ';'
    {
        set_word_src_register_name($6, $1->symbol);
    }
    ;

word_dst_register:
    IDENTIFIER WORD '@' DST REGISTER expression ';'
    {
        set_word_dst_register_name($6, $1->symbol);
    }
    ;

expression:
      expression '+' expression   { $$ = $1 + $3; }
    | expression '-' expression   { $$ = $1 - $3; }
    | expression '*' expression   { $$ = $1 * $3; }
    | expression '/' expression   { $$ = $1 / $3; }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')'          { $$ = $2; }
    | CONSTANT                    { $$ = $1; }
    | IDENTIFIER                  { $$ = $1->address->address; }
    ;
