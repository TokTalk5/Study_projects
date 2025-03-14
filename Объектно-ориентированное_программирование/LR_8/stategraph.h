#ifndef STATEGRAPH_H
#define STATEGRAPH_H

#include "sample.h"
#include <math.h>

class StateGraph : public TSample
{
    int selected;
public:
    StateGraph(graph g);
    void draw(QPainter*,QRect);
    void onClickedEvent(bool);
    StateGraph();

};

#endif // STATEGRAPH_H
