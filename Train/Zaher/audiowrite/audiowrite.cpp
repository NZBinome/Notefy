#include "audiowrite.h"

AudioWrite::AudioWrite()
{
    _b=0;
    _l=0;
    _fs=0;
    _ba=0;
    _nc=1;
}

void AudioWrite::set_buffer(unsigned char *buffer)
{
    _b=buffer;
}

void AudioWrite::set_fs(int fs)
{
    _fs=fs;
}

void AudioWrite::set_l(int l)
{
    _l=l;
}

void AudioWrite::set_ba(int ba)
{
    _ba=ba;
}

AudioWrite::~AudioWrite()
{
    if(_b==0)
    {
        delete [] _b;
    }
}
