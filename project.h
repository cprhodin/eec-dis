#ifndef _PROJECT_H
#define _PROJECT_H

typedef unsigned int uint_t;

#define MAX_INSTR_FIELDS 7

#define min(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define max(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define LSB_MASK(a) ((0x1 << (a)) - 1)
#define swap16(a) ((((a) >> 8) & 0xff) | (((a) & 0xff) << 8))

extern uint_t address_column;
extern uint_t dump_column;
extern uint_t label_column;
extern uint_t mnemonic_column;
extern uint_t parameter_column;

extern uint_t display_column;

#define SET_DISPLAY_COLUMN(a) (display_column += printf("%*.*s", (a) - display_column, (a) - display_column, ""))

#endif // _PROJECT_H
