#include "freqtable.h"
#define FH 24
#define FF 38
#define MH 66

Freqtable * Freqtable::single=0;

const double Freqtable::FREQTABLE[NFT]=
{
    16.35,
    17.32,
    18.35,
    19.45,
    20.6,
    21.83,
    23.12,
    24.5,
    25.96,
    27.5,
    29.14,
    30.87,
    32.7,
    34.65,
    36.71,
    38.89,
    41.2,
    43.65,
    46.25,
    49.0,
    51.91,
    55.0,
    58.27,
    61.74,
    65.41,
    69.3,
    73.42,
    77.78,
    82.41,
    87.31,
    92.5,
    98.0,
    103.83,
    110.0,
    116.54,
    123.47,
    130.81,
    138.59,
    146.83,
    155.56,
    164.81,
    174.61,
    185.0,
    196.0,
    207.65,
    220.0,
    233.08,
    246.94,
    261.63,
    277.18,
    293.66,
    311.13,
    329.63,
    349.23,
    369.99,
    392.0,
    415.3,
    440.0,
    466.16,
    493.88,
    523.25,
    554.37,
    587.33,
    622.25,
    659.25,
    698.46,
    739.99,
    783.99,
    830.61,
    880.0,
    932.33,
    987.77,
    1046.5,
    1108.73,
    1174.66,
    1244.51,
    1318.51,
    1396.91,
    1479.98,
    1567.98,
    1661.22,
    1760.0,
    1864.66,
    1975.53,
    2093.0,
    2217.46,
    2349.32,
    2489.02,
    2637.02,
    2793.83,
    2959.96,
    3135.96,
    3322.44,
    3520.0,
    3729.31,
    3951.07,
    4186.01,
    4434.92,
    4698.63,
    4978.03,
    5274.04,
    5587.65,
    5919.91,
    6271.93,
    6644.88,
    7040.0,
    7458.62,
    7902.13
};

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
        single=new Freqtable(FH,MH);
    return single;
}
