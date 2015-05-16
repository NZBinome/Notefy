#include <fstream>
#include "../freq/freqtable.h"
#include "../libaiff/libaiff/libaiff.h"
#include "../audioread/aiffread.h"
#include "../wavFormat/diviseur.h"
#include "../signal/complex.h"
#include "../signal/signal.h"
#include "../signal/mixer.h"
#include "../midi/midimanipulator.h"
#include "../midi/note.h"
#include "../signal/melody.h"
#include "../audioread/wavread.h"
#include "../libmel/melfile.h"
#include "../audiowrite/aiffwrite.h"
#include "z_audiomidiconverter.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern const int refTempo;

FileType Z_audioMidiConverter::_z_amc_getFileType(const char *f)
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
    _converter=0;
    _soundfont=0;
    _tempo=100;
}

void Z_audioMidiConverter::melToMid(Melody &m, char* filename)
{
    MidiCreator c(m.fs());
    c.setTempo(_tempo);
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

void Z_audioMidiConverter::setTempo(int tempo)
{
    _tempo=tempo;
}

int Z_audioMidiConverter::convert(char *audioFile, char *midiFile)
{
    const int gw=4; //gauss window
    int n=strlen(audioFile);
    AudioRead *f;

    if(_z_amc_getFileType(audioFile)==WAV)
    {
        f=new Wavread();
        if(!f->open(audioFile))
            return 0;
    }
    else if(_z_amc_getFileType(audioFile)==AIF)
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
            melToMid(m,filename);
        }
        else if (!mf.isQuantized())
        {
            printf("quantizing\n");
            MidiManipulator mm;
            mm.open(filename);
            mm.quantize(50);
            mm.flush(filename);
            mm.close();
            mf.set_dnpqt(0);
        }
        else
        {
            m.incScale();
            mf.choose_cs(m.scaleN());
            melToMid(m,filename);
        }
    }

    mf.flush();

    chooseInstrument(inst,filename);
}

void Z_audioMidiConverter::setConverterPath(const char * p)
{
    _converter=new char[strlen(p)];
    strcpy(_converter, p);
}
void Z_audioMidiConverter::setSoundFontPath(const char * p)
{
    _soundfont=new char[strlen(p)];
    strcpy(_soundfont, p);
}

int Z_audioMidiConverter::iconvert(const char *midiFil, char *midiAltered)
{
    if(_converter==0||_soundfont==0)
    {
        throw "No converter or soundfont selected for midi to audio conversion\n";
    }
    sprintf(midiAltered, "%s.aif" ,midiFil);
    int pid = fork();
    if (pid==0) {
        printf("%s %s -T aiff -F %s %s %s\n",_converter,_converter,midiAltered,_soundfont,midiFil);
        execl(_converter, _converter, "-T", "aiff", "-F", midiAltered, _soundfont, midiFil, NULL);
    }
    int returnStatus;
    waitpid(pid, &returnStatus, 0);
    
    return 1;
}

void Z_audioMidiConverter::mix(const char **f, int n, const char *df)
{
    double vref=0.8;
    AudioRead **af=new AudioRead*[n];
    for(int i=0;i<n;++i)
    {
        FileType ft=_z_amc_getFileType(f[i]);
        char exception[100];
        char midiAltered[256];
        
        switch(ft)
        {
            case AIF:
                af[i]=new AiffRead();
                af[i]->open(f[i]);
                break;
            case WAV:
                af[i]=new Wavread();
                af[i]->open(f[i]);
                break;
            case MID:
                iconvert(f[i],midiAltered);
                af[i]=new AiffRead();
                af[i]->open(midiAltered);
                break;
            default:
                throw "not supported file";
        }
    }
    Signal *s=new Signal[n];
    double maxval=0;
    for(int i=0;i<n;++i)
    {
        s[i].set(af[i]->buffer(),af[i]->fs(),af[i]->l(),af[i]->ba(),af[i]->nc());
    }
    for(int i=0;i<n;++i)
    {
        s[i].mult(vref/s[i].s_max());
    }
    
    Mixer m;
    m.addSignals(s,n);
    Signal *mix;
    mix=m.mix();
    
    AiffWrite aw;
    int ba=2;
    aw.set_l(mix->l()*ba);
    aw.set_fs(mix->fs());
    aw.set_ba(ba);
    aw.set_buffer(mix->rawData(ba));

    printf("%s\n",df);
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
    delete [] _converter;
    delete [] _soundfont;
}
