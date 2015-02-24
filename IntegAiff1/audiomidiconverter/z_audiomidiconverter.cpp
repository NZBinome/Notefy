#include "freq/freqtable.h"
#include "libaiff/libaiff/libaiff.h"
#include "AudioRead/aiffread.h"
#include "wavFormat/diviseur.h"
#include "signal/complex.h"
#include "signal/signal.h"
#include "midi/note.h"
#include "midi/midicreator.h"
#include "signal/melody.h"
#include "z_audiomidiconverter.h"
#include <string.h>


Z_audioMidiConverter::Z_audioMidiConverter()
{
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

    _c=new MidiCreator(f.fs());

    Note n;

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());
        m.append(s.fc(),s.p());
    }

    m.filtreBilateral(gw);

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

Z_audioMidiConverter::~Z_audioMidiConverter()
{
    if(_c!=0)
        delete _c;
}

void Z_audioMidiConverter::chooseInstrument(unsigned char inst)
{
    _c->chooseInstrument(inst);
}
