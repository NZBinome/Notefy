//
//  midieotevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "midieotevent.h"
#include <stdio.h>

int MidiEOTEvent::collectData(unsigned char *buff)
{
    printf("end of track :%d,\n",length());
    return 1;
}

int MidiEOTEvent::writeAData(unsigned char *buff)
{
    buff[0]=_ME;
    buff[1]=_ME_EOT;
    buff[2]=0x00;
    return 3;
}
