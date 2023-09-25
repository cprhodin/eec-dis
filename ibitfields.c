#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ibitfields.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// instruction bitfields
//
////////////////////////////////////////////////////////////////////////////////////////////////////

struct iformat
{
    char * identifier;
    char * specifier;
};

struct iformat const iformats[] =
{
    { "O",          "" },
    { "OB",         "1" },
    { "OBD",        "12" },
    { "OBL",        "21" },
    { "OD",         "1" },
    { "OIAQB",      "41" },
    { "OIAQBB",     "541" },
    { "OIAQBW",     "541" },
    { "OIAQW",      "41" },
    { "OIARB",      "41" },
    { "OIARBB",     "541" },
    { "OIARBW",     "541" },
    { "OIARW",      "41" },
    { "OIAXMB",     "51" },
    { "OIAXMBB",    "651" },
    { "OIAXMBW",    "651" },
    { "OIAXMW",     "51" },
    { "OIAYMB",     "51" },
    { "OIAYMBB",    "651" },
    { "OIAYMBW",    "651" },
    { "OIAYMW",     "51" },
    { "OIBB",       "31" },
    { "OIBBB",      "431" },
    { "OIBBW",      "431" },
    { "OIBW",       "31" },
    { "OIMB",       "31" },
    { "OIMBB",      "431" },
    { "OIMBW",      "431" },
    { "OIMW",       "31" },
    { "OIZXMB",     "51" },
    { "OIZXMBB",    "651" },
    { "OIZXMBW",    "651" },
    { "OIZXMW",     "51" },
    { "OIZYMB",     "51" },
    { "OIZYMBB",    "651" },
    { "OIZYMBW",    "651" },
    { "OIZYMW",     "51" },
    { "OJAQ",       "1" },
    { "OJAQL",      "41" },
    { "OJAQW",      "41" },
    { "OJAQWL",     "541" },
    { "OJAQWW",     "541" },
    { "OJAR",       "1" },
    { "OJARL",      "41" },
    { "OJARW",      "41" },
    { "OJARWL",     "541" },
    { "OJARWW",     "541" },
    { "OJAXM",      "1" },
    { "OJAXML",     "51" },
    { "OJAXMW",     "51" },
    { "OJAXMWL",    "651" },
    { "OJAXMWW",    "651" },
    { "OJAYM",      "1" },
    { "OJAYML",     "51" },
    { "OJAYMW",     "51" },
    { "OJAYMWL",    "651" },
    { "OJAYMWW",    "651" },
    { "OJZXM",      "1" },
    { "OJZXML",     "51" },
    { "OJZXMW",     "51" },
    { "OJZXMWL",    "651" },
    { "OJZXMWW",    "651" },
    { "OJZYM",      "1" },
    { "OJZYML",     "51" },
    { "OJZYMW",     "51" },
    { "OJZYMWL",    "651" },
    { "OJZYMWW",    "651" },
    { "OJM",        "1" },
    { "OJML",       "31" },
    { "OJMW",       "31" },
    { "OJMWL",      "431" },
    { "OJMWW",      "431" },
    { "OJW",        "1" },
    { "OJWL",       "31" },
    { "OJWW",       "31" },
    { "OJWWL",      "431" },
    { "OJWWW",      "431" },
    { "OL",         "1" },
    { "OSB",        "21" },
    { "OSL",        "21" },
    { "OSW",        "21" },
    { "OTB",        "21" },
    { "OTL",        "21" },
    { "OTW",        "21" },
    { "OUBD",       "213" },
    { "OW",         "1" },
};
#define NUMBER_OF_IFORMATS (sizeof(iformats)/sizeof(iformats[0]))


char const * get_iformat(char const * identifier)
{
    char xidentifier[8];
    int i;

    for (i = 0; i < 8; i++)
    {
        xidentifier[i] = toupper(identifier[i]);
        if (identifier[i] == '\0') break;
    }

    for (i = 0; i < NUMBER_OF_IFORMATS; i++)
    {
        if (strncmp(iformats[i].identifier, xidentifier, 7) == 0)
        {
            return iformats[i].specifier;
        }
    }

    return NULL;
}

// "O"
struct instr_bitfield_def const flds_intrinsic[] =
{
    {  8, IBF_OPCODE },
    {  0, IBF_END },
};


// "OB"
struct instr_bitfield_def const flds_bytereg[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_DST_BYTE_REGISTER },
    {  0, IBF_END },
};


// "OW"
struct instr_bitfield_def const flds_wordreg[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_DST_WORD_REGISTER },
    {  0, IBF_END },
};


// "OL"
struct instr_bitfield_def const flds_longreg[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_DST_LONG_REGISTER },
    {  0, IBF_END },
};


// "OSB", "OTB"
struct instr_bitfield_def const flds_byteshft[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_SHIFT },
    {  8, IBF_DST_BYTE_REGISTER },
    {  0, IBF_END },
};


// "OSW", "OTW"
struct instr_bitfield_def const flds_wordshft[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_SHIFT },
    {  8, IBF_DST_WORD_REGISTER },
    {  0, IBF_END },
};


// "OSL", "OTL"
struct instr_bitfield_def const flds_longshft[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_SHIFT },
    {  8, IBF_DST_LONG_REGISTER },
    {  0, IBF_END },
};


// "OBL"
struct instr_bitfield_def const flds_norml[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_DST_BYTE_REGISTER },
    {  8, IBF_DST_LONG_REGISTER },
    {  0, IBF_END },
};


// "OD"
struct instr_bitfield_def const flds_lcall_ljmp[] =
{
    {  8, IBF_OPCODE },
    { 16, IBF_DISPLACEMENT },
    {  0, IBF_END },
};


