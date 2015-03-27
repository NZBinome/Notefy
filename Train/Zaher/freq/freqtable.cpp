#include "freqtable.h"
#define FH 24
#define FF 38

Freqtable * Freqtable::single=0;

Freqtable::Freqtable(int minValue, int maxValue)
{
    _minFreq=minValue;
    _maxFreq=maxValue;
}

int Freqtable::min()
{
    return _minFreq;
}

int Freqtable::max()
{
    return _maxFreq;
}

int Freqtable::find(double freq)
{
    int j,i=j=NFT/2;
    while(FREQTABLE[i]>=freq||FREQTABLE[i+1]<freq)
    {
        j/=2;
        if(j==0)
            j=1;
        if(freq>FREQTABLE[i])
        {
            i+=j;
        }
        else
        {
            i-=j;
        }
    }
    if(freq-FREQTABLE[i]<FREQTABLE[i+1]-freq)
        return i;
    else
        return i+1;
}

void Freqtable::setMax(int maxValue)
{
    _maxFreq=maxValue;
}

void Freqtable::setMin(int minValue)
{
    _minFreq=minValue;
}

void Freqtable::set(int minValue, int maxValue)
{
    _minFreq=minValue;
    _maxFreq=maxValue;
}



Freqtable *Freqtable::getInstance()
{
    if(single==0)
        single=new Freqtable(FH,FF);
    return single;
}
