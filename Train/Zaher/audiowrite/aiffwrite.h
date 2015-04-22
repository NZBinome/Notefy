#ifndef AIFFWRITE_H
#define AIFFWRITE_H
#include "audiowrite.h"

class AiffWrite : public AudioWrite
{
    void manipulate(const int ss);
public:
    AiffWrite();
    int write(const char *file);
    ~AiffWrite();
};

#endif // AIFFWRITE_H
