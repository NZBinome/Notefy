#ifndef MELODY_H
#define MELODY_H

//class qui contient un tableau qui contient la melodie
//la melodie est constitue d'une serie de frequence fondamentale
//avec la puissance de chacune
//le but de cette class est de pouvoir traiter une melodie
//pour l'ameliorer

class Melody
{
    double *_f;
    double *_p;

    double *_g;     //time Gaussian
    int _gs;        //Gaussian size

    int _n; //total size
    int _i; //actual size

    void _log2F();
    void _exp2F();

    double range(double d);

public:
    Melody(int n);
    void append(double f, double p);
    void filtreBilateral(int gs);
    void gaussian(int n);
    void valueAt(int i,double v[]); //v tableau de deux valeur
    //0 la frequence 1 la puissance, on remplit le tableau
    ~Melody();
};

#endif // MELODY_H
