#ifndef SIGNAL_H
#define SIGNAL_H

class Signal
{
    double *_s;     //le signal, valeur entre -1 et 1
    int _l;         //la longueur du signal
    int _fs;        //le sample rate, frequence d'echantillonage

    double *_f;     //le module de la transforme de fourier
        //    ^^ ca se peut qu'on ne l'utilisera pas,
        // ca dependera de la necessesite de sauvegarde de la transforme


   // double *_f;     //la puissance de chaque note dans ce signal

    double _p;      //la puissance du signal
    double _fc;        //la frequence de puissance max

    int _n;         //la note

    Signal(Signal &o);
    Signal operator=(Signal &o);

      //consulter commentaire sur _f

public:
    Signal();

    void set(unsigned char * vectOctet, int fs, int l, int ba, int nc);
    /*vectOctet est le signal raw en byte
    fs le sample rate, frequence d'echantillonage
    l la longueur de vectOctet
    ba le nombre de byte pour un echantillon, inclu tous les channel
    nc nombre de channel*/

    void reset();

    double *signal();
    int l();
    int fs();

    double p();
    double fc();

    int n();

    double *fourier();


    ~Signal();
};


#endif // SIGNAL_H
