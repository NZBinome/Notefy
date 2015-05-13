//
//  MidiManipulator.h
//  Train
//
//  Created by Zaher Hamadeh on 5/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__MidiManipulator__
#define __Train__MidiManipulator__

#include <vector>
#include <fstream>
#include "midievent.h"

class MidiManipulator
{
    static const int _MThd=0x6468544d;
    static const int _MTrk=0x6b72544d;
    
    
    std::vector<MidiEvent *> _e;
    std::fstream _f;
    
    short _mf;  //midi format
    short _nt;  //number of tracks
    short _tpqn;//ticks per quarter notes
    
    bool verifyChunk(const int cid, int pos);  //use s to jump to end of c
    int getToChunk(const int cid);
    
public:
    
    void open(const char * filename);
    void readHeader();
    void readBody();
    void quantize(int base);
    void close();
    ~MidiManipulator();
};


#endif /* defined(__Train__MidiManipulator__) */
