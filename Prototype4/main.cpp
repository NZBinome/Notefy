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
    if(!amc.convert("track1.aif",mf))
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
    create();
}

