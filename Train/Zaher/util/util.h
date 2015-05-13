#ifndef UTIL_H
#define UTIL_H

class Util
{
    static void tri(double *tab, int s, int e, int n);
    static int part(double *tab, int s, int e, int n);
public:
    Util();
    static void triRapideDouble(double *tab, int n);
    static void swap(double &a, double &b);
    
    static inline int swift(int b)
    {
        return ((b>>24)&0x000000ff)|((b>>8)&0x0000ff00)|((b<<8)&0x00ff0000)|((b<<24)&0xff000000);
    }
};

#endif // UTIL_H
