#include <fstream>
#include "../freq/freqtable.h"
#include "../libaiff/libaiff/libaiff.h"
#include "../audioread/aiffread.h"
#include "../wavFormat/diviseur.h"
#include "../signal/complex.h"
#include "../signal/signal.h"
#include "../midi/note.h"
#include "../signal/melody.h"
#include "../audioread/wavread.h"
#include "z_audiomidiconverter.h"
#include <string.h>


Z_audioMidiConverter::Z_audioMidiConverter()
{
}

void Z_audioMidiConverter::melToMid(Melody &m, char* filename)
{
    MidiCreator c(m.fs());
    Note n;
    for(int i=0;i<m.n();++i)
    {
        double v[2];
        m.valueAt(i,v);
        n.findNote(v[0],m.scale());
        n.findVolume(v[1]);
        n.set_d(m.l());
        c.addNote(n);
    }
    c.creerMidiFile(filename);
}

int Z_audioMidiConverter::convert(char *audioFile, char *midiFile)
{
    const int gw=4; //gauss window
    int n=strlen(audioFile);
    AudioRead *f;

    if(audioFile[n-3]=='w'&&audioFile[n-2]=='a'&&audioFile[n-1]=='v')
    {
        f=new Wavread();
        if(!f->open(audioFile))
            return 0;
    }
    else if((audioFile[n-3]=='a'&&audioFile[n-2]=='i'&&audioFile[n-1]=='f'))
    {
        f=new AiffRead();
        if(!f->open(audioFile))
            return 0;
    }
    else
        return 0;

    Diviseur d(f->buffer(),f->l(),f->fs(),f->ba(),f->nc());

    Signal s;

    Melody m(d.d(),f->fs());

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f->fs(),d.ld(),f->ba(),f->nc());
        m.append(s.fc(),s.p());
    }

    delete f;

    m.set_l(s.l());

    m.filtreBilateral(gw);
    m.normalize();

    strcpy(midiFile,audioFile);
    midiFile[n-3]='m';
    midiFile[n-2]='e';
    midiFile[n-1]='l';
    midiFile[n]=0;

    m.setScales();
    m.writeToFile(midiFile);

    midiFile[n-3]='m';
    midiFile[n-2]='i';
    midiFile[n-1]='d';
    midiFile[n]=0;

    melToMid(m,midiFile);

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

void Z_audioMidiConverter::fix(char *filename, bool deFix)
{
    char melfile[100];
    int n=strlen(filename);

    strcpy(melfile,filename);

    short inst=getInstrument(filename);

    melfile[n-3]='m';
    melfile[n-2]='e';
    melfile[n-1]='l';
    melfile[n]=0;

    Melody m(0,0);
    m.readFromFile(melfile);
    if(deFix)
        m.deFix();
    else
        m.incScale();
    melToMid(m,filename);
    m.writeToFile(melfile);

    chooseInstrument(inst,filename);
}

Z_audioMidiConverter::~Z_audioMidiConverter()
{
}
