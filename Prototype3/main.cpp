#include <iostream>
#include "freq/freqtable.h"
#include "wavFormat/wavread.h"
#include "wavFormat/diviseur.h"
#include "signal/complex.h"
#include "signal/signal.h"
#include "midi/note.h"
#include "midi/midicreator.h"
#include "signal/melody.h"

using namespace std;

void myfunction()
{
    Wavread f;
    try
    {
       f.open("wav/raghid24.wav");
    }
    catch(const char * c)
    {
        printf("%s\n",c);
    }

    Diviseur d(f.buffer(),f.l(),f.fs(),f.ba(),f.nc());

    Signal s;

    MidiCreator c(f.fs());
    Note n;

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());
        n.findNote(s.fc());
        n.findVolume(s.p());
        //printf("%f  %f\n",s.fc(),s.p());
        n.set_d(s.l());

        c.addNote(n);
    }
    c.creerMidiFile("midi/raghidprot3.mid");
}

void testProtMelody()
{
    Wavread f;
    try
    {
       f.open("wav/raghid24.wav");
    }
    catch(const char * c)
    {
        printf("%s\n",c);
    }

    Diviseur d(f.buffer(),f.l(),f.fs(),f.ba(),f.nc());

    Signal s;


    Melody m(d.d());

    MidiCreator c(f.fs());
    Note n;

    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());

        m.append(s.fc(),s.p());
    }

//    for(int i=0;i<d.d();++i)
//    {
//        double v[2];
//        m.valueAt(i,v);
//        printf("%f  %f\n",v[0],v[1]);
//    }

    m.filtreBilateral(4);

//    for(int i=0;i<d.d();++i)
//    {
//        double v[2];
//        m.valueAt(i,v);
//        printf("%f  %f\n",v[0],v[1]);
//    }
    for(int i=0;i<d.d();++i)
    {
        double v[2];
        m.valueAt(i,v);
        n.findNote(v[0]);
        n.findVolume(v[1]);
        //printf("%f  %f\n",s.fc(),s.p());
        n.set_d(s.l());

        c.addNote(n);
    }
    c.creerMidiFile("midi/raghidbilateral.mid");
}


int main()
{
    Freqtable * f=Freqtable::getInstance();

    //myfunction();
    testProtMelody();
    return 0;
}

