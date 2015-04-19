#ifndef MELODY_H
#define MELODY_H

//class qui contient un tableau qui contient la melodie
//la melodie est constitue d'une serie de frequence fondamentale
//avec la puissance de chacune
//le but de cette class est de pouvoir traiter une melodie
//pour l'ameliorer

class Melody
{
    double *_tfp;
    double *_f;
    double *_p;
    int *_dp;    //positions ou derive de _p forme un pic
    int _di;     //iterateur de _dp, after last value not usable
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
    void calculDerive(int i, double &d);


    Melody(Melody& o);
    Melody& operator =(Melody& o);

public:
    Melody();
    Melody(int n, int fs);
    void append(double f, double p);
    void filtreBilateral(int gs);
    void normalize();
    void valueAt(int i,double v[]); //v tableau de deux valeur
    //0 la frequence 1 la puissance, on remplit le tableau

    void writeToFile(char *filename) const;
    void readFromFile(char *filename);

    void setScales();
    void set_l(int l);
    void set_fs(int fs);
    void incScale();
    void deFix();
    void decompose();  //remplir _dp
    double * correct();    //corrige les notes mal chante

    int scale()const;
    int scaleN()const;
    int fs()const;
    int n()const;
    int l()const;



    void getScal(int scl[]);
    double * freqPow();
    double * distFreq();
    int *distPlace();
    int distNum();

    void set_tfp(double *tfp, int ns);
    void set_dp(int * dp, int di);
    void set_scl(int scl[]);
    void set_scale(int cs);


    ~Melody();
};

#endif // MELODY_H
