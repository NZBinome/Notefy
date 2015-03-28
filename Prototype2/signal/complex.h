#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
    double _arg; //arg=n*k/N
    double _re;
    double _im;

public:
    Complex();
    Complex(double arg, double mod=1.0);

    double re();
    double im();
    double mod();
    double arg();

    Complex operator=(double x);    //conversion d'un reel
    Complex operator=(Complex const &o);
    Complex operator*(Complex const &o);
    Complex operator*(double mod);
    Complex operator+(Complex const &o);
    Complex operator-(Complex const &o);
    Complex operator+=(Complex const &o);

};

Complex operator*(double mod, Complex &o);

#endif // COMPLEX_H
