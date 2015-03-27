#include "complex.h"
#include <cmath>

extern const double PI=acos(-1.0);

Complex::Complex()
{
    _arg=0;
    _re=0;
    _im=0;
}

Complex::Complex(double arg, double mod)
{
    _arg=arg;
    _re=mod*cos(2*PI*_arg);
    _im=mod*sin(2*PI*_arg);
}

double Complex::re()
{
    return _re;
}

double Complex::im()
{
    return _im;
}

double Complex::mod()
{
   return sqrt(_re*_re+_im*_im);
}

double Complex::arg()
{
    return _arg;
}

Complex Complex::operator =(double x)
{
    _re=x;
    _arg=0;
    _im=0;

    return *this;
}

Complex Complex::operator =(Complex const &o)
{
    _re=o._re;
    _im=o._im;
    _arg=o._arg;

    return *this;
}

Complex Complex::operator *(double mod)
{
    Complex r(*this);
    r._re*=mod;
    r._im*=mod;

    return r;
}

Complex Complex::operator *(Complex const &o)
{
    Complex r;
    r._im=(*this)._im*o._re+(*this)._re*o._im;
    r._re=(*this)._re*o._re-(*this)._im*o._im;

    return r;
}

Complex Complex::operator +(Complex const &o)
{
    Complex r(*this);
    r._im+=o._im;
    r._re+=o._re;
    //calcule d'arg a faire

    return r;
}

Complex Complex::operator -(Complex const &o)
{
    Complex r(*this);
    r._im-=o._im;
    r._re-=o._re;

    return r;
}

Complex Complex::operator +=(Complex const &o)
{
    this->_re+=o._re;
    this->_im+=o._im;

    return *this;
}

Complex operator *(double mod, Complex &o)
{
    return o*mod;
}
