#include "complex.h"
#include "signal.h"
#include "freq/freqtable.h"
#include <string.h>
#include <stdio.h>

Signal::Signal()
{
    _s=0;
    _l=0;
    _fs=0;
    _f=0;
    _p=-1.0;
    _fc=-1.0;
    _n=-1;
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


    if(_l*ba!=l)   //au cas ou on reeutilise le meme vecteur
    {
        _l=l/ba;    //la longueur de _s sera le nombre d'echantillon
        if(_s!=0)
            delete [] _s;
        _s=new double[_l];
    }

    _fs=fs;

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
//    if(_s!=0)
//        delete []_s;
//    _s=0;

//    if(_f!=0)
//        delete [] _f;
//    _f=0;                 c'est pas necessaire de liberer vu qu'on peut reeutiliser

    _p=-1.0;
    _fc=-1.0;
    _n=-1;
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

double * Signal::fourier()
{
    if(_fc!=-1.0)                       //on cree fourier quand on la demande la premiere foi
        return _f;
    Complex * F=new Complex[_l];
    fftf(_s,_l,1,F);

    _f=new double[_l/2];

    _p=-1.0;

    for(int i=0;i<_l/2;++i)
    {
        _f[i]=F[i].mod();       //on sauvegarde le module de la transformation de fourier

        if(_f[i]>_p)
        {
            _p=_f[i];
            _fc=(double)i*_fs/_l;
        }
    }

    Freqtable * defaultFreq=Freqtable::getInstance();
    if(_fc<FREQTABLE[defaultFreq->min()])
    {
        //3abbi red 0
    }


    delete [] F;
    return _f;
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
    if(_p!=-1.0)
        return _p;
    n();
    return _p;
}

double Signal::fc()
{
    if(_fc==-1.0)
        fourier();
    return _fc;
}

int Signal::n()
{
    if(_n!=-1)
        return _n;
    Freqtable * defaultFreq=Freqtable::getInstance();


    int min=defaultFreq->min();
    int max=defaultFreq->max();

    double ifr=(double)_l/_fs;

    double *f=fourier();

    int minf=(int)(FREQTABLE[min]*ifr);
    int maxf=(int)(FREQTABLE[max]*ifr);

    //cela ne sera pas necessaire

    /*
    double *ft=new double[max-min];
    memset(ft,0,(max-min)*sizeof(double));
    */

    //on ne memorizera qu'une seule valeur

    double ft[]={0.0, 0.0};     //en faite on memorizera 2. indice 0 est la valeur la plus grand jusqu'a maintenant
    //et indice 1 la valeur incremente

    for(int j=0;j<max-min;++j)
    {
        double sf=FREQTABLE[min+j];
        int nbf=1+(FREQTABLE[max+24]-sf)/sf;

        double p=0;
        double x=1;
        for(int i=0;i<nbf;++i)
        {
            p+=x;
            x*=0.5;
        }
        x=1;
        for(double freq=sf;freq<FREQTABLE[max+24];freq+=sf)
        {
            int d=(int)(freq*ifr);
            ft[1]+=f[d]*x*p;
            //ft[j]+=f[d]*x*p;
            x*=0.5;
        }
        if(ft[1]>ft[0])
        {
            ft[0]=ft[1];
            _n=j+min;
        }
        ft[1]=0;
    }
    _p=ft[0]*0.127;

//    for(int i=0;i<max-min;++i)
//        printf("%d  %f\n",i+min,ft[i]);



//    for(int i=min;i<max;++i)
//    {
//        double sf=FREQTABLE[defaultFreq->min()+i];


//        for(double f=sf;f<FREQTABLE[defaultFreq->max()];f+=sf)
//        {
//            ++n;

//        }
//        int vv=1+(FREQTABLE[defaultFreq->max()]-sf)/sf;
//        printf("%f  %d  %d\n",sf,n,vv);
//        n=0;
//    }
    return _n;
}
