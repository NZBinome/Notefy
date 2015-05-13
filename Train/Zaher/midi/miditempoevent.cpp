//
//  miditempoevent.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "miditempoevent.h"

int MidiTempoEvent::collectData(unsigned char *buff)
{
    _tempo=vlqInt(ucharVlq(buff+1, 3));
    return 4;
}