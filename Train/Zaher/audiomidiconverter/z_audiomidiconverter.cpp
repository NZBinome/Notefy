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

    int i=0;
    while(1)
    {
        if(audioFile[i]!='.')
        {
            midiFile[i]=audioFile[i];
            ++i;
        }
        else
        {
            midiFile[i]='.';
            midiFile[i+1]='m';
            midiFile[i+2]='i';
            midiFile[i+3]='d';
            midiFile[i+4]=0;
            break;
        }
    }

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

Z_audioMidiConverter::~Z_audioMidiConverter()
{
    if(_c!=0)
        delete _c;
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
