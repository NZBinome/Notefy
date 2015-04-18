#ifndef MELFILE_H
#define MELFILE_H

#include <fstream>

class MelFile
{
    std::fstream _file;
    int _scl[12];     //table of errors to scales, size 12. must copy
    double * _tfp;  //table of freq and pow, size (ns)*2+1 for sharing enabling.
    double * _dft;  //distinguished frequency table size dn+1 for sharing enabling.
    int * _dnp;     //distinguished note placement, size dn+1 for sharing enabling.
    int * _dnpqt;   //distinguished note quantized placement. ""
    int _lt;   //lenght time
    int _fs;    //sample rate
    int _ns;    //nb of samples (warning these sample are in lenght time of sample rate)
    int _cs;    //current scale
    int _dn;    //number of distinguished notes
    bool _dc;   //if melodie decomposed
    bool _cr;   //if melodie corrected
    bool _qt;   //if melodie quantized

    static const int MEL=0x204c454d;
    static const int INFO=0x4f464e49;
    static const int FREQ=0x51455246;
    static const int SCAL=0x4c414353;
    static const int COQA=0x41514f43;

    int getToChunk(const int cid);
    bool verifyChunk(const int cid, int pos);


    //simplyfi

    void myDelete(double *&p, int size);
    void myDelete(int *&p, int size);

    //end


    //functions used in melFile creation

    void writeMEL();
    int createInfo();
    int createFreq();
    int createScal();
    int createCoqa();
    void writeSize(int size);

    //end of functions used in melFile creation

    MelFile(MelFile const &o);
    MelFile& operator =(MelFile const &o);

public:


    MelFile();

    bool read(char* filename);

    void getInfo();
    void getFreq();
    void getScal();
    void getCoqa();


    bool create(char* filename);

    void set_lt(int lt);
    void set_fs(int fs);
    void set_tfp(double *tfp, int ns);
    void set_dft_dnp_dnpqt(double *dft, int *dnp, int *dnpqt, int dn);
    void set_dnpqt(int *dnpqt);
    void set_scl(int scl[]);
    void choose_cs(int cs);


    bool manipulate(char *filename);


    void close();

    void getScal(int scl[]);
    double * freqPow();       //this class is not responsible of sharing,
    double * distFreq();
    int *distPlace(bool qt);

    int lenghTime()const;
    int sampleRate()const;
    int numSample()const;
    int currScaleN()const;
    int currScale()const;
    int numDistNote()const;
    bool isDecomposed()const;
    bool isCorrected()const;
    bool isQuantized()const;


    void getFrom(Melody &m);
    void writeTo(Melody &m);


    ~MelFile();
};

#endif // MELFILE_H
