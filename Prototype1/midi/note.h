#ifndef NOTE_H
#define NOTE_H

/*class qui traduit
  les les frequence et puissance
  d'un signal en note message midi
*/

class Note
{
    int _d;             //durre d'une note
    unsigned char _n;   //la note
    unsigned char _v;   //le volume de la note
public:
    Note();

    void set_d(int d);
    void inc_d(int d);


    void findNote(double frequence);    //on trouve la note grace a la frequence
    void findVolume(double puissance);  //le volume grace a la puissance

    int d();
    unsigned char n();
    unsigned char v();

    unsigned char * toMidiMessage(int &s, double r, short int channel);     //pas de control si on n'a pas saisi tous les membres
    //s est la longueur de message midi en byte
};

#endif // NOTE_H
