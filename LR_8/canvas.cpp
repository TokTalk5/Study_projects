#include "canvas.h"

TCanvas::TCanvas(StateGraph f, QWidget *parent) : QWidget(parent) {
    sample = f;
    setFixedSize(640,480);
    QToolButton* someButton = new QToolButton(this);
    someButton->setGeometry(5, 5, 630, 20);
    someButton->setText("Choose graph file...");
    connect(someButton, SIGNAL(clicked()), this, SLOT(browse()));
}

void TCanvas::browse(){
    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this, ("Open File"), "", ("Graph (*grp)"));
    if (fileName != ""){
        graph g;
        g.setGraph(fileName);
        this->sample = StateGraph(g);
        repaint();
    } else return;
}

TCanvas::~TCanvas(){}

void TCanvas::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    sample.draw(&p, QRect(5, 30, 630, 450));
    p.end();
}

void TCanvas::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton)  sample.onClickedEvent(false);
    if (event->button() == Qt::RightButton) sample.onClickedEvent(true);
    update();
}

