//
//  midinoteevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "midinoteevent.h"
#include <stdio.h>

int MidiNoteEvent::collectData(unsigned char * buff)
{
    printf("Note On: ");

    _data[0]=buff[0]&0x0F; //midi Channel
    _data[1]=buff[1];      //note launched
    _data[2]=buff[2];      //velocity

    printf("length %d, note %u, vel %u,\n",length(),_data[1],_data[2]);

    return 3;
}

int MidiNoteEvent::writeAData(unsigned char *buff)
{
    buff[0]=_data[0]|_NO;
    buff[1]=_data[1];
    buff[2]=_data[2];
    return 3;
}
