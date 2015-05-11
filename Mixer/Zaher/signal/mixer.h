#ifndef MIXER_H
#define MIXER_H
#include <vector>

class Mixer
{
    std::vector<Signal *> _v;
public:
    Mixer();
    void addSignals(Signal *s,int n);
    Signal * mix();
};

#endif // MIXER_H
