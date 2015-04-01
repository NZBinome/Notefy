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

    Complex *_F;    //tableau transformer de fourier
   // double *_f;     //la puissance de chaque note dans ce signal

    double _p;      //la puissance du signal
    double _fc;        //la frequence fondamentale

    int _n;         //la note

    double *_filt;  //tableau filtre

    double _pmax;  //puissance maximale
    double _fmax;  //frequence a puissance maximale


    Signal(Signal &o);
    Signal operator=(Signal &o);

      //consulter commentaire sur _f
    void fftf(double *x, int N, int i,Complex *F);
    void methodeParMorceau();   //une methode pour extraction de frequence fondamentale
    void methodePMIterre();     //par morceau ittere
    void itere(double *fp, int n);
    void clusters(double *pr, int n);

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
    void filter();


    ~Signal();
};


#endif // SIGNAL_H
