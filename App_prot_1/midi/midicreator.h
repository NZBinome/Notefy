#ifndef MIDICREATOR_H
#define MIDICREATOR_H
#include "note.h"
#include <vector>

class MidiCreator
{
    char *_name;
    const int _dt=100;
    double _fdt;       //facteur pour savaoir le temps en tick du delta time du fichier midi.
    int _inst;
    std::vector<Note> _n;


public:
    MidiCreator(int fs);
    /* pour deduire _fdt, on doit connaitre :
        fs la frequence d'echantillonage, chaque echantillon fait 1/fs seconde

        ainsi on connait la quantite de tick par echantillon
        en fixant la longueur d'une noire

        */

    int sizeData(char *&c);
    void addNote(Note n);
    void creerMidiFile(char * name);
};

#endif // MIDICREATOR_H
