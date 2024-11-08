#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "project.h"
#include "tgt_memory.h"

uint8_t * tgt_memory;

uint32_t tgt_byteread(uint32_t tgt_addr)
{
    if (tgt_addr > 0x0000ffff)
    {
        printf("\n\nFATAL ERROR: get_bitfield(), invalid address\n");
        exit(1);
    }

    return tgt_memory[tgt_addr];
}


uint32_t tgt_wordread(uint32_t tgt_addr)
{
    if (tgt_addr > 0x0000fffe)
    {
        printf("\n\nFATAL ERROR: get_bitfield(), invalid address\n");
        exit(1);
    }

    return tgt_memory[tgt_addr] | (tgt_memory[tgt_addr + 1] << 8);
}
