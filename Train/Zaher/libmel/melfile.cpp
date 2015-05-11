#include "../signal/melody.h"
#include "melfile.h"
#include <string.h>
using namespace std;

MelFile::MelFile()
{
    _tfp=0;
    _dft=0;
    _dnp=0;
    _dnpqt=0;
    _lt=0;
    _fs=0;
    _ns=0;
    _cs=-2;
    _dn=0;
    _cr=0;
    _dc=false;
    _cr=false;
    _qt=false;
    _flags=0;
    _endof=0;
    _fsize=0;
}

bool MelFile::verifyChunk(const int cid, int pos, int &size)
{
    if(!_file.is_open())
        return false;
    int fcid;
    _file.seekg(pos,ios::beg);
    _file.read((char*)&fcid,sizeof(int));
    if(fcid==cid)
    {
        _file.read((char*)&size,sizeof(int));
        return true;
    }
    return false;
}

int MelFile::getToChunk(const int cid)
{
    if(!_file.is_open())
        return -1;
    int size=0;
    int fcid;
    _file.seekg(8,ios::beg);
    do
    {
        _file.seekg(size,ios::cur);
        _file.read((char*)&fcid,sizeof(int));
        _file.read((char*)&size,sizeof(int));
        if(_file.eof())
            return 0;
    }while(fcid!=cid);

    return size;
}


bool MelFile::read(char *filename)
{
    if(_file.is_open())
        return false;
    _file.open(filename,ios::binary|ios::in);
    if(!_file.is_open())
        return false;

    if(!verifyChunk(MEL,0,_fsize))
        return false;

    return true;
}

void MelFile::getInfo()
{
    int size=getToChunk(INFO);
    if(size)
    {
        _file.read((char*)&_lt,sizeof(int));
        _file.read((char*)&_fs,sizeof(int));
    }
}

void MelFile::getFreq()
{
    int size=getToChunk(FREQ);
    if(size)
    {
         myDelete(_tfp,_ns+_ns);
        _file.read((char*)&_ns,sizeof(int));
        if(_ns!=0)
        {
            _tfp=new double[_ns+_ns+1];
            _tfp[_ns+_ns]=1.0;
            _file.read((char*)_tfp,(_ns+_ns)*sizeof(double));
        }
    }
}

void MelFile::getScal()
{
    int size=getToChunk(SCAL);
    if(size)
    {
        _file.read((char*)&_cs,sizeof(int));
        if(_cs!=-2)
            _file.read((char*)_scl,12*sizeof(int));
    }
}

void MelFile::getCoqa()
{
    int size=getToChunk(COQA);
    if(size)
    {
        _file.read((char*)&_dc,sizeof(bool));
        _file.read((char*)&_cr,sizeof(bool));
        _file.read((char*)&_qt,sizeof(bool));
        _file.seekg(1,ios::cur);
        if(!_dc)
            return;

        _file.read((char*)&_dn,sizeof(int));

        myDelete(_dnp,_dn);
        _dnp=new int[_dn+1];
        _dnp[_dn]=1;
        _file.read((char*)_dnp,_dn*sizeof(int));

        if(!_cr)
            return;


        myDelete(_dft,_dn);
        _dft=new double[_dn+1];
        _dft[_dn]=1.0;

        _file.read((char*)_dft,_dn*sizeof(double));

        if(_qt)
        {
            myDelete(_dnpqt,_dn);
            _dnpqt=new int[_dn+1];
            _dnpqt[_dn+1]=1;
            _file.read((char*)_dnpqt,_dn*sizeof(int));
        }
    }
}


void MelFile::writeMEL()
{
    int t[]={MEL, 0};
    _file.write((char*)t,2*sizeof(int));
}

int MelFile::createInfo()
{
    int info=INFO;
    _file.write((char*)&info,sizeof(int));
    int s=0;
    if(_lt==0||_fs==0)
    {
        _file.write((char*)&s,sizeof(int));
        return 2*sizeof(int);
    }
    s=2*sizeof(int);
    _file.write((char*)&s,sizeof(int));
    _file.write((char*)&_lt,sizeof(int));
    _file.write((char*)&_fs,sizeof(int));

    return 2*sizeof(int)+s;
}

int MelFile::createFreq()
{
    int freq=FREQ;
    _file.write((char*)&freq,sizeof(int));
    int s=0;
    int ns2;
    if(_ns==0)
    {
        _file.write((char*)&s,sizeof(int));
        return 2*sizeof(int);
    }
    s=(_ns+_ns)*sizeof(double)+sizeof(int);
    ns2=_ns+_ns;
    _file.write((char*)&s,sizeof(int));
    _file.write((char*)&_ns,sizeof(int));
    _file.write((char*)_tfp,ns2*sizeof(double));

    return 2*sizeof(int)+s;

}

