//
//  midievent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "midinoteevent.h"
#include "miditextevent.h"
#include "midieotevent.h"
#include "miditempoevent.h"
#include "midiprogramchangeevent.h"
#include <stdio.h>

MidiEvent * MidiEvent::createMidiEvent(unsigned char *buff, int &s)
{
    MidiEvent * etr=0;
    
    vlqSize(buff,s);
    
    if ((buff[s]&0xF0)==_NO)
    {
        etr=new MidiNoteEvent();
        etr->_t=_NO;
        etr->setL(buff,s);
        return etr;
    }
    else if((buff[s]&0xF0)==_PC)
    {
        etr=new MidiProgramChangeEvent();
        etr->_t=_PC;
        etr->setL(buff, s);
        return etr;
    }
    else if(buff[s]==_ME)
    {
        ++s;
        if (buff[s]<=_ME_TE)
        {
            etr=new MidiTextEvent();
            etr->setL(buff, s-1);
            etr->_t=_ME_TE;
        }
        else if (buff[s]==_ME_tempo)
        {
            etr=new MidiTempoEvent();
            etr->setL(buff, s-1);
            etr->_t=_ME_tempo;
        }
        else if (buff[s]==_ME_EOT)
        {
            etr=new MidiEOTEvent();
            etr->setL(buff, s-1);
            etr->_t=_ME_EOT;
        }
        return etr;
    }
    return etr;
}

int MidiEvent::length()const
{
    return _l;
}

void MidiEvent::vlqSize(unsigned char * buff, int &s)
{
    s=0;
    while(buff[s++]&0x80)
    {
        //yes this should be empty, don't worry
    }
}

unsigned int MidiEvent::intVlq(unsigned int l)
{
    unsigned int vlq=l&0x7F;
    
    while(l>>=7)
    {
        vlq<<=8;
        vlq|=(l&0x7F)|0x80;
    }
    return vlq;
}

unsigned int MidiEvent::vlqInt(unsigned int vlq)
{
    unsigned int l=vlq&0x7F;
    
    while(vlq&0x80)
    {
        vlq>>=8;
        l<<=7;
        l|=vlq&0x7F;
    }
    return l;
}

unsigned int MidiEvent::ucharVlq(unsigned char *vlqc, int s)
{
    unsigned int v=0;
    for(int i=0;i<s;++i)
    {
        v|=((unsigned int)vlqc[i])<<(8*i);
    }
    return v;
}

void MidiEvent::vlqUchar(unsigned char *vlqc, int &s, unsigned int vlq)
{
    s=0;
    vlqc[s++]=((unsigned char)vlq)&0xFF;
    
    while(vlq>>=8)
    {
        vlqc[s++]=((unsigned char)vlq&0XFF);
    }
}

void MidiEvent::setL(unsigned char *vlq, int s)
{
    _l=vlqInt(ucharVlq(vlq, s));
}

void MidiEvent::quantizeL(int base, int &offset, int &last)
{
    offset+=_l;
    int div=offset/base;
    if (offset-div*base<(div+1)*base-offset)
    {
        _l=div*base;
    }
    else
        _l=(div+1)*base;
    _l-=last;
    last+=_l;
}

unsigned char MidiEvent::type()
{
    return _t;
}

int MidiEvent::collectData(unsigned char *buff)
{
    return 0;
}

int MidiEvent::writeAData(unsigned char *buff)
{
    return 0;
}

int MidiEvent::writeData(unsigned char *buff)
{
    unsigned char vlqc[4];
    int s;
    vlqUchar(vlqc, s, intVlq(length()));
    for (int i=0; i<s; ++i)
    {
        buff[i]=vlqc[i];
    }
    
    s+=writeAData(buff+s);
    return s;
}
