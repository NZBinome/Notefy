//
//  midieotevent.h
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__midieotevent__
#define __Train__midieotevent__

#include "midievent.h"

class MidiEOTEvent : public MidiEvent
{
public:
    int collectData(unsigned char * buff);
};

#endif /* defined(__Train__midieotevent__) */
