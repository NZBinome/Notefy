#ifndef Z_UTIL_H
#define Z_UTIL_H

static inline unsigned int z_BigEndian(unsigned char *b)
{
    return (b[0]<<24)|(b[1]<<16)|(b[2]<<8)|(b[3]);
}

static inline unsigned int z_BigEndianI(int b)
{
    return ((b>>24)&0x000000ff)|((b>>8)&0x0000ff00)|((b<<8)&0x00ff0000)|((b<<24)&0xff000000);
}

static inline unsigned short z_BigEndian16(unsigned char *b)
{
    return (b[0]<<8)|(b[1]);
}

static inline unsigned int z_BigEndian16I(short b)
{
    return ((b>>8)&0x00ff)|((b<<8)&0xff00);
}

#endif // Z_UTIL_H
