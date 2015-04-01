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
};

#endif // UTIL_H
