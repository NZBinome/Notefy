#include "complex.h"
#include "signal.h"
#include "freq/freqtable.h"

#include <QDebug>

Signal::Signal()
{
    _s=0;
    _l=0;
    _fs=0;
    _f=0;
    _p=-1.0;
    _fc=-1.0;
    //_n=-1;
}

Signal::~Signal()
{
    if(_s!=0)
        delete [] _s;
    _s=0;
    if(_f!=0)
        delete [] _f;
    _f=0;
}

void Signal::set(unsigned char *vectOctet, int fs, int l, int ba, int nc)
{
    reset();

    _fs=fs;
    _l=l/ba;    //la longueur de _s sera le nombre d'echantillon

    _s=new double[_l];

    ba/=nc;     //ba inclu tous les channel, pour recuperer l'echantillon de chaque channel

    double N;
    switch (ba) {
    case 1:
        N=1/128.0;
        break;
    case 2:
        N=1/32768.0;
        break;
    case 3:
        N=1/8388608.0;
        break;
    case 4:
        N=1/2147483648.0;
        break;
    default:
        break;
    }

    int *a=new int[nc];

    for(int i=0;i<_l;++i)
    {
        int f=i*ba*nc;

        _s[i]=0;
        for(int j=0;j<nc;++j)
        {
            a[j]=0;

            //on lit les charactere dans un int
            for(int b=0;b<ba;++b)   //un echantillon peut etre sur 1,2,3 ou 4 byte
            {
                a[j]+=vectOctet[f+b+j*3]<<(8*b);
            }
            //on voudrait avoir la moyenne des deux signal
            double d=a[j]*N;
            if(d>=1.0)
                d-=2.0; //condition necessaire si un echantillon n'est pas code sur 4 byte
            _s[i]+=d;
            if(_s[i]>=1)
                _s[i]-=2;
        }
        _s[i]/=nc;
    }

    delete [] a;
}

void Signal::reset()
{
    if(_s!=0)
        delete []_s;
    _s=0;

    if(_f!=0)
        delete [] _f;
    _f=0;

    _l=0;
    _fs=0;
    _p=-1.0;
    _fc=-1.0;
    //_n=-1;
}

double * Signal::signal()
{
    return _s;
}


void fftf(double *x, int N, int i,Complex *F) // fast fourier transform utilisant radix-2
{
   if(N==1)
   {
       *F=*x;
       return;
   }
   N/=2;
   fftf(x,N,2*i,F);
   fftf(x+i,N,2*i,F+N);

   for(int k=0;k<N;++k)
   {
       Complex t=F[k];
       double n=N;
       Complex e(-k/(2*n));
       F[k]=t+e*F[k+N];
       F[k+N]=t-e*F[k+N];
   }
   return;
}

void Signal::fourier()
{
//    if(_f!=0)                       //on cree fourier quand on la demande la premiere foi
//        return _f;
    Complex * F=new Complex[_l];
    fftf(_s,_l,1,F);

    //_f=new double[NFT];

    _p=-1.0;

    for(int i=0;i<_l/2;++i)
    {
        double m=F[i].mod();
        //double r=(1.0*_l)/_fs;

        if(m>_p)
        {
            _p=m;
            _fc=(double)i*_fs/_l;
        }

//        for(int j=0;j<NFT;++j)
//        {
//            int intf=(int)(FREQTABLE[j]*r);
//            if(i%intf==0)
//            {
//                _f[j]+=m;
//            }
//        }
    }

    delete [] F;
}

int Signal::l()
{
    return _l;
}

int Signal::fs()
{
    return _fs;
}

double Signal::p()
{
    return _p;
}

double Signal::fc()
{
    if(_fc==-1)
        fourier();
    return _fc;
}

int Signal::n()
{
//    if(_n!=-1)
//        return _n;

//    double s=-1.0;
//    fourier();
//    for(int i=0;i<NFT;++i)
//    {
//        if(_f[i]>s)
//        {
//            s=_f[i];
//            _n=i;
//        }
//    }

    //return _n;

    return 0;
}
