#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include <QFile>
#include <QTextStream>


class graph
{
protected:
    matrix<int> adjMatrix;
    int dim = 3;
public:
    graph();
    void setGraph(QString);
    int getDim();
    int getElement(int, int);

};

#endif
