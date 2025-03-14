#ifndef PAINT_H
#define PAINT_H

#include <QPainter>

class TPaint
{
    int count;
     QVector <QVector<int>> graph;
public:
    void setGraph(QVector <QVector<int>>);
    TPaint();
    void draw(QPainter*);
};

#endif // PAINT_H
