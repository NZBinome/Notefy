//
//  midiprogramchangeevent.h
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__midiprogramchangeevent__
#define __Train__midiprogramchangeevent__

#include "midievent.h"

class MidiProgramChangeEvent : public MidiEvent
{
    unsigned char _inst[2];
public:
    int collectData(unsigned char * buff);
    int writeAData(unsigned char *buff);
};

#endif /* defined(__Train__midiprogramchangeevent__) */
