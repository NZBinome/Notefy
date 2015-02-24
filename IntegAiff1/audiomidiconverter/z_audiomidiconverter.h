#ifndef Z_AUDIOMIDICONVERTER_H
#define Z_AUDIOMIDICONVERTER_H

class Z_audioMidiConverter
{
    MidiCreator *_c;
public:
    Z_audioMidiConverter();

    int convert(char *audioFile, char *midiFile);
    void chooseInstrument(unsigned char inst);
    ~Z_audioMidiConverter();
};

#endif // Z_AUDIOMIDICONVERTER_H
