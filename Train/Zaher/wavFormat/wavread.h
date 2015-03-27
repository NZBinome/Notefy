#ifndef WAVREAD_H
#define WAVREAD_H

class Wavread
{
    unsigned char * _b;      //buffer
    int _l;         //longueur du buffer
    int _fs;        //frequence d'echantillonage (sample rate)
    int _ba;        //nombre de bit par echantillon inclu nombre de channel (block allign)
    unsigned short int _nc;  //nombre de channe


public:
    Wavread();
    ~Wavread();

    void open(const char *file);
    unsigned char *buffer();
    int fs();
    int l();
    int ba();
    int nc();
};

#endif // WAVREAD_H
