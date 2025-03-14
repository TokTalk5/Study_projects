#include "canvas.h"


TCanvas::TCanvas(TPaint* f, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Окно представления графа");
    s = f;
    setFixedSize(500,500);
}

TCanvas::~TCanvas()
{

}

void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    s->draw(&p);
    p.end();
}
