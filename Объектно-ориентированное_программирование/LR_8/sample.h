#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>
#include "graph.h"

class TSample {
protected:
    graph G;

public:
    TSample(graph);
    TSample();
    void draw(QPainter*,QRect);
    void drawLines(QPointF*, QPainter*, int i, int j, qreal);
    bool isConnected(int i, int j);

};

#endif
