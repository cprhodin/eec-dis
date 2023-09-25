#ifndef _MEMORY_H
#define _MEMORY_H

extern uint8_t tgt_memory[];

extern uint32_t tgt_byteread(uint32_t tgt_addr);
extern uint32_t tgt_wordread(uint32_t tgt_addr);

#define tgt_address(a) (&tgt_memory[a])

#endif // _MEMORY_H
