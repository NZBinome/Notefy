#include <cmath>
#include "../freq/freqtable.h"
#include "melody.h"
#include <string.h>
#include <stdio.h>
#include <fstream>

extern const double PI;

const double ilogst=12.0;   //inverse de log d'un semiton

Melody::Melody(int n, int fs)
{
    _i=0;
    _l=0;
    _fs=fs;
    _n=n;
    _gs=0;
    _f=0;
    _p=0;
    if(_n!=0)
    {
        _f=new double[n+1];
        _p=new double[n+1];
        _f[_n]=1.0;
        _p[_n]=1.0;
    }
    _g=0;
    _scales[0]=0;
    _scales[1]=1;
    _scales[2]=2;
    _scales[3]=3;
    _scales[4]=4;
    _scales[5]=5;
    _scales[6]=6;
    _scales[7]=7;
    _scales[8]=8;
    _scales[9]=9;
    _scales[10]=10;
    _scales[11]=11;
    _scale=-1;
    _pmax=0;
}

Melody::Melody(Melody &o)
{
    _i=o._i;
    _n=o._n;
    _l=o._l;
    _fs=o._fs;
    _gs=0;
    _f=o._f;
    _p=o._p;
    ++_p[_n];
    ++_f[_n];
    _g=0;
    memcpy(_scales,o._scales,12*sizeof(int));
    _scale=-1;
    _pmax=o._pmax;
}

Melody& Melody::operator =(Melody& o)
{
    if(_n!=0)
    {
        if(--_f[_n]==0.0)
            delete [] _f;
        if(--_p[_n]==0.0)
            delete [] _p;
    }

    _i=o._i;
    _n=o._n;
    _l=o._l;
    _fs=o._fs;
    _gs=0;
    _f=o._f;
    _p=o._p;
    ++_p[_n];
    ++_f[_n];
    _g=0;
    memcpy(_scales,o._scales,12*sizeof(int));
    _scale=o._scale;
    _pmax=o._pmax;
    return *this;
}

void Melody::writeToFile(char *filename) const
{
    std::fstream f;
    f.open(filename,std::ios::out|std::ios::binary);
    f.write((char*)&_n,sizeof(int));
    f.write((char*)&_l,sizeof(int));
    f.write((char*)&_fs,sizeof(int));
    f.write((char*)_f,_n*sizeof(double));
    f.write((char*)_p,_n*sizeof(double));
    f.write((char*)&_scale,sizeof(int));
    f.write((char*)_scales,12*sizeof(int));
    f.close();
}

void Melody::readFromFile(char *filename)
{
    std::fstream f;
    f.open(filename,std::ios::in|std::ios::binary);
    if(!f.is_open())
    {
        throw "no file";
    }
    int n;
    f.read((char*)&n,sizeof(int));
    if(n!=_n)
    {
        if(_n!=0)
        {
            if(--_f[_n]==0.0)
                delete [] _f;
            if(--_p[_n]==0.0)
                delete [] _p;
        }
        _f=new double[n+1];
        _p=new double[n+1];
        _f[n]=1.0;
        _p[n]=1.0;
    }
    _n=n;
    f.read((char*)&_l,sizeof(int));
    f.read((char*)&_fs,sizeof(int));
    f.read((char*)_f,_n*sizeof(double));
    f.read((char*)_p,_n*sizeof(double));
    f.read((char*)&_scale,sizeof(int));
    f.read((char*)_scales,12*sizeof(int));
    f.close();
}

void Melody::gaussian(int n)
{
    double s=n*n*0.5;   // s=2*s^2
    double d=1.0;
    _g[0]=1.0;
    for(int i=1;i<n;++i)
    {
        _g[i]=exp(-i*i/s);
        d+=2*_g[i];
    }
    for(int i=0;i<n;++i)
        _g[i]/=d;
}

double Melody::range(double d)
{
    if(d<=0.8&&d>=-0.8)
        return 1.0;
    if(d<=1.2&&d>=-1.2)
        return 0.75;
    if(d<=1.7&&d>=-1.7)
        return 0.25;
    if(d<=2.2&&d>=-2.2)
        return 0.1;
    return 0.0;
}