// "OD"
struct instr_bitfield_def const flds_scall_sjmp[] =
{
    {  5, IBF_OPCODE },
    { 11, IBF_DISPLACEMENT },
    {  0, IBF_END },
};


// "OD"
struct instr_bitfield_def const flds_jmp[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_DISPLACEMENT },
    {  0, IBF_END }
};


// "OUBD"
struct instr_bitfield_def const flds_jbc_jbs[] =
{
    {  5, IBF_OPCODE },
    {  3, IBF_BIT_SELECT },
    {  8, IBF_SRC_BYTE_REGISTER },
    {  8, IBF_DISPLACEMENT },
    {  0, IBF_END }
};


// "OBD"
struct instr_bitfield_def const flds_djnz[] =
{
    {  8, IBF_OPCODE },
    {  8, IBF_DST_BYTE_REGISTER },
    {  8, IBF_DISPLACEMENT },
    {  0, IBF_END }
};


// "OJW", "OJM", "OJAQ", "OJAR", "OJAXM", "OJAYM"
struct instr_bitfield_def const flds_1op_waop[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_WORD_AOP },
    {  0, IBF_END }
};


// "OIBB", "OIMB", "OIAQB", "OIARB", "OIAXMB", "OIAYMB"
struct instr_bitfield_def const flds_2op_baops[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_BYTE_AOP },
    {  8, IBF_SRC_BYTE_REGISTER },
    {  0, IBF_END }
};


// "OIBb", "OIMb", "OIAQb", "OIARb", "OIAXMb", "OIAYMb"
struct instr_bitfield_def const flds_2op_baop[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_BYTE_AOP },
    {  8, IBF_DST_BYTE_REGISTER },
    {  0, IBF_END }
};


// "OIBW", "OIMW", "OIAQW", "OIARW", "OIAXMW", "OIAYMW"
struct instr_bitfield_def const flds_2op_baopw[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_BYTE_AOP },
    {  8, IBF_DST_WORD_REGISTER },
    {  0, IBF_END }
};


// "OJWW", "OJMW", "OJAQW", "OJARW", "OJAXMW", "OJAYMW"
struct instr_bitfield_def const flds_2op_waops[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_WORD_AOP },
    {  8, IBF_SRC_WORD_REGISTER },
    {  0, IBF_END }
};


// "OJWW", "OJMW", "OJAQW", "OJARW", "OJAXMW", "OJAYMW"
struct instr_bitfield_def const flds_2op_waop[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_WORD_AOP },
    {  8, IBF_DST_WORD_REGISTER },
    {  0, IBF_END }
};


// "OJWL", "OJML", "OJAQL", "OJARL", "OJAXML", "OJAYML"
struct instr_bitfield_def const flds_2op_waopl[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_WORD_AOP },
    {  8, IBF_DST_LONG_REGISTER },
    {  0, IBF_END }
};


// "OIBBB", "OIMBB", "OIAQBB", "OIARBB", "OIAXMBB", "OIAYMBB"
struct instr_bitfield_def const flds_3op_baop[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_BYTE_AOP },
    {  8, IBF_SRC_BYTE_REGISTER },
    {  8, IBF_DST_BYTE_REGISTER },
    {  0, IBF_END }
};


// "OIBBW", "OIMBW", "OIAQBW", "OIARBW", "OIAXMBW", "OIAYMBW"
struct instr_bitfield_def const flds_3op_baopw[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_BYTE_AOP },
    {  8, IBF_SRC_BYTE_REGISTER },
    {  8, IBF_DST_WORD_REGISTER },
    {  0, IBF_END }
};


// "OJWWW", "OJMWW", "OJAQWW", "OJARWW", "OJAXMWW", "OJAYMWW"
struct instr_bitfield_def const flds_3op_waop[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_WORD_AOP },
    {  8, IBF_SRC_WORD_REGISTER },
    {  8, IBF_DST_WORD_REGISTER },
    {  0, IBF_END }
};


// "OJWWL", "OJMWL", "OJAQWL", "OJARWL", "OJAXMWL", "OJAYMWL"
struct instr_bitfield_def const flds_3op_waopl[] =
{
    {  6, IBF_OPCODE },
    {  2, IBF_WORD_AOP },
    {  8, IBF_SRC_WORD_REGISTER },
    {  8, IBF_DST_LONG_REGISTER },
    {  0, IBF_END }
};


// "-B-"
struct instr_bitfield_def const flds_direct_byte[] =
{
    {  8, IBF_SRC_BYTE_REGISTER },
    {  0, IBF_END }
};


// "-W-"
struct instr_bitfield_def const flds_direct_word[] =
{
    {  8, IBF_SRC_WORD_REGISTER },
    {  0, IBF_END }
};


// "-M-"
struct instr_bitfield_def const flds_immediate_byte[] =
{
    {  8, IBF_IMMEDIATE },
    {  0, IBF_END }
};


// "-M-"
struct instr_bitfield_def const flds_immediate_word[] =
{
    { 16, IBF_IMMEDIATE },
    {  0, IBF_END }
};


// "-AQ-", "-AR-"
struct instr_bitfield_def const flds_indirect[] =
{
    {  7, IBF_ADDRESS_REGISTER },
    {  1, IBF_AUTO_INCREMENT },
    {  0, IBF_END }
};


// "-AXM-", "-AYM-"
struct instr_bitfield_def const flds_indexed[] =
{
    {  7, IBF_ADDRESS_REGISTER },
    {  1, IBF_INDEXED },
    {  0, IBF_END }
};
