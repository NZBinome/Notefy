#ifndef DIVISEUR_H
#define DIVISEUR_H

/*class qui divise le signal
 * initial en fenetre
 */

class Diviseur
{
    unsigned char * _b;      //buffer
    int _l;         //longueur du buffer
    int _fs;        //frequence d'echantillonage (sample rate)
    int _ba;        //nombre de bit par echantillon inclu nombre de channel (block allign)
    int _nc;        //nombre de channe
    int _d;         //nombre de division
    int _ld;        //longueur d'une division
public:
    Diviseur(unsigned char * b, int l, int fs, int ba, int nc);
    ~Diviseur();

    int ld();
    int d();

    unsigned char * operator[](int i); //cette methode recupere les divisions
    //il n'y a pas de control sur i, un out of bounds est possible
};

#endif // DIVISEUR_H
