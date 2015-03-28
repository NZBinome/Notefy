#ifndef RASMEH_H
#define RASMEH_H

#include <QWidget>
#include <QPaintEvent>

class Rasmeh : public QWidget
{
    Q_OBJECT
    double *_s;
    int _l;
public:
    explicit Rasmeh(double *s, int l, QWidget *parent = 0);
    ~Rasmeh();

protected:
    void paintEvent(QPaintEvent* e);

signals:

public slots:

};

#endif // RASMEH_H
