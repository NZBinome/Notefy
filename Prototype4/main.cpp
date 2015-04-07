#include "../Train/Zaher/signal/melody.h"
#include "../Train/Zaher/midi/musicinstrument.h"
#include "../Train/Zaher/midi/midicreator.h"
#include "../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"
#include "../Train/Zaher/freq/freqtable.h"
#include <ctime>
#include <iostream>

using namespace std;

void create()
{
    Z_audioMidiConverter amc;
    char mf[24];
    if(!amc.convert("track2.aif",mf))
    {
        printf("file not found!\n");
    }
    amc.chooseInstrument(MusicInstrument::Trumpet,mf);

}

void read()
{
    Z_audioMidiConverter amc;
    amc.fix("track2.mid");
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


    read();


    printf("\n--\n--\nend run\n--------------------------------------------------------------\n--------------------------------------------------------------\n");
}

void prototype5()
{
    freopen("C:/MATLAB7/work/projet 5as/melodieRafinemet.m","w",stdout);
    create();
}

int main()
{
    prototype4();
}

