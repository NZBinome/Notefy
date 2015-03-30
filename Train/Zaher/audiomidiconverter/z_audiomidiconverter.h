#ifndef Z_AUDIOMIDICONVERTER_H
#define Z_AUDIOMIDICONVERTER_H

#include "../midi/midicreator.h"
#include "../signal/melody.h"

class Z_audioMidiConverter
{
    void melToMid(Melody& m, char *filename);
public:
    Z_audioMidiConverter();

    int convert(char *audioFile, char *midiFile);
    void chooseInstrument(unsigned char inst, char * filename);
    static unsigned short getInstrument(char * filename);
    void fix(char * filename);
    ~Z_audioMidiConverter();
};

#endif // Z_AUDIOMIDICONVERTER_H
