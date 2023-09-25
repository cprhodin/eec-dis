#ifndef _IBITFIELDS_H
#define _IBITFIELDS_H

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// instruction bitfields
//
////////////////////////////////////////////////////////////////////////////////////////////////////

struct instr_bitfield_def
{
    uint8_t width;
    uint8_t type;
};


enum instr_bitfield_type
{
    IBF_END                 = '\0', // terminates instruction bitfield definition

    IBF_OPCODE              = 'O',  // instruction opcode
    IBF_BYTE_AOP            = 'I',  // byte address operand
    IBF_WORD_AOP            = 'J',  // word address operand

    IBF_BYTE_AOP_SRC        = 'i',  // byte address operand
    IBF_WORD_AOP_SRC        = 'j',  // word address operand

    IBF_SHIFT               = 'S',
    IBF_SHIFT_IMMEDIATE     = IBF_SHIFT,
    IBF_SHIFT_REGISTER      = IBF_SHIFT + 1,

    IBF_AUTO_INCREMENT      = 'Q',
    IBF_NO_INCREMENT        = IBF_AUTO_INCREMENT,
    IBF_INCREMENT           = IBF_AUTO_INCREMENT + 1,

    IBF_ADDRESS_REGISTER    = 'A',

    IBF_DST_BYTE_REGISTER   = 'b',
    IBF_DST_WORD_REGISTER   = 'w',
    IBF_DST_LONG_REGISTER   = 'l',

    IBF_SRC_BYTE_REGISTER   = 'B',
    IBF_SRC_WORD_REGISTER   = 'W',
    IBF_SRC_LONG_REGISTER   = 'L',

    IBF_BIT_SELECT          = 'U',

    IBF_IMMEDIATE           = 'M',

    IBF_INDEXED             = 'X',
    IBF_SHORT_INDEX         = IBF_INDEXED,
    IBF_LONG_INDEX          = IBF_INDEXED + 1,

    IBF_DISPLACEMENT        = 'D',

    IBF_PREFIX              = 'P',
};


extern struct instr_bitfield_def const flds_intrinsic[];
extern struct instr_bitfield_def const flds_bytereg[];
extern struct instr_bitfield_def const flds_wordreg[];
extern struct instr_bitfield_def const flds_longreg[];
extern struct instr_bitfield_def const flds_byteshft[];
extern struct instr_bitfield_def const flds_wordshft[];
extern struct instr_bitfield_def const flds_longshft[];
extern struct instr_bitfield_def const flds_norml[];
extern struct instr_bitfield_def const flds_scall_sjmp[];
extern struct instr_bitfield_def const flds_lcall_ljmp[];
extern struct instr_bitfield_def const flds_jbc_jbs[];
extern struct instr_bitfield_def const flds_jmp[];
extern struct instr_bitfield_def const flds_djnz[];
extern struct instr_bitfield_def const flds_1op_waop[];
extern struct instr_bitfield_def const flds_2op_baops[];
extern struct instr_bitfield_def const flds_2op_baop[];
extern struct instr_bitfield_def const flds_2op_baopw[];
extern struct instr_bitfield_def const flds_2op_waops[];
extern struct instr_bitfield_def const flds_2op_waop[];
extern struct instr_bitfield_def const flds_2op_waopl[];
extern struct instr_bitfield_def const flds_3op_baop[];
extern struct instr_bitfield_def const flds_3op_baopw[];
extern struct instr_bitfield_def const flds_3op_waop[];
extern struct instr_bitfield_def const flds_3op_waopl[];
extern struct instr_bitfield_def const flds_direct_byte[];
extern struct instr_bitfield_def const flds_direct_word[];
extern struct instr_bitfield_def const flds_immediate_byte[];
extern struct instr_bitfield_def const flds_immediate_word[];
extern struct instr_bitfield_def const flds_indirect[];
extern struct instr_bitfield_def const flds_indexed[];


extern char const * get_iformat(char const * identifier);

#endif // _IBITFIELDS_H
