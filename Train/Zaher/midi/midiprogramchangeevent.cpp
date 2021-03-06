//
//  midiprogramchangeevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "midiprogramchangeevent.h"
#include <stdio.h>

int MidiProgramChangeEvent::collectData(unsigned char *buff)
{
    _inst[0]=buff[0]&0x0F;
    _inst[1]=buff[1];
    printf("Instrument Changed :%u,\n",_inst[1]);
    return 2;
}

int MidiProgramChangeEvent::writeAData(unsigned char *buff)
{
    buff[0]=_inst[0]|_PC;
    buff[1]=_inst[1];
    return 2;
}
