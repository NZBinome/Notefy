#include <iostream>
#include "signal/complex.h"
#include "signal/signal.h"
#include "wavFormat/wavread.h"
#include "wavFormat/diviseur.h"
#include "midi/note.h"
#include "midi/midicreator.h"
#include "freq/freqtable.h"
#include <fstream>


using namespace std;

int t[56][2];
double p[56][2];

void readCreateFile()
{
    Wavread f;
    try
    {
       f.open("wav/testsound44.wav");
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
        n.findVolume(100);
        n.set_d(s.l());

        t[i][0]=n.n();
        p[i][0]=s.p();

        c.addNote(n);
    }
    c.creerMidiFile("midi/testthree.mid");
}

int main()
{
    Wavread f;
    try
    {
       f.open("wav/testsound44.wav");
    }
    catch(const char * c)
    {
        printf("%s\n",c);
    }

    Diviseur d(f.buffer(),f.l(),f.fs(),f.ba(),f.nc());

    Signal s;

    Note n;

    MidiCreator c(f.fs());


    for(int i=0;i<d.d();++i)
    {
        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());
        n.setNote(s.n());
        n.findVolume(s.p()*2.0);
        n.set_d(s.l());
        c.addNote(n);

        t[i][1]=n.n();
        p[i][1]=s.p();

        //n.findNote(s.fc());
        //printf("\n\n%d\n",n.n());
        //readCreateFile();
    }
    readCreateFile();

    for(int i=0;i<56;++i)
    {
        printf("%d   %f  %d   %f\n",t[i][0],p[i][0],t[i][1],p[i][1]);
    }
   // c.creerMidiFile("midi/testfive.mid");
    return 0;
}

