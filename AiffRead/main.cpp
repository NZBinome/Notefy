#include <stdio.h>
#include "libaiff/libaiff/libaiff.h"
#include "AudioRead/aiffread.h"

void testfunction1()
{
    AIFF_Ref file=AIFF_OpenFile("lado.aif",F_RDONLY);
    if(file)
    {
        printf("File opened successfully.\n");
    }
    uint64_t nSamples ;
    int channels ;
    double samplingRate ;
    int bitsPerSample ;
    int segmentSize ;

    if( AIFF_GetAudioFormat( file,&nSamples,&channels,
                &samplingRate,&bitsPerSample,
                &segmentSize ) < 1 )
    {
        printf( "Error" );
        AIFF_Close( file );
    }

    printf("%d  %d  %d  %d,  %f\n",(int)nSamples,channels,(int)samplingRate,bitsPerSample,nSamples/samplingRate);

    int *samples=new int[nSamples*channels*3];

    AIFF_ReadSamples(file,samples,nSamples*channels*3);

    printf("hello world\n");
    AIFF_CloseFile(file);
}

void test2()
{
    AiffRead file;
    file.open("raghid24.aif");
    printf("%d  %d  %d\n",file.fs(),file.l(),file.ba());
}

int main()
{
    test2();
    return 0;
}

