//
//  midiprogramchangeevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "midiprogramchangeevent.h"


int MidiProgramChangeEvent::collectData(unsigned char *buff)
{
    _inst[0]=buff[0]&0x0F;
    _inst[1]=buff[1];
    return 2;
}