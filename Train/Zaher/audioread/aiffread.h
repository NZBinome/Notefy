#ifndef AIFFREAD_H
#define AIFFREAD_H
#include "audioread.h"

class AiffRead : public AudioRead
{
    void manipulate(const int ss);
public:
    AiffRead();
    int open(const char *file);
    ~AiffRead();
};

#endif // AIFFREAD_H
