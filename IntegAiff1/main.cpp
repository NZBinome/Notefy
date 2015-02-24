#include "freq/freqtable.h"
#include "wavFormat/wavread.h"
#include "wavFormat/diviseur.h"
#include "signal/complex.h"
#include "signal/signal.h"
#include "midi/note.h"
#include "midi/midicreator.h"
#include "signal/melody.h"
#include "libaiff/libaiff/libaiff.h"
#include "AudioRead/aiffread.h"
#include "audiomidiconverter/z_audiomidiconverter.h"

void myfunction()
{
    AiffRead f;
    if(!f.open("raghid24.aif"))
        return ;

    Diviseur d(f.buffer(),f.l(),f.fs(),f.ba(),f.nc());

    Signal s;

    MidiCreator c(f.fs());

    Note n;

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());
        n.findNote(s.fc());
        n.findVolume(s.p());
        n.set_d(s.l());

        c.addNote(n);
    }
    c.creerMidiFile("raghidint.mid");

}


int main()
{
    //myfunction();
    Z_audioMidiConverter amc;
    char mf[24];
    if(!amc.convert("raghid24.aif",mf))
    {
        printf("file not found!\n");
    }
    amc.chooseInstrument(57);
    return 0;
}

