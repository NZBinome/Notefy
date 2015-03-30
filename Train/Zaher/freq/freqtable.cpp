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
    if(freq/FREQTABLE[i]<FREQTABLE[i+1]/freq)
        return i;
    else
        return i+1;
}

bool Freqtable::inScale(int ind, int scale)
{
    const int MAJORSCALE[]={0, 2, 4, 5, 7, 9, 11};
    int pos=(ind-scale)%12;
    for(int i=0;i<7;++i)
    {
        if(pos==MAJORSCALE[i])
        {
            return true;
        }
    }
    return false;
}


int Freqtable::find(double freq, int scale, double *diff)
{

    int iFreq=find(freq);
    if(inScale(iFreq,scale))
    {
        if(diff!=0)
            *diff=FREQTABLE[iFreq]/freq;
        return iFreq;
    }
    if(freq/FREQTABLE[iFreq-1]<FREQTABLE[iFreq+1]/freq)
    {
        if(diff!=0)
            *diff=FREQTABLE[iFreq-1]/freq;
        return iFreq-1;
    }
    else
    {
        if(diff!=0)
            *diff=FREQTABLE[iFreq+1]/freq;
        return iFreq+1;
    }
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
