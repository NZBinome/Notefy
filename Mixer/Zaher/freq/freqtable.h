#ifndef FREQTABLE_H
#define FREQTABLE_H

class Freqtable
{
    static Freqtable * single;

    int _minFreq;
    int _maxFreq;

    Freqtable(int minValue, int maxValue);

public:

    static const int NFT=108;
    static const double FREQTABLE[NFT];

    static Freqtable * getInstance();
    int min();
    int max();
    int find(double freq); //retourne l'indice d'une frequence
    int find(double freq, int scale, double *diff=0); //indice dans freqtable, frequence dans scale, avec la difference entre la frequence initiale et celle corige
    bool inScale(int ind, int scale);
    void setMin(int minValue);
    void setMax(int maxValue);
    void set(int minValue, int maxValue);
};

#endif // FREQTABLE_H
