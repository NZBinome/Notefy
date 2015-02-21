#ifndef Z_AUDIOMIDICONVERTER_H
#define Z_AUDIOMIDICONVERTER_H

class Z_audioMidiConverter
{
public:
    Z_audioMidiConverter();

    int convert(char *audioFile, char *midiFile);
};

#endif // Z_AUDIOMIDICONVERTER_H
