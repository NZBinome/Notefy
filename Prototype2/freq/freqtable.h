#ifndef FREQTABLE_H
#define FREQTABLE_H

const int NFT=108;
const double FREQTABLE[NFT]=
{
    16.35,
    17.32,
    18.35,
    19.45,
    20.6,
    21.83,
    23.12,
    24.5,
    25.96,
    27.5,
    29.14,
    30.87,
    32.7,
    34.65,
    36.71,
    38.89,
    41.2,
    43.65,
    46.25,
    49.0,
    51.91,
    55.0,
    58.27,
    61.74,
    65.41,
    69.3,
    73.42,
    77.78,
    82.41,
    87.31,
    92.5,
    98.0,
    103.83,
    110.0,
    116.54,
    123.47,
    130.81,
    138.59,
    146.83,
    155.56,
    164.81,
    174.61,
    185.0,
    196.0,
    207.65,
    220.0,
    233.08,
    246.94,
    261.63,
    277.18,
    293.66,
    311.13,
    329.63,
    349.23,
    369.99,
    392.0,
    415.3,
    440.0,
    466.16,
    493.88,
    523.25,
    554.37,
    587.33,
    622.25,
    659.25,
    698.46,
    739.99,
    783.99,
    830.61,
    880.0,
    932.33,
    987.77,
    1046.5,
    1108.73,
    1174.66,
    1244.51,
    1318.51,
    1396.91,
    1479.98,
    1567.98,
    1661.22,
    1760.0,
    1864.66,
    1975.53,
    2093.0,
    2217.46,
    2349.32,
    2489.02,
    2637.02,
    2793.83,
    2959.96,
    3135.96,
    3322.44,
    3520.0,
    3729.31,
    3951.07,
    4186.01,
    4434.92,
    4698.63,
    4978.03,
    5274.04,
    5587.65,
    5919.91,
    6271.93,
    6644.88,
    7040.0,
    7458.62,
    7902.13
};

const double FACTTABLE[NFT]=
{
    0.00207039,
    0.00219298,
    0.00232558,
    0.00246305,
    0.00261097,
    0.00277008,
    0.00293255,
    0.00310559,
    0.00328947,
    0.00348432,
    0.00369004,
    0.00392157,
    0.00414938,
    0.00438596,
    0.00465116,
    0.00492611,
    0.0052356,
    0.00552486,
    0.00588235,
    0.00621118,
    0.00657895,
    0.00699301,
    0.00740741,
    0.00787402,
    0.00833333,
    0.00877193,
    0.00934579,
    0.00990099,
    0.0105263,
    0.0111111,
    0.0117647,
    0.0125,
    0.0131579,
    0.0140845,
    0.0149254,
    0.015625,
    0.0166667,
    0.0175439,
    0.0188679,
    0.02,
    0.0212766,
    0.0222222,
    0.0238095,
    0.025,
    0.0263158,
    0.0285714,
    0.030303,
    0.03125,
    0.0333333,
    0.0357143,
    0.0384615,
    0.04,
    0.0434783,
    0.0454545,
    0.047619,
    0.05,
    0.0526316,
    0.0588235,
    0.0625,
    0.0625,
    0.0666667,
    0.0714286,
    0.0769231,
    0.0833333,
    0.0909091,
    0.0909091,
    0.1,
    0.1,
    0.111111,
    0.125,
    0.125,
    0.142857,
    0.142857,
    0.142857,
    0.166667,
    0.166667,
    0.2,
    0.2,
    0.2,
    0.2,
    0.25,
    0.25,
    0.25,
    0.25,
    0.333333,
    0.333333,
    0.333333,
    0.333333,
    0.5,
    0.5,
    0.5,
    0.5,
    0.5,
    0.5,
    0.5,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0
};

class Freqtable
{
    static Freqtable * single;

    int _minFreq;
    int _maxFreq;

    Freqtable(int minValue, int maxValue);

public:
    static Freqtable * getInstance();
    int min();
    int max();

    void setMin(int minValue);
    void setMax(int maxValue);
    void set(int minValue, int maxValue);
};

#endif // FREQTABLE_H