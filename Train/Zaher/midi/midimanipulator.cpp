//
//  MidiManipulator.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "midimanipulator.h"
#include "../util/util.h"

using namespace std;

void MidiManipulator::open(const char *filename)
{
    _f.open(filename,ios::binary|ios::in);
    if(!verifyChunk(_MThd, 0))
        return;
    readHeader();
    readBody();
    
}

bool MidiManipulator::verifyChunk(const int cid, int pos)
{
    int rcid;
    _f.seekp(pos);
    _f.read((char *)&rcid, 4);
    if(cid==rcid)
        return true;
    return false;
}

int MidiManipulator::getToChunk(const int cid)
{
    if(!_f.is_open())
        return -1;
    int size=0;
    int fcid;
    _f.seekg(0,ios::beg);
    do
    {
        _f.seekg(size,ios::cur);
        _f.read((char*)&fcid,sizeof(int));
        _f.read((char*)&size,sizeof(int));
        if(_f.eof())
            return 0;
    }while(fcid!=cid);
    
    return size;
}

void MidiManipulator::readHeader()
{
    getToChunk(_MThd);
    _f.read((char *)&_mf, 2);
    _f.read((char *)&_nt, 2);
    _f.read((char *)&_tpqn, 2);
}

void MidiManipulator::readBody()
{
    int bs=getToChunk(_MTrk);
    unsigned char * buff=new unsigned char[bs];
    int s=0;
    do
    {
        _e.push_back(MidiEvent::createMidiEvent(buff, s));
        buff+=s;
        buff+=((MidiEvent *)_e.back())->collectData(buff);
    }while(((MidiEvent *)_e.back())->type()==MidiEvent::_ME_EOT);
}

void MidiManipulator::close()
{
    _f.close();
}

MidiManipulator::~MidiManipulator()
{
    if (_f.is_open())
    {
        _f.close();
    }
}