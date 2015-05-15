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

MidiManipulator::MidiManipulator()
{
    _buff=0;
}

void MidiManipulator::open(const char *filename)
{
    _f.open(filename,ios::binary|ios::in|ios::out);
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
        size=Util::swift(size);
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
    _mf=Util::swift(_mf);
    _nt=Util::swift(_nt);
    _tpqn=Util::swift(_tpqn);
}

void MidiManipulator::readBody()
{
    int bs=getToChunk(_MTrk);
    _buff=new unsigned char[bs+bs/5];
    _f.read((char *)_buff, bs);
    unsigned char * b=_buff;
    int s=0;
    do
    {
        _e.push_back(MidiEvent::createMidiEvent(b, s));
        b+=s;
        b+=((MidiEvent *)_e.back())->collectData(b);
    }while(((MidiEvent *)_e.back())->type()!=MidiEvent::_ME_EOT);
}

void MidiManipulator::quantize(int base)
{
    int offset,last=offset=0;
    for(int i=0; i<_e.size(); ++i)
    {
        ((MidiEvent *)_e[i])->quantizeL(base,offset,last);
    }
}

void MidiManipulator::flush(const char * filename)
{
    if (!_f.is_open())
    {
        return;
    }
    int bs=getToChunk(_MTrk);
    unsigned char * b=_buff;
    int s=0;
    
    for (int i=0; i<_e.size(); ++i)
    {
        s=((MidiEvent *)_e[i])->writeData(b);
        b+=s;
    }
    s=b-_buff;
    for(int i=0;i<s;++i)
    {
        printf("%x ",_buff[i]);
    }

    _f.seekp(_f.tellg());
    _f.write((char *)_buff,s);
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
    delete [] _buff;
}
