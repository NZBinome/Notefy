#include <cmath>
#include "../freq/freqtable.h"
#include "melody.h"
#include <string.h>
#include <stdio.h>
#include <fstream>

extern const double PI;

const double ilogst=12.0;   //inverse de log d'un semiton

Melody::Melody(int n)
{
    _i=0;
    _n=n;
    _gs=0;
    _f=0;
    _p=0;
    if(_n!=0)
    {
        _f=new double[n];
        _p=new double[n];
    }
    _g=0;
    _scale=0;
}

void Melody::writeToFile(char *filename) const
{
    std::fstream f;
    f.open(filename,std::ios::out|std::ios::binary);
    f.write((char*)&_n,sizeof(int));
    f.write((char*)_f,sizeof(_f));
    f.write((char*)_p,sizeof(_p));
    f.write((char*)_scale,sizeof(short));
    f.close();
}

void Melody::readFromFile(char *filename)
{
    std::fstream f;
    f.open(filename,std::ios::in|std::ios::binary);
    int n;
    f.read((char*)&n,sizeof(int));
    if(n!=_n)
    {
        delete [] _f;
        delete [] _p;
        _f=new double[n];
        _p=new double[n];
    }
    _n=n;
    f.read((char*)_f,sizeof(_f));
    f.read((char*)_p,sizeof(_p));
    f.read((char*)_scale,sizeof(short));
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
    if(d<=0.5&&d>=-0.5)
        return 1.0;
    if(d<=1.0&&d>=-1.0)
        return 0.75;
    if(d<=1.5&&d>=-1.5)
        return 0.25;
    if(d<=2.0&&d>=-2.0)
        return 0.1;
    return 0.0;
}

void Melody::append(double f, double p)
{
    _f[_i]=f;
    _p[_i]=p;
    ++_i;
}

void Melody::filtreBilateral(int gs)
{
    if(gs!=_gs)
    {
        if(_g!=0)
            delete [] _g;
        _g=new double[gs];
        _gs=gs;
        gaussian(_gs);
    }
    _log2F();


//    printf("\nlog\n");
//    for(int i=0;i<_i;++i)
//    {
//        if(_p[i]!=0)
//            printf("%f  %f\n",_f[i],_p[i]);
//    }

    //test sur un filtre guaussien normal

//    printf("\n\n\n");
    double * f=new double[_i];
    for(int i=0;i<_i;++i)
        f[i]=0;


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
                //printf("d %f\n",d);
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
                //printf("d %f\n",d);
                wp+=_g[j]*d;
                f[i]+=_f[i+j]*_g[j]*d;
            }
        }
        //printf("%f \n",wp);
        f[i]/=wp;
    }

    for(int i=0;i<_i;++i)
        _f[i]=f[i];
//    double * newf=new double[_i];
//    memset(newf,0,sizeof(newf));

//    for(int i=0;i<_i;++i)
//    {
//        double wp=0;
//        for(int j=0;j<_gs;++j)
//        {
//            double x;
//            if(i+j<_i)
//            {
//                x=_f[i]-_f[i+j];
//                wp+=_g[j]*(1/(PI*_SR)*exp(-x*x/_SR));
//            }
//            if(i-j>-1)
//            {
//                x=_f[i]-_f[i-j];
//                wp+=_g[j]*(1/(PI*_SR)*exp(-x*x/_SR));
//            }
//        }
//        for(int j=0;j<_gs;++j)
//        {
//            double x;
//            if(i+j<_i)
//            {
//                x=_f[i]-_f[i+j];
//                newf[i]+=_g[j]*(1.0/(PI*_SR)*exp(-x*x/_SR))*_f[i+j];
//            }
//            if(i-j>-1)
//            {
//                x=_f[i]-_f[i-j];
//                newf[i]+=_g[j]*(1.0/(PI*_SR)*exp(-x*x/_SR))*_f[i-j];
//            }
//        }
//        newf[i]*=1.0/wp;
//    }
//

//    for(int i=0;i<_i;++i)
//    {
//        for(int j=0;j<_gs;++j)
//        {
//            if(i+j>=_i)
//                newf[i]+=_g[j]*_f[i];
//            else
//                newf[i]+=_g[j]*_f[i+j];
//            if(i-j<0)
//                newf[i]+=_g[j]*_f[i];
//            else
//                newf[i]+=_g[j]*_f[i-j];
//        }
//    }

//    for(int i=0;i<_i;++i)
//        _f[i]=newf[i];
//    delete [] newf;

//    printf("\nfilt\n");
//    for(int i=0;i<_i;++i)
//    {
//        if(_p[i]!=0)
//            printf("%f  %f\n",_f[i],_p[i]);
//    }

//    printf("\n\n");
    _exp2F();

}

void Melody::_log2F()
{
    for(int i=0;i<_i;++i)
        _f[i]=ilogst*log2(_f[i]);
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

Melody::~Melody()
{
    if(_f!=0)
        delete [] _f;
    if(_g!=0)
        delete [] _p;
    if(_g!=0)
        delete [] _g;
}
