#include "diviseur.h"
#include <stdio.h>

Diviseur::Diviseur(unsigned char * b, int l, int fs, int ba, int nc)
{
    _b=b;
    _l=l;
    ++_b[_l]; //cet objet partage ce tableau, on incremente les liens
    _fs=fs;
    _ba=ba;
    _nc=nc;
    _ld=1;
    while(_ld<_fs/10)
    {
        _ld*=2;
    }
    _ld*=_ba;
    _d=_l/_ld;
}

int Diviseur::d()
{
    return _d;
}

int Diviseur::ld()
{
    return _ld;
}

unsigned char * Diviseur::operator [](int i)
{
    if((i+1)*_ld>_l)
        return 0;
    return _b+i*_ld;
}

Diviseur::~Diviseur()
{
    if(_b!=0)
    {
        if((--_b[_l])==0) //on decremente les liens vers ce tableau
        {
            delete [] _b;
            _b=0;
        }
    }
}
