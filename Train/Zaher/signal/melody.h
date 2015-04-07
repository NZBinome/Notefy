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
    int *_dp;    //positions ou derive de _p forme un pic
    int _di;     //iterateur de _dp
    bool _corrected;

    double *_g;     //time Gaussian
    int _gs;        //Gaussian size

    int _scales[12]; //pour tous les gammes, taux d'erreur
    int _scale;

    int _n; //total size
    int _i; //actual size

    int _l; //lenght time for midi conversion
    int _fs;

    double _pmax;



    double range(double d);
    void _log2F();
    void _exp2F();
    void gaussian(int n);

public:
    Melody(int n, int fs);
    Melody(Melody& o);
    Melody& operator =(Melody& o);
    void append(double f, double p);
    void filtreBilateral(int gs);
    void normalize();
    void valueAt(int i,double v[]); //v tableau de deux valeur
    //0 la frequence 1 la puissance, on remplit le tableau
    void writeToFile(char *filename) const;
    void readFromFile(char *filename);
    void setScales();
    void set_l(int l);
    void incScale();
    void deFix();
    void correct();    //corrige les notes mal chante

    int scale()const;
    int fs()const;
    int n()const;
    int l()const;

    ~Melody();
};

#endif // MELODY_H
