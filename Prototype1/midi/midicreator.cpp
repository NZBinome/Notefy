#include <vector>
#include "note.h"
#include "midicreator.h"

#include <fstream>

#include <QDebug>

using namespace std;

MidiCreator::MidiCreator(int fs)
{
    double t=1.0/fs;        //un echantillon fait t seconde
    _fdt=t*2*_dt;           //une note de longueur t fait _fdt tick
}

void MidiCreator::addNote(Note n)
{
    if(_n.size()==0)
    {
        _n.push_back(n);
        return;
    }

    if(_n.back().n()==n.n())
    {
        if(_n.back().v()>=n.v())
            _n.back().inc_d(n.d());
    }
    else
    {
        _n.push_back(n);
    }
}

int MidiCreator::sizeData(char *&c)
{
    c=new char[1000];
    int sd=0;
    for(int i=0;i<_n.size();++i)
    {
        int s;
        memcpy(c+sd,((Note)_n[i]).toMidiMessage(s,_fdt,0),11);
        sd+=s;
    }
    return sd;
}

void MidiCreator::creerMidiFile(char *name)
{
    fstream f;
    f.open(name,ios::out|ios::binary);

    //on ecrit le header du fichier
    char ch[]="MThd";
    f.write(ch,4*sizeof(char));

    //la taille du header
    int data=6;
    unsigned char c;
    c=(unsigned char)((data>>24)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data>>16)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data>>8)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data)&0xFF);
    f.write((char*)&c,sizeof(char));

    //le format du fichier
    data=0;
    c=(unsigned char)((data>>8)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data)&0xFF);
    f.write((char*)&c,sizeof(char));

    //le nombre de track
    data=1;
    c=(unsigned char)((data>>8)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data)&0xFF);
    f.write((char*)&c,sizeof(char));

    //le nombre de tick par noire
    data=_dt;
    c=(unsigned char)((data>>8)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data)&0xFF);
    f.write((char*)&c,sizeof(char));

    char ch2[]="MTrk";
    f.write(ch2,4*sizeof(char));

    //la taille du MIDI data
    char *d=0;
    data=sizeData(d)+4;
    c=(unsigned char)((data>>24)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data>>16)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data>>8)&0xFF);
    f.write((char*)&c,sizeof(char));
    c=(unsigned char)((data)&0xFF);
    f.write((char*)&c,sizeof(char));

    f.write(d,(data-4)*sizeof(char));

    if(d!=0)
        delete []d;

    unsigned char eot[4] = {0, 0xff, 0x2f, 0x00};
    f.write((char*)eot,sizeof(char));
    f.write((char*)eot+1,sizeof(char));
    f.write((char*)eot+2,sizeof(char));
    f.write((char*)eot+3,sizeof(char));

    f.close();
}
