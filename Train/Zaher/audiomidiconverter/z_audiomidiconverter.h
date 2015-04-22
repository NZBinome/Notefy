#ifndef Z_AUDIOMIDICONVERTER_H
#define Z_AUDIOMIDICONVERTER_H

#include "../midi/midicreator.h"
#include "../signal/melody.h"

class Z_audioMidiConverter
{

public:
    Z_audioMidiConverter();
    void melToMid(Melody& m, char *filename);
    int convert(char *audioFile, char *midiFile);
    void chooseInstrument(unsigned char inst, char * filename);
    static unsigned short getInstrument(char * filename);
    void fix(char * filename, bool deFix=false);
    void mix(char ** files, int numberOfFiles, char *destFile);
    ~Z_audioMidiConverter();
};

#endif // Z_AUDIOMIDICONVERTER_H
