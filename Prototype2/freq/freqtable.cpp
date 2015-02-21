#include "freqtable.h"

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
        single=new Freqtable(24,60);
    return single;
}
