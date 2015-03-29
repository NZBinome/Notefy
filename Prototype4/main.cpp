#include "../Train/Zaher/midi/musicinstrument.h"
#include "../Train/Zaher/midi/midicreator.h"
#include "../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"
#include <iostream>

using namespace std;

int main()
{
    Z_audioMidiConverter amc;
    char mf[24];
    if(!amc.convert("raghid16.aif",mf))
    {
        printf("file not found!\n");
    }
    amc.chooseInstrument(MusicInstrument::Bass,mf);
}

