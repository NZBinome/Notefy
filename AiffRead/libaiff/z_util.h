#ifndef Z_UTIL_H
#define Z_UTIL_H

static inline unsigned int z_BigEndian(unsigned char *b)
{
    return (b[0]<<24)|(b[1]<<16)|(b[2]<<8)|(b[3]);
}

static inline unsigned short z_BigEndian16(unsigned char *b)
{
    return (b[0]<<8)|(b[1]);
}

#endif // Z_UTIL_H