int MelFile::createScal()
{
    int scal=SCAL;
    _file.write((char*)&scal,sizeof(int));
    int s=0;
    if(_cs==-2)
    {
        _file.write((char*)&s,sizeof(int));
        return 2*sizeof(int);
    }
    s=13*sizeof(int);
    _file.write((char*)&s,sizeof(int));
    _file.write((char*)&_cs,sizeof(int));
    _file.write((char*)_scl,12*sizeof(int));

    return 2*sizeof(int)+s;
}

int MelFile::createCoqa()
{
    int coqa=COQA;
    _file.write((char*)&coqa,sizeof(int));
    int s=0;
    if(_ns==0)
    {
        _file.write((char*)&s,sizeof(int));
        return 2*sizeof(int);
    }

    s=sizeof(int);

    if(_dc)
    {
        s=2*sizeof(int)+_dn*sizeof(int);
        if(_cr)
            s+=_dn*sizeof(double);
        _file.write((char*)&s,sizeof(int));
        _file.write((char*)&_dc,sizeof(bool));
        _file.write((char*)&_cr,sizeof(bool));
        _file.write((char*)&_qt,sizeof(bool));
        char a[]={0};
        _file.write(a,sizeof(char));
        _file.write((char*)&_dn,sizeof(int));
        _file.write((char*)_dnp,_dn*sizeof(int));
        if(_cr)
            _file.write((char*)_dft,_dn*sizeof(double));

        return 2*sizeof(int)+s;
    }
    _file.write((char*)&s,sizeof(int));
    _file.write((char*)&_dc,sizeof(bool));
    _file.write((char*)&_cr,sizeof(bool));
    _file.write((char*)&_qt,sizeof(bool));
    char a[]={0};
    _file.write(a,sizeof(char));

    return 2*sizeof(int)+s;

}

void MelFile::addQuantized()
{
    _file.write((char*)_dnpqt,_dn*sizeof(int));
}

void MelFile::writeSize(int size)
{
    _file.seekg(4,ios::beg);
    _file.write((char*)&size,sizeof(int));
}


bool MelFile::create(char *filename)
{
    if(_file.is_open())
        return false;
    _file.open(filename,ios::binary|ios::out);
    if(!_file.is_open())
        return false;
    int size=0;
    writeMEL();
    size+=createInfo();
    size+=createFreq();
    size+=createScal();
    size+=createCoqa();
    writeSize(size);
    return true;

}

void MelFile::set_lt(int lt)
{
    _lt=lt;
}

void MelFile::set_fs(int fs)
{
    _fs=fs;
}

void MelFile::set_tfp(double *tfp, int ns)
{
    myDelete(_tfp,_ns+_ns);
    _ns=ns;
    _tfp=tfp;
    ++_tfp[_ns+_ns];
}

void MelFile::set_dft_dnp_dnpqt(double *dft, int *dnp, int *dnpqt, int dn)
{
    myDelete(_dft,_dn);
    myDelete(_dnp,_dn);
    myDelete(_dnpqt,_dn);
    _dn=dn;
    if(dnp!=0)
    {
        _flags|=DECO;
        _dc=true;
        _dnp=dnp;
        ++_dnp[_dn];
    }
    if(dft!=0)
    {
        _flags|=CORR;
        _cr=true;
        _dft=dft;
        ++_dft[_dn];
    }
    if(dnpqt!=0)
    {      
        set_dnpqt(dnpqt);
    }
}

void MelFile::set_dnpqt(int *dnpqt)
{
    if(_cr&&!_qt)
    {
        _flags|=QANT;
        _qt=true;
        _dnpqt=dnpqt;
        ++_dnpqt[_dn];
    }
}

void MelFile::set_scl(int scl[])
{
    choose_cs(-1);
    memcpy(_scl,scl,12*sizeof(int));
}

void MelFile::choose_cs(int cs)
{
    if(_cs==-2)
        _flags|=SCCR;
    else
        _flags|=SCCH;
    _cs=cs;
}

bool MelFile::manipulate(char *filename)
{
    if(_file.is_open())
        return false;
    _file.open(filename,ios::binary|ios::out|ios::in);
    if(!_file.is_open())
        return false;
    if(!verifyChunk(MEL,0,_fsize))
        return false;

    _file.seekg(0,ios::end);
    _endof=_file.tellg();
    _flags=0;
    return true;
}