void Melody::append(double f, double p)
{
    _f[_i]=f;
    _p[_i]=p;
    ++_i;
    if(_pmax<p)
        _pmax=p;
}

void Melody::normalize()
{
}

void Melody::filtreBilateral(int gs)
{
//    printf("\n\nbeforebilatera\n");
//    for(int i=0;i<_i;++i)
//    {
//        printf("%f   \t%f\n",_f[i],_p[i]);
//    }

    double p=0.5;
    _pmax=pow(_pmax,p);

    if(gs!=_gs)
    {
        if(_g!=0)
            delete [] _g;
        _g=new double[gs];
        _gs=gs;
        gaussian(_gs);
    }
    _log2F();
    double * f=new double[_i];
    memset(f,0,_i*sizeof(double));


    for(int i=0;i<_i;++i)
    {
        if(_p[i]==0)
            continue;
        double wp=0;
        wp+=_g[0];
        f[i]+=_f[i]*_g[0];
        for(int j=1;j<_gs;++j)
        {
            double d;
            if(i-j<0)
            {
                wp+=_g[j];
                f[i]+=_f[i]*_g[j];
            }
            else
            {
                d=range(_f[i]-_f[i-j]);
                wp+=_g[j]*d;
                f[i]+=_f[i-j]*_g[j]*d;
            }
            if(i+j>=_i)
            {
                wp+=_g[j];
                f[i]+=_f[i]*_g[j];
            }
            else
            {
                d=range(_f[i]-_f[i+j]);
                wp+=_g[j]*d;
                f[i]+=_f[i+j]*_g[j]*d;
            }
        }
        f[i]/=wp;
        _p[i]=pow(_p[i],p);
    }

    for(int i=0;i<_i;++i)
        _f[i]=f[i];
    _exp2F();

//    printf("\n\nMelody\n");
//    for(int i=0;i<_i;++i)
//    {
//        printf("%f   \t%f\n",_f[i],_p[i]);
//    }

}

void Melody::_log2F()
{
    for(int i=0;i<_i;++i)
    {
        if(_f[i]>0)
            _f[i]=ilogst*log2(_f[i]);
    }
}

void Melody::_exp2F()
{
    for(int i=0;i<_i;++i)
        _f[i]=exp2(_f[i]*(1.0/ilogst));
}

void Melody::valueAt(int i,double v[])
{
    v[0]=_f[i];
    v[1]=_p[i];
}

void Melody::set_l(int l)
{
    _l=l;
}

int Melody::fs()const
{
    return _fs;
}

int Melody::n()const
{
    return _n;
}

int Melody::l()const
{
    return _l;
}

void Melody::setScales()
{
    double diff;
    Freqtable *f=Freqtable::getInstance();
    double scalesV[12];
    memset(scalesV,0,12*sizeof(double));
    for(int s=0;s<12;++s)
    {
        for(int i=0;i<_n;++i)
        {
            if(_p[i]!=0)
            {
                f->find(_f[i],s,&diff);
                if(diff<1.0)
                    diff=1.0/diff;
                scalesV[s]+=diff;
            }
        }

    }
    for(int i=0;i<11;++i)
    {
        for(int j=0;j+i<11;++j)
        {
            if(scalesV[_scales[j]]>scalesV[_scales[j+1]])
            {
                int temp=_scales[j];
                _scales[j]=_scales[j+1];
                _scales[j+1]=temp;
            }
        }
    }

}

int Melody::scale()const
{
    if(_scale==-1)
        return _scale;
    return _scales[_scale];
}

void Melody::deFix()
{
    _scale=-1;
}

void Melody::incScale()
{
    ++_scale;
    _scale=_scale%12;
}

Melody::~Melody()
{
    if(_f!=0)
        if(--_f[_n]==0)
            delete [] _f;
    if(_p!=0)
        if(--_p[_n]==0)
            delete [] _p;
    if(_g!=0)
        delete [] _g;
}
