#include "rasmeh.h"
#include <QPainter>

Rasmeh::Rasmeh(double *s, int l,QWidget *parent) :
    QWidget(parent)
{
    _l=l;
    _s=new double[l];

    for(int i=0;i<l;++i)
    {
        _s[i]=s[i];
    }
}

Rasmeh::~Rasmeh()
{
    delete []_s;
}

void Rasmeh::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawLine(0,0,200,200);
    for(int i=0;i<_l;i+=2)
    {
        p.drawPoint(i/2,_s[i]*0.1+200);
    }
}
