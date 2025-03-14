#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include "paint.h"

class TCanvas : public QWidget
{
    Q_OBJECT

    TPaint* s;
public:
    TCanvas(TPaint*,QWidget *parent = 0);
    ~TCanvas();

protected:
    void paintEvent(QPaintEvent*);
};

#endif // VIEWER_H
