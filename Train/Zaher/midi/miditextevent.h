//
//  miditextevent.h
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__miditextevent__
#define __Train__miditextevent__

#include "midievent.h"

class MidiTextEvent : public MidiEvent
{
    unsigned int _len;
    char * _text;
public:
    int collectData(unsigned char *buff);
    int writeAData(unsigned char *buff);
};

#endif /* defined(__Train__miditextevent__) */
