#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "project.h"
#include "bitfield.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// extract an arbitrarily aligned bitfield of up to 32 bits
//
//         Low address ---------------------------- High address
//
//         76543210:76543210:76543210:76543210:76543210:76543210
//
// offset: 00000000 00111111 11112222 22222233 33333333 44444444
//         01234567 89012345 67890123 45678901 23456789 01234567
//
////////////////////////////////////////////////////////////////////////////////////////////////////

bitfield_t get_bitfield(uint8_t * address, uint_t offset, uint_t width)
{
    bitfield_t bitfield = 0;

    if (width > sizeof(bitfield) * CHAR_BIT)
    {
        fprintf(stderr, "\n\nFATAL ERROR: get_bitfield(), invalid width\n");
        exit(1);
    }

    // adjust address and offset to reference the first byte with bits from the bitfield
    address += offset / CHAR_BIT;
    offset %= CHAR_BIT;

    // retrieve the bitfield
    while (width)
    {
        uint_t width_in_byte = min(width, CHAR_BIT - offset);

        bitfield <<= width_in_byte;
        bitfield |= (*address++ >> (CHAR_BIT - offset - width_in_byte)) & LSB_MASK(width_in_byte);

        offset = 0;
        width -= width_in_byte;
    }

    return bitfield;
}

void set_bitfield(uint8_t * address, uint_t offset, uint_t width, bitfield_t bitfield)
{
    if (width > sizeof(bitfield) * CHAR_BIT)
    {
        fprintf(stderr, "\n\nFATAL ERROR: get_bitfield(), invalid width\n");
        exit(1);
    }

    // adjust address and offset to reference the first byte with bits from the bitfield
    address += offset / CHAR_BIT;
    offset %= CHAR_BIT;

    // set the bitfield
    while (width)
    {
        bitfield_t bits_in_byte;
        bitfield_t mask_in_byte;
        uint_t width_in_byte = min(width, CHAR_BIT - offset);

        mask_in_byte = LSB_MASK(width_in_byte) << (CHAR_BIT - width_in_byte - offset);

        bits_in_byte = bitfield >> (width - width_in_byte);
        bits_in_byte <<= CHAR_BIT - width_in_byte - offset;
        bits_in_byte &= mask_in_byte;

        bits_in_byte |= *address & ~mask_in_byte;
        *address++ = bits_in_byte;

        offset = 0;
        width -= width_in_byte;
    }
}
