#ifndef AUDIOREAD_H
#define AUDIOREAD_H

/* AudioRead est une class abstraite
 * elle doit permetre de recuperer un signal audio
 * d'un fichier quelque soit son format
 */

class AudioRead
{
protected:
    unsigned char *_b;  //buffer
    int _l;             //longueur du buffer
    int _fs;            //longueur d'echantillonage (sample rate)
    int _ba;            //nombre de bit par echantillon inclu nombre de channel (block allign)
    unsigned short int _nc;     //nb de channel
public:
    AudioRead();
    virtual ~AudioRead();

    virtual int open(const char *file)=0;
    unsigned char *buffer();
    int fs();
    int l();
    int ba();
    int nc();
};

#endif // AUDIOREAD_H
