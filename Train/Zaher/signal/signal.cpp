#include <cmath>
#include "complex.h"
#include "signal.h"
#include "../freq/freqtable.h"
#include "../util/util.h"
#include <string.h>
#include <stdio.h>

double const sst=1.03;   //rapport d'un quarton

extern const double PI;

Signal::Signal()
{
    _s=0;
    _l=0;
    _fs=0;
    _f=0;
    _F=0;
    _p=-1.0;
    _fc=-1.0;
    _n=-1;
    _filt=0;
    _pmax=0;
    _fmax=0;
}

Signal::~Signal()
{
    if(_s!=0)
        delete [] _s;
    _s=0;
    if(_f!=0)
        delete [] _f;
    _f=0;
    if(_F!=0)
        delete [] _F;
    _F=0;
    if(_filt!=0)
        delete [] _filt;
    _filt=0;

}

void Signal::set(unsigned char *vectOctet, int fs, int l, int ba, int nc)
{
    reset();
    if(vectOctet==0)
    {
        _fc=1.0;
        _p=1.0;
        return;
    }

    if(_l*ba!=l)   //au cas ou on reeutilise le meme vecteur
    {
        _l=l/ba;    //la longueur de _s sera le nombre d'echantillon
        if(_s!=0)
            delete [] _s;
        _s=new double[_l];
        if(_filt!=0)
            delete [] _filt;
        _filt=new double[_l];
        double il=1.0/_l;
        for(int i=0;i<_l;++i)
        {
            _filt[i]=0.54-0.46*cos(2*PI*i*il);
        }
        if(_f!=0)
            delete [] _f;
        _f=0;
        if(_F!=0)
            delete [] _F;
        _F=0;
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
                a[j]+=vectOctet[f+b+j*nc]<<(8*b);
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
    _pmax=0;
}

double * Signal::signal()
{
    return _s;
}

void Signal::fftf(double *x, int N, int i,Complex *F) // fast fourier transform utilisant radix-2
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

void Signal::filter()         //pour filtrer le son initiale pour une meilleur presence de pic des frequence harmonic
{
    for(int i=0;i<_l;++i)
        _s[i]*=_filt[i];

}

void Signal::methodeParMorceau()
{
    Freqtable * defaultFreq=Freqtable::getInstance();
    double min=defaultFreq->FREQTABLE[defaultFreq->min()];
    const int N=8;
    double fc[N];
    double fp[N];
    memset(fc,0,sizeof(fc));
    memset(fp,0,sizeof(fp));
    int n=0;

    for(int i=0;i<_l/2;++i)
    {
        _f[i]=_F[i].mod();       //on sauvegarde le module de la transformation de fourier

        double f=1.0*i*_fs/(_l*1.0);

        n=(int)(f/min)-1;
        if(n>-1&&n<N)
        {
            if(_f[i]>=fp[n])
            {
                fp[n]=_f[i];
                fc[n]=f;
            }
        }
    }


    //code important
    int dist=1;
    int val=0;
    for(int i=1;i<N/2;++i)
        val+=N-i;
    double *tab=new double[val*2];
    int ind=0;
    while(dist<N/2)
    {
        for(int i=0;i<N-dist;++i)
        {
            double diff=fc[i+dist]-fc[i];
            double prod=fp[i+dist]*fp[i];
            int j;
            for(j=0;j<ind;++j)
            {
                if(diff/tab[j]<sst&&tab[j]/diff<sst)
                {
                    tab[j+val]+=prod;
                    break;
                }
            }
            if(j==ind)
            {
                tab[j]=diff;
                tab[j+val]=prod;
                ++ind;
            }
        }
        ++dist;
    }

    _p=-1.0;
    for(int i=val;i<ind+val;++i)
    {
        if(tab[i]>_p&&tab[i-val]>min)
        {
            _p=tab[i];
            _fc=tab[i-val];
        }
    }


    double fdst=sst; //differrence frequence en semiton
    for(int i=0;i<8;++i)
    {
        fdst*=sst;
    }
    int ftd=_fc/fdst*_l/_fs;
    int ftf=_fc*fdst*_l/_fs;

    double max=0;
    int tf;


    for(int i=ftd;i<ftf;++i)
    {
        if(_f[i]>max)
        {
            max=_f[i];
            tf=i;
        }
    }

    _fc=tf*_fs*1.0/_l;

    delete [] tab;

    //fin de code important
}

void Signal::correct()
{
    int arr;
    double div;
    if(_fc!=0)
    {
        div=_fmax/_fc;
        arr=(int)div;
        if(arr+1.0-div<div-arr)
            ++arr;
        _fc=_fmax/arr;
    }
}

void Signal::correct2()
{
    double rap=(1.0*_l)/(1.0*_fs);
    int ind=(int)(_fc*rap);
    int indd=(int)(_fc*rap*(1/(sst*sst)));
    int indf=(int)(_fc*rap*sst*sst);

    for(int i=indd;i<=indf;++i)
    {
        if(_f[i]>_f[ind])
            ind=i;
    }
    _fc=1.0*ind/rap;
}

void Signal::clusters(double *pr, int n)
{  
    Freqtable *df=Freqtable::getInstance();

    double bk[]={0, 0};
    for(int i=0;i<n;++i)
    {
        int j=i;
        double k[]={0, 0};
        if(pr[i]<df->FREQTABLE[df->min()])
            continue;
        while(pr[j]/pr[i]<sst*sst*sst*sst)
        {
            k[0]+=pr[j]*pr[j+n];
            k[1]+=pr[j+n];
            if(++j>=n)
                break;
        }
        if(k[1]!=0)
            k[0]/=k[1];
        if(k[1]>bk[1])
        {
            bk[0]=k[0];
            bk[1]=k[1];
        }
//        else
//        {
//            break;
//        }
    }
    _fc=bk[0];
    _p=bk[1];
    correct2();  //slightly better result
}

void Signal::itere(double *fp, int n)
{
    int val=0;
    double apuiss=1.5;
    double pseuil=pow(_pmax,apuiss);  //puissance seuil

    Freqtable *df=Freqtable::getInstance();
    double imaxf=1.0/df->FREQTABLE[df->max()];

    for(int i=1;i<n;++i)
    {
        val+=n-i;
    }
    double *pr=new double[val*2];
    int it=0;
    //double maxValue[]={0, 0}; //0 frequence, 1 puissance

    for(int i=0;i<n-1;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            pr[it]=fp[j]-fp[i];
            pr[it+val]=fp[j+n]*fp[i+n];

            if(pr[it+val]>pseuil)
            {
                pr[it+val]*=(2-2*pr[it]*imaxf);
                ++it;
            }
//            if(pr[it+val]>maxValue[1])
//            {
//                maxValue[1]=pr[it+val];
//                maxValue[0]=pr[it];
//            }

        }
    }

    double *nfp=0;
    if(it<val)
    {
        nfp=new double[it*2];
        memcpy(nfp,pr,it*sizeof(double));
        memcpy(nfp+it,pr+val,it*sizeof(double));
        delete [] pr;
        pr=nfp;
    }
    val=it;

    Util::triRapideDouble(pr,val);
    
    clusters(pr,val);
    
    delete [] pr;
}

