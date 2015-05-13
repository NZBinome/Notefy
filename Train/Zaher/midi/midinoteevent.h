//
//  midinoteevent.h
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__midinoteevent__
#define __Train__midinoteevent__

#include "midievent.h"

class MidiNoteEvent : public MidiEvent
{
    unsigned char _data[3];
    
public:
    
    int collectData(unsigned char * buff);
};

#endif /* defined(__Train__midinoteevent__) */
