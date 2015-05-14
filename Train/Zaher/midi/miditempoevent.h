//
//  miditempoevent.h
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__miditempoevent__
#define __Train__miditempoevent__

#include "midievent.h"

class MidiTempoEvent : public MidiEvent
{
    unsigned int _tempo;
public:
    int collectData(unsigned char * buff);
    int writeAData(unsigned char * buff);
};

#endif /* defined(__Train__miditempoevent__) */
