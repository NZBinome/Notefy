#include "util.h"
#include <stdio.h>
Util::Util()
{
}

void Util::tri(double *tab, int s, int e, int n)
{
    int m;
    m=part(tab,s,e,n);
    if(s<m-1)
        tri(tab,s,m-1,n);
    if(m<e)
        tri(tab,m,e,n);
}

void Util::swap(double &a, double &b)
{
    if(a!=b)
    {
        b=a-b;
        a=a-b;
        b=a+b;
    }
}

int Util::part(double *tab, int s, int e, int n)
{
    int i=s,j=e;
    double pivot=tab[(j+i)/2];

    while(i<=j)
    {
        while(tab[i]<pivot)
            ++i;
        while(tab[j]>pivot)
            --j;
        if(i<=j)
        {
            swap(tab[i],tab[j]);
            swap(tab[i+n],tab[j+n]);
            ++i;
            --j;
        }
    }

    return i;
}

void Util::triRapideDouble(double *tab, int n)
{
    tri(tab,0,n-1,n);
}
