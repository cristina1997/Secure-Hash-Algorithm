/* UNION
** - represents a message block
** - used to read file in blocks of 512 bits
** - like structures (structs)
** - can only store one value at a time
** - stored in the same location.
** - used in variables related to each other
**   that might have different types.
*/
union msgBlock{
    uint8_t  e[64];                                   // 8  bits(type) * 64 = 512
    uint32_t t[16];                                   // 32 bits(type) * 16 = 512
    uint64_t s[8];                                    // 64 bits(type) * 8  = 512
};