#include "../Train/Zaher/signal/melody.h"
#include "../Train/Zaher/midi/musicinstrument.h"
#include "../Train/Zaher/midi/midicreator.h"
#include "../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"
#include "../Train/Zaher/freq/freqtable.h"
#include <iostream>

using namespace std;

void create()
{
    Z_audioMidiConverter amc;
    char mf[24];
<<<<<<< HEAD
    if(!amc.convert("kheryet kaleb.wav",mf))
=======
    if(!amc.convert("track1.aif",mf))
>>>>>>> parent of 62ad6e2... unfuddle task #5
    {
        printf("file not found!\n");
    }
    amc.chooseInstrument(MusicInstrument::Bass,mf);

}

void read()
{
    Z_audioMidiConverter amc;
    amc.fix("raghid16.mid");
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

int main()
{
<<<<<<< HEAD
    freopen("log.log","a",stdout);
    time_t t=time(0);
    struct tm * now=localtime(&t);
    printf("\n--\n--\nstart run :: %d/%d/%d -- %d:%d:%d\n--\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);


    create();


    printf("\n--\n--\nend run\n--------------------------------------------------------------\n--------------------------------------------------------------\n");
=======
    create();
>>>>>>> parent of 62ad6e2... unfuddle task #5
}

