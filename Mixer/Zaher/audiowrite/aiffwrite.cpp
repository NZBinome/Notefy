#include "aiffwrite.h"
#include "../libaiff/libaiff/libaiff.h"

AiffWrite::AiffWrite()
{
}

int AiffWrite::write(const char *file)
{
    AIFF_Ref ref=AIFF_OpenFile(file,F_WRONLY|F_AIFC);
    if(!ref)
    {
        AIFF_CloseFile(ref);
        return 0;
    }

    if(AIFF_SetAudioFormat(ref,_nc,1.0*_fs,8*_ba/_nc)<1)
    {
        AIFF_CloseFile(ref);
        return 0;
    }

    manipulate(_ba/_nc);

    AIFF_StartWritingSamples(ref);
    AIFF_WriteSamples(ref,_b,_l);
    AIFF_EndWritingSamples(ref);

    AIFF_CloseFile(ref);
    return 1;
}

void AiffWrite::manipulate(const int ss)
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

AiffWrite::~AiffWrite()
{

}
