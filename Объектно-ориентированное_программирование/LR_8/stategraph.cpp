#include "stategraph.h"

StateGraph::StateGraph()
{
    this->selected = 0;
}

StateGraph::StateGraph(graph g)
{
    this->selected = 0;
    this->G = g;
}

void StateGraph::draw(QPainter* painter, QRect window){
    TSample::draw(painter, window);

    int count = this->G.getDim();
    qreal pSize = 20;
    if (count > 33 && count <= 66) pSize = 10;
    else if (count > 66) pSize = 5;

    qreal cw = 0.5*window.width();
    qreal ch = 0.5*window.height() + 15;
    qreal cr = (cw>ch?ch:cw) - 2*pSize - 50;
    qreal a = 2.0*acos(-1.0)/this->G.getDim();
    QPointF t(cw+cr*sin(this->selected*a),ch-cr*cos(this->selected*a));
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::cyan));
    painter->drawEllipse(t,20,20);

    painter->drawText(QRectF(t.x()-pSize,t.y()-pSize, 2.0*pSize,2.0*pSize),
                      QString().setNum(this->selected+1), QTextOption(Qt::AlignCenter));
}

void StateGraph::onClickedEvent(bool direction){
    if (direction) this->selected++;
    else this->selected = --this->selected + this->G.getDim();
    this->selected = this->selected % this->G.getDim();
}