void MelFile::flush()
{
    if(!_file.is_open())
        return ;
    int t;
    int s;
    unsigned char *buff;
    if(_flags&SCCR)
    {
        printf("sc_created\n");
        _flags|=SICH;
        s=getToChunk(SCAL);
        t=_file.tellg();
        _file.seekg(s,ios::cur);
        buff=new unsigned char[_endof-t-s];
        _file.read((char*)buff,_endof-t-s);
        _file.seekp(t-8,ios::beg);
        createScal();
        _file.write((char*)buff,_endof-t-s);
        delete [] buff;
    }
    if(_flags&SCCH)
    {
        printf("sc_changed\n");
        s=getToChunk(SCAL);
        _file.seekg(-8,ios::cur);
        createScal();
    }
    if((_flags&CORR)||(_flags&DECO))
    {
        printf("corrected\n");
        _flags|=SICH;
        s=getToChunk(COQA);
        t=_file.tellg();
        _file.seekg(s,ios::cur);
        buff=new unsigned char[_endof-t-s];
        _file.read((char*)buff,_endof-t-s);
        _file.seekp(t-8,ios::beg);
        createCoqa();
        if(_flags&QANT)
        {
            printf("quantized\n");
            addQuantized();
        }
        _file.write((char*)buff,_endof-t-s);
        delete [] buff;

    }
    if(_flags&SICH)
    {
        int s=0;
        s+=getToChunk(FREQ);
        s+=getToChunk(SCAL);
        s+=getToChunk(INFO);
        s+=getToChunk(COQA);
        writeSize(s);
    }
}

void MelFile::close()
{
    _file.close();
}

void MelFile::getScal(int scl[])
{
    memcpy(scl,_scl,12*sizeof(int));
}

double * MelFile::freqPow()
{
    return _tfp;
}

double * MelFile::distFreq()
{
    return _dft;
}

int * MelFile::distPlace(bool qt)
{
    if(qt&&_qt)
    {
        return _dnpqt;
    }
    return _dnp;
}

int MelFile::lenghTime()const
{
    return _lt;
}

int MelFile::sampleRate()const
{
    return _fs;
}

int MelFile::numSample()const
{
    return _ns;
}

int MelFile::numDistNote()const
{
    return _dn;
}

int MelFile::currScaleN()const
{
    return _cs;
}

int MelFile::currScale()const
{
    if(_cs==-1)
        return _cs;
    return _scl[_cs];
}

bool MelFile::isDecomposed()const
{
    return _dc;
}

bool MelFile::isCorrected()const
{
    return _cr;
}

bool MelFile::isQuantized()const
{
    return _qt;
}


void MelFile::myDelete(double *&p, int size)
{
    if(p!=0)
    {
        if(--p[size]==0.0)
        {
            delete [] p;
            p=0;
        }
    }
}
void MelFile::myDelete(int *&p, int size)
{
    if(p!=0)
    {
        if(--p[size]==0)
        {
            delete [] p;
            p=0;
        }
    }
}


void MelFile::getFrom(Melody &m)
{
    set_tfp(m.freqPow(),m.n());
    set_dft_dnp_dnpqt(m.distFreq(),m.distPlace(),0,m.distNum());
    set_fs(m.fs());
    set_lt(m.l());
    int scl[12];
    m.getScal(scl);
    set_scl(scl);
}

void MelFile::writeTo(Melody &m)
{
    m.set_l(_lt);
    m.set_fs(_fs);
    if(_cr)
    {
        //something about the melody
        if(_qt)
        {
            m.set_dp(_dnpqt,_dn);
        }
        else
        {
            m.set_dp(_dnp,_dn);
        }

        double *tfp=new double[_ns+_ns+1];
        tfp[_ns+_ns]=0.0;
        int it=0;

        for(int i=0;i<_ns;++i)
        {
            if(i==_dnp[it+1])
                ++it;
            tfp[i]=_tfp[i];
            if(tfp[i]!=1.0)
                tfp[i]=_dft[it];
        }
        for(int i=_ns;i<_ns+_ns;++i)
        {
            tfp[i]=_tfp[i];
        }

        m.set_tfp(tfp,_ns);

    }
    else
    {
        m.set_tfp(_tfp,_ns);
    }
    m.set_scl(_scl);
    m.set_scale(_cs);
}

MelFile::~MelFile()
{
    if(_file.is_open())
        _file.close();
    if(_tfp!=0)
    {
        if(--_tfp[_ns+_ns]==0.0)
            delete [] _tfp;
    }
    if(_dft!=0)
    {
        if(--_dft[_dn]==0.0)
            delete [] _dft;
    }
    if(_dnp!=0)
    {
        if(--_dnp[_dn]==0)
            delete [] _dnp;
    }
    if(_dnpqt!=0)
    {
        if(--_dnpqt[_dn]==0)
            delete [] _dnpqt;
    }
}
