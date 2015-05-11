#include "aiffread.h"
#include "../libaiff/libaiff/libaiff.h"

AiffRead::AiffRead()
{
}

int AiffRead::open(const char *file)
{
    AIFF_Ref ref=AIFF_OpenFile(file,F_RDONLY);
    if(!ref)
    {
        AIFF_CloseFile(ref);
        return 0;
    }

    uint64_t nSample;
    int bps; //bitspersample
    int ss; //segmentSize
    int channels;
    double sampleRate;
    if(AIFF_GetAudioFormat(ref,&nSample,&channels,&sampleRate,&bps,&ss)<1)
    {
        AIFF_CloseFile(ref);
        return 0;
    }

    _nc=(short unsigned int)channels;
    _fs=(int)sampleRate;
    _ba=ss*_nc;
    _l=nSample*channels*ss;
    _b=new unsigned char[_l+1];
    _b[_l]=1;
    AIFF_ReadSamples(ref,_b,_l);
    manipulate(ss);   //to convert samples to little endian
    AIFF_CloseFile(ref);
    return 1;

}

void AiffRead::manipulate(const int ss)
{
    for(int i=0;i<_l;i+=ss)
    {
        unsigned char temp;
        for(int j=0;j<ss/2;++j)
        {
            temp=_b[i+j];
            _b[i+j]=_b[i+ss-j-1];
            _b[i+ss-j-1]=temp;
        }
    }
}

AiffRead::~AiffRead()
{
}
