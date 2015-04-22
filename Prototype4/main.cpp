#include "../Train/Zaher/signal/melody.h"
#include "../Train/Zaher/midi/musicinstrument.h"
#include "../Train/Zaher/midi/midicreator.h"
#include "../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"
#include "../Train/Zaher/freq/freqtable.h"
#include "../Train/Zaher/libmel/melfile.h"
#include "../Train/Zaher/audioread/aiffread.h"
#include "../Train/Zaher/wavFormat/diviseur.h"
#include "../Train/Zaher/signal/complex.h"
#include "../Train/Zaher/signal/signal.h"
#include <ctime>
#include <iostream>

using namespace std;

void create()
{
    Z_audioMidiConverter amc;
    char mf[24];
    if(!amc.convert("petra.wav",mf))
    {
        printf("file not found!\n");
    }
    amc.chooseInstrument(MusicInstrument::Trumpet,mf);

}

void read()
{
    Z_audioMidiConverter amc;
    amc.fix("petra.mid");
}

void freqtabletest()
{
    Freqtable *f=Freqtable::getInstance();
    double diff;
    for(int i=0;i<12;++i)
    {
        printf("%d  ",f->find(68.0,i,&diff));
        printf("%f\n",diff);
    }
}

void prototype4()
{
    freopen("log.log","a",stdout);
    time_t t=time(0);
    struct tm * now=localtime(&t);
    printf("\n--\n--\nstart run :: %d/%d/%d -- %d:%d:%d\n--\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);


    create();


    printf("\n--\n--\nend run\n--------------------------------------------------------------\n--------------------------------------------------------------\n");
}

void prototype5()
{

    freopen("C:/MATLAB7/work/projet 5as/melodieRafinemet.m","w",stdout);
    create();

}

void melFiled()
{
    AiffRead ar;
    ar.open("track1.aif");
    Diviseur d(ar.buffer(),ar.l(),ar.fs(),ar.ba(),ar.nc());
    Signal s;

    Melody m(d.d(),ar.fs());

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],ar.fs(),d.ld(),ar.ba(),ar.nc());
        m.append(s.fc(),s.p());
    }

    m.set_l(s.l());
    m.filtreBilateral(4);

    //m.setScales();

    MelFile f;

    f.getFrom(m);
    f.create("hash.mel");
    f.close();
}

void melFiledw()
{
    MelFile f;

    f.read("hash.mel");

    f.getInfo();
    f.getFreq();
    f.getScal();
    f.getCoqa();

    Melody m;

    f.writeTo(m);

    Z_audioMidiConverter amc;
    amc.melToMid(m,"hash1.mid");
}

void melFilem()
{
    MelFile f;

    f.manipulate("hash.mel");

    Melody m;

    f.getInfo();
    f.getFreq();
    f.getScal();
    f.getCoqa();

    f.writeTo(m);
    m.setScales();
    int scl[12];
    m.getScal(scl);
    f.set_scl(scl);
    f.flush();
}

void mix()
{
    Z_audioMidiConverter amc;
    char *a[]={"track1.aif","track2.aif","track3.aif"};

    amc.mix(a,3,"mix.aif");
}

int main()
{
    mix();
}
