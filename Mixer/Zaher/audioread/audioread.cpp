#include "audioread.h"
#include "stdio.h"

AudioRead::AudioRead()
{
    _b=0;
    _l=0;
    _fs=0;
    _ba=0;
    _nc=0;
}

unsigned char * AudioRead::buffer()
{
    return _b;
}

int AudioRead::fs()
{
    return _fs;
}

int AudioRead::ba()
{
    return _ba;
}

int AudioRead::nc()
{
    return _nc;
}

int AudioRead::l()
{
    return _l;
}

AudioRead::~AudioRead()
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
