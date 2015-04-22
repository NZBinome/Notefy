#ifndef AUDIOWRITE_H
#define AUDIOWRITE_H

/*AudioWrite est une class abstraite
 * elle doit permettre de creer un fichier audio
 * a partir d'un signal
 */

class AudioWrite
{
protected:
    unsigned char *_b;  //buffer
    int _l;             //longueur du buffer
    int _fs;            //longueur d'echantillonage (sample rate)
    int _ba;            //nombre de bit par echantillon inclu nombre de channel (block allign)
    short int _nc;
public:
    AudioWrite();
    virtual ~AudioWrite();

    virtual int write(const char *file)=0;
    void set_buffer(unsigned char* buffer);
    void set_fs(int fs);
    void set_l(int l);
    void set_ba(int ba);
};

#endif // AUDIOWRITE_H
