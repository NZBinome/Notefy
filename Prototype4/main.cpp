#include "../Train/Zaher/signal/melody.h"
#include "../Train/Zaher/midi/musicinstrument.h"
#include "../Train/Zaher/midi/midicreator.h"
#include "../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"
#include "../Train/Zaher/freq/freqtable.h"
#include "../Train/Zaher/signal/complex.h"
#include "../Train/Zaher/signal/signal.h"
#include "../Train/Zaher/audioread/aiffread.h"
#include "../Train/Zaher/wavFormat/diviseur.h"
#include "../Train/Zaher/util/util.h"
#include "../Train/Zaher/audioread/wavread.h"
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>

using namespace std;

void create()
{
    Z_audioMidiConverter amc;
    char mf[24];
    if(!amc.convert("kheryet kaleb.wav",mf))
    {
        printf("file not found!\n");
    }
    amc.chooseInstrument(MusicInstrument::Bass,mf);

}

void read()
{
    Z_audioMidiConverter amc;
    amc.fix("raghid.mid");
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

void newSignalTest()
{
    Wavread f;
    if(!f.open("kheryet kaleb.wav"))
        ;
    Diviseur d(f.buffer(),f.l(),f.fs(),f.ba(),f.nc());

    Signal s;

    s.set(d[10],f.fs(),d.ld(),f.ba(),f.nc());
    s.fourier();
}

void testQuickSort()
{
    double tab[]={0.9, 0.5, -0.7, 1.0, 4.7, -0.6, 6.2, 1.0, 3.9, 1.0, 1.0, 0.7, 1, 2, 3, 4, 5, 6, 7,8,9,10,11,12};
    Util::triRapideDouble(tab,12);
    printf("last tri\n");
    for(int i=0;i<12;++i)
    {
        printf("%f   \t  %f\n",tab[i],tab[i+12]);
    }
    printf("\n");
}

void strlenwkaza()
{
}

int main()
{
    freopen("log.log","a",stdout);
    time_t t=time(0);
    struct tm * now=localtime(&t);
    printf("\n--\n--\nstart run :: %d/%d/%d -- %d:%d:%d\n--\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);


    create();


    printf("\n--\n--\nend run\n--------------------------------------------------------------\n--------------------------------------------------------------\n");
}

