#ifndef WAVREAD_H
#define WAVREAD_H
#include "audioread.h"

class Wavread : public AudioRead
{

public:
    Wavread();
    ~Wavread();

    int open(const char *file);
};

#endif // WAVREAD_H
