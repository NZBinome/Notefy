#include "note.h"
#include "freq/freqtable.h"


Note::Note()
{
    _d=0;
    _n=0;
    _v=0;
}

void Note::set_d(int d)
{
    _d=d;
}

void Note::inc_d(int d)
{
    _d+=d;
}

void Note::findNote(double f)
{
    Freqtable * freq=Freqtable::getInstance();
    _n=freq->find(f);

    //juste hek
    _n+=12;
}

void Note::findVolume(double p)
{
    if(p>127)
        p=127;
    if(p<18)
        p=0;
    _v=p;
}

void Note::setNote(unsigned char note)
{
    _n=note;
}


int Note::d()
{
    return _d;
}

unsigned char Note::n()
{
    return _n;
}

unsigned char Note::v()
{
    return _v;
}

unsigned char * Note::toMidiMessage(int &s,double t,short int c)
{
    unsigned int vlq;   //variable lenght quantity

    int d=_d*t;

    vlq=d&0x7F;
    s=1;            //nombre de byte pour la vlq
    while(d>>=7)
    {
        vlq<<=8;
        vlq|=((d&0x7F)|0x80);
        ++s;
    }
    unsigned char vlqc[4];
    for(int i=0;i<s;++i)
    {
        vlqc[i]=vlq>>(i*8)&0xFF;
    }

    char com=0x90|(c&0x0F);

    unsigned char m[11];

    m[0]=0;m[1]=com;m[2]=_n;m[3]=_v;
    int i;
    for(i=4;i<s+4;++i)
    {
        m[i]=vlqc[i-4];
    }
    m[i++]=com;m[i++]=_n;m[i++]=0;
    s+=7;

    return m;
}
