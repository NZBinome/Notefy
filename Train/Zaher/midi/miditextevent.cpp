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
    vlqSize(buff, s);
    _len=vlqInt(ucharVlq(buff, s));
    _text=new char [_len];
    memcpy(_text, buff+s, _len);
    return s+_len;
}