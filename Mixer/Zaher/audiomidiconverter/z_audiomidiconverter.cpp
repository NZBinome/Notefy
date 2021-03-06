#include <fstream>
#include "../freq/freqtable.h"
#include "../libaiff/libaiff/libaiff.h"
#include "../audioread/aiffread.h"
#include "../wavFormat/diviseur.h"
#include "../signal/complex.h"
#include "../signal/signal.h"
#include "../signal/mixer.h"
#include "../midi/note.h"
#include "../signal/melody.h"
#include "../audioread/wavread.h"
#include "../libmel/melfile.h"
#include "../audiowrite/aiffwrite.h"
#include "z_audiomidiconverter.h"
#include <string.h>


enum FileType{
    MID,
    AIF,
    WAV,
    INV
};

inline FileType _z_amc_getFileTye(char *f)
{
    int n=strlen(f);
    char end[4];
    for(int i=0;i<4;++i)
    {
        end[i]=f[n+i-4];
    }
    if(end[0]=='.')
    {
        if(end[1]=='m'&&end[2]=='i'&&end[3]=='d')
            return MID;
        else if(end[1]=='a'&&end[2]=='i'&&end[3]=='f')
            return AIF;
        else if(end[1]=='w'&&end[3]=='a'&&end[3]=='v')
            return WAV;
    }
    return INV;
}

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

    if(_z_amc_getFileTye(audioFile)==WAV)
    {
        f=new Wavread();
        if(!f->open(audioFile))
            return 0;
    }
    else if(_z_amc_getFileTye(audioFile)==AIF)
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

    strcpy(midiFile,audioFile);
    midiFile[n-3]='m';
    midiFile[n-2]='e';
    midiFile[n-1]='l';
    midiFile[n]=0;

    m.setScales();

    MelFile mf;
    mf.getFrom(m);
    mf.create(midiFile);

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
    char melfile[256];
    int n=strlen(filename);

    strcpy(melfile,filename);

    short inst=getInstrument(filename);

    melfile[n-3]='m';
    melfile[n-2]='e';
    melfile[n-1]='l';
    melfile[n]=0;

    Melody m;
    MelFile mf;
    mf.manipulate(melfile);
    mf.getInfo();
    mf.getFreq();
    mf.getScal();
    mf.getCoqa();

    mf.writeTo(m);

    if(deFix)
        m.deFix();
    else
    {
        if(!mf.isCorrected())
        {
            m.decompose();
            mf.set_dft_dnp_dnpqt(m.correct(),m.distPlace(),0,m.distNum());
        }
        else
        {
            m.incScale();
            mf.choose_cs(m.scaleN());
        }
    }

    melToMid(m,filename);
    mf.flush();

    chooseInstrument(inst,filename);
}


void Z_audioMidiConverter::mix(const char **f, int n, const char *df)
{
    AudioRead **af=new AudioRead*[n];
    for(int i=0;i<n;++i)
    {
        switch(_z_amc_getFileTye(f[i]))
        {
            case AIF:
                af[i]=new AiffRead();
                break;
            case WAV:
                af[i]=new Wavread();
                break;
            case MID:
                throw("not suported yet");
            default:
                throw("not supported files");
        }
    }
    Signal *s=new Signal[n];
    for(int i=0;i<n;++i)
    {
        af[i]->open(f[i]);
        s[i].set(af[i]->buffer(),af[i]->fs(),af[i]->l(),af[i]->ba(),af[i]->nc());
    }
    Mixer m;
    m.addSignals(s,n);
    Signal *mix=m.mix();

    AiffWrite aw;
    int ba=2;
    aw.set_l(mix->l()*ba);
    aw.set_fs(mix->fs());
    aw.set_ba(ba);
    aw.set_buffer(mix->rawData(ba));

    aw.write(df);
    delete [] s;
    for(int i=0;i<n;++i)
    {
        delete af[i];
    }
    delete [] af;
}

Z_audioMidiConverter::~Z_audioMidiConverter()
{
}
