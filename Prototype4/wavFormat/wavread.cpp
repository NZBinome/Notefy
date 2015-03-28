#include <fstream>
#include "wavread.h"
#include <stdio.h>
using namespace std;

Wavread::Wavread()
{
    _b=0;
    _l=0;
    _fs=0;
    _ba=0;
    _nc=0;
}

void Wavread::open(const char *file)
{
    fstream wavFile;
    wavFile.open(file,ios::binary|ios::in);
    if(wavFile.is_open())
    {

        char RIFF[4];
        int ChunkSize;
        char WAVE[4];
        char fmt[4];
        int SubChunkSize;
        short int AudFor;
        short int NumChan;
        int SamplRate;
        int ByteRate;
        short int BlockA;
        short int BpSample;
        char data[4];
        int SubChunkSize2;

        wavFile.read(RIFF,4);
        if(RIFF[0]!='R'||RIFF[1]!='I'||RIFF[2]!='F'||RIFF[3]!='F')     //making sure the file is okay
            throw "Riff non existant\0";
        wavFile.read((char*)&ChunkSize,4);
        wavFile.read(WAVE,4);
        if(WAVE[0]!='W'||WAVE[1]!='A'||WAVE[2]!='V'||WAVE[3]!='E')
            throw "Wave non existant\0";
        wavFile.read(fmt,4);
        if(fmt[0]!='f'||fmt[1]!='m'||fmt[2]!='t'||fmt[3]!=' ')
            throw "fmt non existant\0";
        wavFile.read((char*)&SubChunkSize,4);
        wavFile.read((char*)&AudFor,2);
        if(AudFor!=1||SubChunkSize!=16)
            throw "AudioFormat non supporter\0";
        wavFile.read((char*)&NumChan,2);
        _nc=NumChan;
        wavFile.read((char*)&SamplRate,4);
        _fs=SamplRate;
        wavFile.read((char*)&ByteRate,4);
        wavFile.read((char*)&BlockA,2);
        wavFile.read((char*)&BpSample,2);
        if(BpSample!=8*BlockA/NumChan)
            throw "erreur dans les bit per sample\0";
        _ba=BlockA;
        wavFile.read(data,4);
        if(data[0]!='d'||data[1]!='a'||data[2]!='t'||data[3]!='a')
            throw "data non existant\0";
        wavFile.read((char*)&SubChunkSize2,4);
        wavFile.seekg(0,ios::end);
        int end=wavFile.tellg();
        if(ChunkSize!=SubChunkSize2+36||ChunkSize!=(end-8))
            throw "erreur dans la taille du fichier\0";
        _l=SubChunkSize2;



        wavFile.seekg(44,ios::beg);

        _b=new unsigned char[_l+1];  //le +1 est necessaire pour facilite le partage de ce tableau

        wavFile.read((char*)_b,_l*sizeof(char));

        _b[_l]=1;

        printf("%d  %d  %d\n",SamplRate,BlockA,BpSample);
    }
    else
    {
        throw "je ne peux ouvrir le fichier";
    }


    wavFile.close();
}

unsigned char * Wavread::buffer()
{
    return _b;
}

int Wavread::fs()
{
    return _fs;
}

int Wavread::ba()
{
    return _ba;
}

int Wavread::nc()
{
    return _nc;
}

int Wavread::l()
{
    return _l;
}

Wavread::~Wavread()
{
    if(_b!=0)
    {
        if((--_b[_l])==0) //on decremente les liens vers ce tableau
        {
            delete [] _b;
            _b=0;
        }
    }
}
