#include <cmath>
#include "freq/freqtable.h"
#include "melody.h"
#include <string.h>
#include <stdio.h>

extern const double PI;

const double ilogst=12.0;   //inverse de log d'un semiton

Melody::Melody(int n)
{
    _i=0;
    _n=n;
    _gs=0;
    _f=new double[n];
    _p=new double[n];
    _g=0;
}

void Melody::gaussian(int n)
{
    double s=n*n*0.5;   // s=2*s^2
    for(int i=0;i<n;++i)
    {
        _g[i]=1.0/(PI*s)*exp(-i*i/s);
    }
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


    double d=0;
    for(int i=0;i<_gs;++i)
        d+=_g[i];
    printf("\ngaus\n%f\n",d);

    printf("\nlog\n");
    for(int i=0;i<_i;++i)
    {
        printf("%f  %f\n",_f[i],_p[i]);
    }

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

    printf("\nfilt\n");
    for(int i=0;i<_i;++i)
    {
        printf("%f  %f\n",_f[i],_p[i]);
    }

    printf("\n\n");
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
    delete [] _f;
    delete [] _p;
    if(_g!=0)
        delete [] _g;
}
