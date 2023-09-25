////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define MCS_96_INVALID_INSTRUCTION                                                                 \
    INSTRUCTION_DEF( 0x00, "********<invalid instruction>********", flds_intrinsic, TGT_INVALID )

// index: opcode / 16 - 4
#define MCS_96_PREFIXED_INSTRUCTION_SET                                                            \
    INSTRUCTION_DEF( 0x4c, "mul",   flds_3op_waopl,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x5c, "mulb",  flds_3op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x6c, "mul",   flds_2op_waopl,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x7c, "mulb",  flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x8c, "div",   flds_2op_waopl,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x9c, "divb",  flds_2op_baopw,  TGT_READ ),                                   \

#define MCS_96_INSTRUCTION_SET                                                                     \
    INSTRUCTION_DEF( 0x00, "skip",  flds_bytereg,    0 ),                                          \
    INSTRUCTION_DEF( 0x01, "clr",   flds_wordreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x02, "not",   flds_wordreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x03, "neg",   flds_wordreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x04, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x05, "dec",   flds_wordreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x06, "ext",   flds_longreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x07, "inc",   flds_wordreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x08, "shr",   flds_wordshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x09, "shl",   flds_wordshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x0a, "shra",  flds_wordshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x0b, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x0c, "shrl",  flds_longshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x0d, "shll",  flds_longshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x0e, "shral", flds_longshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x0f, "norml", flds_norml,      0 ),                                          \
    INSTRUCTION_DEF( 0x10, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x11, "clrb",  flds_bytereg,    0 ),                                          \
    INSTRUCTION_DEF( 0x12, "notb",  flds_bytereg,    0 ),                                          \
    INSTRUCTION_DEF( 0x13, "negb",  flds_bytereg,    0 ),                                          \
    INSTRUCTION_DEF( 0x14, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x15, "decb",  flds_bytereg,    0 ),                                          \
    INSTRUCTION_DEF( 0x16, "extb",  flds_wordreg,    0 ),                                          \
    INSTRUCTION_DEF( 0x17, "incb",  flds_bytereg,    0 ),                                          \
    INSTRUCTION_DEF( 0x18, "shrb",  flds_byteshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x19, "shlb",  flds_byteshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x1a, "shrab", flds_byteshft,   0 ),                                          \
    INSTRUCTION_DEF( 0x1b, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x1c, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x1d, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x1e, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x1f, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0x20, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x21, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x22, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x23, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x24, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x25, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x26, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x27, "sjmp",  flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0x28, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x29, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x2a, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x2b, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x2c, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x2d, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x2e, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x2f, "scall", flds_scall_sjmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0x30, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x31, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x32, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x33, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x34, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x35, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x36, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x37, "jbc",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x38, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x39, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x3a, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x3b, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x3c, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x3d, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x3e, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x3f, "jbs",   flds_jbc_jbs,    TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0x40, "and",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x41, "and",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x42, "and",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x43, "and",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x44, "add",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x45, "add",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x46, "add",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x47, "add",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x48, "sub",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x49, "sub",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x4a, "sub",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x4b, "sub",   flds_3op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x4c, "mulu",  flds_3op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x4d, "mulu",  flds_3op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x4e, "mulu",  flds_3op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x4f, "mulu",  flds_3op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x50, "andb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x51, "andb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x52, "andb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x53, "andb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x54, "addb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x55, "addb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x56, "addb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x57, "addb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x58, "subb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x59, "subb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x5a, "subb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x5b, "subb",  flds_3op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x5c, "mulub", flds_3op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x5d, "mulub", flds_3op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x5e, "mulub", flds_3op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x5f, "mulub", flds_3op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x60, "and",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x61, "and",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x62, "and",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x63, "and",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x64, "add",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x65, "add",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x66, "add",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x67, "add",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x68, "sub",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x69, "sub",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x6a, "sub",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x6b, "sub",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x6c, "mulu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x6d, "mulu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x6e, "mulu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x6f, "mulu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x70, "andb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x71, "andb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x72, "andb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x73, "andb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x74, "addb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x75, "addb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x76, "addb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x77, "addb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x78, "subb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x79, "subb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x7a, "subb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x7b, "subb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x7c, "mulub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x7d, "mulub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x7e, "mulub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x7f, "mulub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x80, "or",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x81, "or",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x82, "or",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x83, "or",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x84, "xor",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x85, "xor",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x86, "xor",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x87, "xor",   flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x88, "cmp",   flds_2op_waops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x89, "cmp",   flds_2op_waops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x8a, "cmp",   flds_2op_waops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x8b, "cmp",   flds_2op_waops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x8c, "divu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x8d, "divu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x8e, "divu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x8f, "divu",  flds_2op_waopl,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x90, "orb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x91, "orb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x92, "orb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x93, "orb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x94, "xorb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x95, "xorb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x96, "xorb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x97, "xorb",  flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x98, "cmpb",  flds_2op_baops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x99, "cmpb",  flds_2op_baops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x9a, "cmpb",  flds_2op_baops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x9b, "cmpb",  flds_2op_baops,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0x9c, "divub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x9d, "divub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x9e, "divub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0x9f, "divub", flds_2op_baopw,  TGT_PREFIX | TGT_READ ),                      \
    INSTRUCTION_DEF( 0xa0, "ld",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa1, "ld",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa2, "ld",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa3, "ld",    flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa4, "addc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa5, "addc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa6, "addc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa7, "addc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa8, "subc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xa9, "subc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xaa, "subc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xab, "subc",  flds_2op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xac, "ldbze", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xad, "ldbze", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xae, "ldbze", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xaf, "ldbze", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb0, "ldb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb1, "ldb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb2, "ldb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb3, "ldb",   flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb4, "addcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb5, "addcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb6, "addcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb7, "addcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb8, "subcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xb9, "subcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xba, "subcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xbb, "subcb", flds_2op_baop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xbc, "ldbse", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xbd, "ldbse", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xbe, "ldbse", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xbf, "ldbse", flds_2op_baopw,  TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xc0, "st",    flds_2op_waops,  TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xc1, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xc2, "st",    flds_2op_waops,  TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xc3, "st",    flds_2op_waops,  TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xc4, "stb",   flds_2op_baops,  TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xc5, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xc6, "stb",   flds_2op_baops,  TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xc7, "stb",   flds_2op_baops,  TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xc8, "push",  flds_1op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xc9, "push",  flds_1op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xca, "push",  flds_1op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xcb, "push",  flds_1op_waop,   TGT_READ ),                                   \
    INSTRUCTION_DEF( 0xcc, "pop",   flds_1op_waop,   TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xcd, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xce, "pop",   flds_1op_waop,   TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xcf, "pop",   flds_1op_waop,   TGT_WRITE ),                                  \
    INSTRUCTION_DEF( 0xd0, "jnst",  flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd1, "jnh",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd2, "jgt",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd3, "jnc",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd4, "jnvt",  flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd5, "jnv",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd6, "jge",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd7, "jne",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd8, "jst",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xd9, "jh",    flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xda, "jle",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xdb, "jc",    flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xdc, "jvt",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xdd, "jv",    flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xde, "jlt",   flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xdf, "je",    flds_jmp,        TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xe0, "djnz",  flds_djnz,       TGT_EXECUTION_JUMP ),                         \
    INSTRUCTION_DEF( 0xe1, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xe2, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xe3, "br",    flds_wordreg,    TGT_EXECUTION_BARRIER ),                      \
    INSTRUCTION_DEF( 0xe4, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xe5, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xe6, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xe7, "ljmp",  flds_lcall_ljmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_BARRIER ), \
    INSTRUCTION_DEF( 0xe8, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xe9, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xea, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xeb, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xec, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xed, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xee, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xef, "lcall", flds_lcall_ljmp, TGT_EXECUTION_JUMP | TGT_EXECUTION_CALL ),    \
    INSTRUCTION_DEF( 0xf0, "ret",   flds_intrinsic,  TGT_EXECUTION_BARRIER ),                      \
    INSTRUCTION_DEF( 0xf1, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xf2, "pushf", flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xf3, "popf",  flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xf4, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xf5, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xf6, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xf7, "trap",  flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xf8, "clrc",  flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xf9, "setc",  flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xfa, "di",    flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xfb, "ei",    flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xfc, "clrvt", flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xfd, "nop",   flds_intrinsic,  0 ),                                          \
    INSTRUCTION_DEF( 0xfe, NULL,    NULL,            TGT_INVALID ),                                \
    INSTRUCTION_DEF( 0xff, "rst",   flds_intrinsic,  TGT_EXECUTION_BARRIER ),
