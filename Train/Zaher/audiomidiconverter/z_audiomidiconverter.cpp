#include <fstream>
#include "../freq/freqtable.h"
#include "../libaiff/libaiff/libaiff.h"
#include "../AudioRead/aiffread.h"
#include "../wavFormat/diviseur.h"
#include "../signal/complex.h"
#include "../signal/signal.h"
#include "../midi/note.h"
#include "../midi/midicreator.h"
#include "../signal/melody.h"
#include "z_audiomidiconverter.h"
#include <string.h>


Z_audioMidiConverter::Z_audioMidiConverter()
{
    _c=0;
}

int Z_audioMidiConverter::convert(char *audioFile, char *midiFile)
{
    const int gw=4; //gauss window


    AiffRead f;
    if(!f.open(audioFile))
        return 0;
    Diviseur d(f.buffer(),f.l(),f.fs(),f.ba(),f.nc());

    Signal s;

    Melody m(d.d());


    

    Note n;

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());
        m.append(s.fc(),s.p());
    }

    m.filtreBilateral(gw);

    int ftd=0;
    while(1)
    {
        if(audioFile[ftd]!='.')
        {
            midiFile[ftd]=audioFile[ftd];
            ++ftd;
        }
        else
        {
            midiFile[ftd]='.';
            midiFile[ftd+1]='m';
            midiFile[ftd+2]='e';
            midiFile[ftd+3]='l';
            midiFile[ftd+4]=0;
            break;
        }
    }

    //m.writeToFile(midiFile);

    _c=new MidiCreator(f.fs());
    for(int i=0;i<d.d();++i)
    {
        double v[2];
        m.valueAt(i,v);
        n.findNote(v[0]);
        n.findVolume(v[1]);
        //printf("%f  %f\n",s.fc(),s.p());
        n.set_d(s.l());

        _c->addNote(n);
    }

    midiFile[ftd]='.';
    midiFile[ftd+1]='m';
    midiFile[ftd+2]='i';
    midiFile[ftd+3]='d';
    midiFile[ftd+4]=0;

    printf("name, %s\n",midiFile);
    _c->creerMidiFile(midiFile);
    return 1;
}

unsigned short Z_audioMidiConverter::getInstrument(char * filename)
{
    std::fstream f;
    f.open(filename,std::ios::in|std::ios::binary);
    f.seekg(22,std::ios::beg);
    char c[3];
    f.read(c,3*sizeof(char));
    f.close();
    return c[2];
}

void Z_audioMidiConverter::chooseInstrument(unsigned char inst, char * filename)
{
    //_c->chooseInstrument(inst);
    std::fstream f;
    f.open(filename,std::ios::in|std::ios::out|std::ios::binary);
    f.seekp(22,std::ios::beg);
    char c[3];
    c[0]=0;
    c[1]=192;
    c[2]=inst;
    f.write(c,3*sizeof(char));
    f.close();
}

void Z_audioMidiConverter::fix(char *filename)
{
    int ftd=0;
    while(1)
    {
        if(filename[ftd]='.')
        {
            filename[ftd]='.';
            filename[ftd+1]='m';
            filename[ftd+2]='e';
            filename[ftd+3]='l';
            filename[ftd+4]=0;
            break;
        }
    }
    Melody m(0);
    m.readFromFile(filename);
}

Z_audioMidiConverter::~Z_audioMidiConverter()
{
    if(_c!=0)
        delete _c;
}
