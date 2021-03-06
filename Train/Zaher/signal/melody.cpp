#include <cmath>
#include <limits>
#include "../freq/freqtable.h"
#include "melody.h"
#include <string.h>
#include <stdio.h>
#include <fstream>

extern const double PI;

const double ilogst=12.0;   //inverse de log d'un semiton

Melody::Melody()
{
    _i=0;
    _l=0;
    _fs=0;
    _n=0;
    _gs=0;
    _tfp=0;
    _f=0;
    _p=0;
    _dp=0;
    _di=0;
    _corrected=false;
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
    _pmin=std::numeric_limits<double>::max();
}

Melody::Melody(int n, int fs)
{
    _i=0;
    _l=0;
    _fs=fs;
    _n=n;
    _gs=0;
    _tfp=0;
    _f=0;
    _p=0;
    _dp=0;
    _di=0;
    _corrected=false;
    if(_n!=0)
    {
        _tfp=new double[_n+_n+1];
        _f=_tfp;
        _p=_tfp+_n;
        _dp=new int[n];
        _tfp[_n+_n]=1.0;
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
    _pmin=std::numeric_limits<double>::max();
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
    _dp=o._dp;
    _di=o._di;
    ++_p[_n];
    ++_f[_n];
    ++_dp[_n-1];
    _g=0;
    _corrected=o._corrected;
    memcpy(_scales,o._scales,12*sizeof(int));
    _scale=-1;
    _pmax=o._pmax;
    _pmax=o._pmin;
}

Melody& Melody::operator =(Melody& o)
{
    if(_n!=0)
    {
        if(--_f[_n]==0.0)
            delete [] _f;
        if(--_p[_n]==0.0)
            delete [] _p;
        if(--_dp[_n-1]==0)
            delete [] _dp;
    }

    _i=o._i;
    _n=o._n;
    _l=o._l;
    _fs=o._fs;
    _gs=0;
    _f=o._f;
    _p=o._p;
    _dp=o._dp;
    _di=o._di;
    _corrected=o._corrected;
    if(_n!=0)
    {
        ++_p[_n];
        ++_f[_n];
        ++_dp[_n-1];
    }
    _g=0;
    memcpy(_scales,o._scales,12*sizeof(int));
    _scale=o._scale;
    _pmax=o._pmax;
    _pmin=o._pmin;
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
    f.write((char*)&_corrected,sizeof(bool));
    f.write((char*)&_di,sizeof(int));
    f.write((char*)_dp,(_di+1)*sizeof(int));
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
    if(_n!=0)
    {
        if(--_f[_n]==0.0)
            delete [] _f;
        if(--_p[_n]==0.0)
            delete [] _p;
        if(--_dp[_n-1]==0)
            delete [] _dp;
    }
    _f=new double[n+1];
    _p=new double[n+1];
    _dp=new int[n];
    _f[n]=1.0;
    _p[n]=1.0;
    _dp[n-1]=1;
    _n=n;
    _i=n;
    f.read((char*)&_l,sizeof(int));
    f.read((char*)&_fs,sizeof(int));
    f.read((char*)_f,_n*sizeof(double));
    f.read((char*)_p,_n*sizeof(double));
    f.read((char*)&_scale,sizeof(int));
    f.read((char*)_scales,12*sizeof(int));
    f.read((char*)&_corrected,sizeof(bool));
    f.read((char*)&_di,sizeof(int));
    f.read((char*)_dp,(_di+1)*sizeof(int));
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
    if(_pmin>p&&f>2.0&&_pmin>10.0)
        _pmin=p;
}

void Melody::normalize()
{
    const double midmax=127;
    const double midmin=90;
    
    double a=(midmax-midmin)/(_pmax-_pmin);
    double b=midmin-_pmin*(midmax-midmin)/(_pmax-_pmin);
    for(int i=0;i<_i;++i)
    {
        if (_f[i]>1)
        {
            _p[i]=a*_p[i]+b;
        }

    }
}

void Melody::calculDerive(int i,double &d)
{
    double nder=_p[i+1]-_p[i];
    if(nder>d&&nder>0&&d<=0)
    {
        _dp[_di++]=i+1;
    }
    d=nder;
}

void Melody::decompose()
{
    if(_dp!=0)
        return;
    _dp=new int[_n];
    double derive=0.0;
    for(int i=0;i<_n-1;++i)
    {
        calculDerive(i,derive);
    }

    //ce bloc est meme que celui a la fin de filtreBilateral
    _dp[_di++]=_n-1;
    int *dp=new int[_di+1];
    memcpy(dp,_dp,_di*sizeof(int));
    delete [] _dp;
    _dp=dp;
    _dp[_di]=1;
}

double *Melody::correct() //correction
{
    if(_f==0)
    {
        return 0;
    }
    int it=0;
    double avg=0;
    double sum=0;

    double *mFreq=new double[_di+1];
    memset(mFreq,0,(_di+1)*sizeof(double));

    for(int i=0;i<_n;++i)
    {
        if(i==_dp[it+1])
        {
            if(sum!=0.0)
                mFreq[it]=avg/sum;
            avg=sum=0;
            if(it<_di-1)
                ++it;
        }
        if(_f[i]>1.0)
        {
            avg+=_f[i];
            ++sum;
        }
    }
    it=0;
    for(int i=0;i<_n;++i)
    {
        if(i==_dp[it+1])
            ++it;
        if(_f[i]!=1.0)
            _f[i]=mFreq[it];
    }

    return mFreq;
}

void Melody::filtreBilateral(int gs)
{
    if (_f==0)
    {
        return;
    }
    double p=0.5;
    //_pmax=pow(_pmax,p);
    //_pmin=pow(_pmin,p);

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

    double derive=0.0;

    for(int i=0;i<_i;++i)
    {
        //calcul de derivee

        if(i<_i-1)
        {
            calculDerive(i,derive);
        }
        _dp[_di]=_i-1;

        //fin calcul de derivee

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

    //ce bloc est mem que celui de decompose
    ++_di;
    int *dp=new int[_di+1];
    memcpy(dp,_dp,_di*sizeof(int));
    delete [] _dp;
    _dp=dp;
    _dp[_di]=1;

    //ici on calcule directement les limites des note
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

int Melody::scaleN() const
{
    return _scale;
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

void Melody::getScal(int scl[])
{
    memcpy(scl,_scales,12*sizeof(int));
}

double * Melody::freqPow()
{
    return _tfp;
}

double * Melody::distFreq()
{
    return 0;
}

int  * Melody::distPlace()
{
    return _dp;
}

int Melody::distNum()
{
    return _di;
}


void Melody::set_fs(int fs)
{
    _fs=fs;
}

void Melody::set_tfp(double *tfp, int ns)
{
    if(_tfp!=0)
        if(--_tfp[_n+_n]==0.0)
            delete [] _tfp;
    _n=ns;
    _i=ns;

    _tfp=tfp;
    ++_tfp[_n+_n];
    _f=_tfp;
    _p=_tfp+_n;
}

void Melody::set_dp(int *dp, int di)
{
    if(_dp!=0)
        if(--_dp[_di]==0)
            delete [] _dp;

    _di=di;

    _dp=dp;
    ++_dp[_di];
}

void Melody::set_scl(int scl[])
{
    memcpy(_scales,scl,12*sizeof(int));
}

void Melody::set_scale(int cs)
{
    _scale=cs;
}

Melody::~Melody()
{
    if(_tfp!=0)
        if(--_tfp[_n+_n]==0.0)
            delete [] _tfp;
    if(_g!=0)
        delete [] _g;
    if(_dp!=0)
        if(--_dp[_di]==0)
            delete [] _dp;
}
