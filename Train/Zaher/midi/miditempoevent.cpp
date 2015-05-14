//
//  miditempoevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "miditempoevent.h"
#include <stdio.h>

int MidiTempoEvent::collectData(unsigned char *buff)
{
    _tempo=0;
    _tempo|=(((int)buff[2])<<16)&0x00FF0000;
    _tempo|=(((int)buff[3])<<8)&0x0000FF00;
    _tempo|=((int)buff[4])&0x000000FF;
    printf("tempo : %d,\n", _tempo);
    return 5;
}

int MidiTempoEvent::writeAData(unsigned char *buff)
{
    buff[0]=_ME;
    buff[1]=_ME_tempo;
    buff[2]=0x03;
    buff[3]=(unsigned char)(_tempo>>16);
    buff[4]=(unsigned char)(_tempo>>8);
    buff[5]=(unsigned char)_tempo;
    return 6;
}