void Signal::methodePMIterre()
{
    Freqtable * df=Freqtable::getInstance();
    double min=df->FREQTABLE[12]-df->FREQTABLE[0];
    double max=df->FREQTABLE[df->max()];

    int n=(int)(max/min);

    double * fp;  //frequence et puissance;
    fp=new double[n*2];

    memset(fp,0,2*n*sizeof(double));
    int it=0; //iterator morceau fp

    for(int i=0;i<_l/2;++i)
    {
        _f[i]=_F[i].mod();
        double f=1.0*i*_fs/(_l*1.0);

        if(_f[i]>_pmax)
        {
            _fmax=f;
            _pmax=_f[i];
        }
        it=(int)(f/min);
        if(it<n)
        {
            if(_f[i]>=fp[it+n])
            {
                fp[it+n]=_f[i];
                fp[it]=f;
            }
        }
    }
    itere(fp,n);

    delete [] fp;
}


double * Signal::fourier()
{
    if(_fc!=-1.0)                       //on cree fourier quand on la demande la premiere foi
        return _f;
    if(_F==0)               //reeutilisation du pointeur (a tester)
        _F=new Complex[_l];

    filter();
    fftf(_s,_l,1,_F);
    if(_f==0)
        _f=new double[_l/2];

    methodePMIterre();

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
    if(_p==-1.0)
       fourier();
    if(_p<1000.0)
        return 0.0;
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

    int minf=(int)(defaultFreq->FREQTABLE[min]*ifr);
    int maxf=(int)(defaultFreq->FREQTABLE[max]*ifr);

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
        double sf=defaultFreq->FREQTABLE[min+j];
        int nbf=1+(defaultFreq->FREQTABLE[max+24]-sf)/sf;

        double p=0;
        double x=1;
        for(int i=0;i<nbf;++i)
        {
            p+=x;
            x*=0.5;
        }
        x=1;
        for(double freq=sf;freq<defaultFreq->FREQTABLE[max+24];freq+=sf)
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
    return _n;
}
