#include <string.h>
#include "complex.h"
#include "signal.h"
#include "mixer.h"

using namespace std;

Mixer::Mixer()
{
}

void Mixer::addSignals(Signal *s, int n)
{
    for(int i=0;i<n;++i)
    {
        _v.push_back(s+i);
    }
}

Signal * Mixer::mix()
{
    Signal * result=new Signal();

    int maxl=0;
    int sfs; //all the Signals should have the same _fs in order to mix
    sfs=((Signal *)_v[0])->fs();
    for(int i=0;i<_v.size();++i)
    {
        int l=((Signal *)_v[i])->l();
        int fs=((Signal*)_v[i])->fs();
        if(fs!=sfs)
            throw "unsuported";
        if(l>maxl)
            maxl=l;
    }
    double * signal=new double[maxl];
    memset(signal,0,maxl*sizeof(double));

    for(int i=0;i<_v.size();++i)
    {
        for(int j=0;j<((Signal *)_v[i])->l();++j)
        {
            signal[j]+=((Signal *)_v[i])->signal()[j];
        }
    }
    for(int i=0;i<maxl;++i)
        signal[i]/=_v.size();

    result->set(signal,sfs,maxl);
    return result;
}

