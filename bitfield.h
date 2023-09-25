#ifndef _BITFIELD_H
#define _BITFIELD_H

#define bitfield_t uint32_t

extern bitfield_t get_bitfield(uint8_t * address, uint_t offset, uint_t width);
extern void set_bitfield(uint8_t * address, uint_t offset, uint_t width, bitfield_t bitfield);

#endif // _BITFIELD_H
