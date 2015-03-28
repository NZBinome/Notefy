#ifndef Z_AUDIOMIDICONVERTER_H
#define Z_AUDIOMIDICONVERTER_H

class Z_audioMidiConverter
{
    MidiCreator *_c;

public:
    Z_audioMidiConverter();


    int convert(char *audioFile, char *midiFile);
    void chooseInstrument(unsigned char inst, char * filename);
    static unsigned short getInstrument(char * filename);
    void fix(char * filename);
    ~Z_audioMidiConverter();
};

#endif // Z_AUDIOMIDICONVERTER_H
