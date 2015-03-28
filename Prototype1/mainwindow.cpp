#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "signal/complex.h"
#include "signal/signal.h"
#include "wavFormat/wavread.h"
#include "wavFormat/diviseur.h"
#include "midi/note.h"
#include "midi/midicreator.h"

#include <fstream>

#include <cmath>
#include <QDebug>

#include "rasmeh.h"
#include "freq/freqtable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

//    std::fstream file;
//    file.open("3u",std::ios::binary|std::ios::out);

    MidiCreator c(f.fs());

    //std::fstream w;
    //w.open("durb.txt",std::ios::out);
    Note n;

    for(int i=0;i<d.d();++i)
    {

        s.set(d[i],f.fs(),d.ld(),f.ba(),f.nc());
        //s.n();
       // qDebug()<<s.n();

        n.findNote(s.fc());
        n.findVolume(100);
        n.set_d(s.l());

        c.addNote(n);
    }
   // w.close();
    c.creerMidiFile("midi/raghid.mid");

    //file.close();


//    Rasmeh *n=new Rasmeh(s.fourier(),s.l()/2,this);



//    n->setGeometry(10,10,700,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}
