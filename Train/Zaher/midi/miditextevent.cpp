//
//  miditextevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "miditextevent.h"
#include "string.h"

int MidiTextEvent::collectData(unsigned char *buff)
{
    int s;
    _t=buff[0];
    ++buff;
    vlqSize(buff, s);
    _len=vlqInt(ucharVlq(buff, s));
    _text=new char [_len];
    memcpy(_text, buff+s, _len);
    return 1+s+_len;
}

int MidiTextEvent::writeAData(unsigned char *buff)
{
    buff[0]=_t;
    ++buff;
    unsigned char vlqc[4];
    int s;
    vlqUchar(vlqc,s,_len);
    for(int i=0;i<s;++i)
    {
        buff[i]=vlqc[i];
    }
    memcpy(buff+s,_text, _len);
    return 1+s+_len;
}
