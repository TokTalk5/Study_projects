#include "paint.h"
#include <math.h>

TPaint::TPaint()
{
}

void TPaint::setGraph(QVector <QVector<int>> s)
{
    graph = s;
}

void TPaint::draw(QPainter* painter)
{

    count = graph.size();
    QRect window(0,0,500,500);
    qreal cwidth = 0.5*window.width();
    qreal cheight = 0.5*window.height();
    qreal cwindow = 0.9*(cwidth>cheight?cheight:cwidth);
    qreal angelVertices = 2.0*acos(-1.0)/count;
    QPointF *pointArrow = new QPointF[count];
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    painter->setFont(font);

    for (int i = 0; i<count; ++i)
    {
        QString str;
        pointArrow[i] = QPointF(cwidth+cwindow*sin(i*angelVertices),cheight-cwindow*cos(i*angelVertices));
        painter->drawEllipse(QPointF(cwidth+cwindow*sin(i*angelVertices),cheight-cwindow*cos(i*angelVertices)),25,25);
        painter->drawText(QPointF(cwidth+cwindow*sin(i*angelVertices)-6,cheight-cwindow*cos(i*angelVertices)+6),str.setNum(i+1));
    }

    for(int i = 0; i < graph.size(); ++i)
    {
        for(int j = 0; j < graph.size(); ++j)
        {
            if(graph[i][j] == 1)
            {
                painter->drawText(QPointF(cwidth+cwindow*sin(i*angelVertices)+4,cheight-cwindow*cos(i*angelVertices)),"*");
                QPoint edge1, edge2;
                edge1.setX(int(pointArrow[i].x()));
                edge1.setY(int(pointArrow[i].y()));
                edge2.setX(int(pointArrow[j].x()));
                edge2.setY(int(pointArrow[j].y()));
                if(edge1.x() < edge2.x())
                {
                    if(edge1.y() == edge2.y())
                    {
                        edge1.setX(pointArrow[i].x()+25);
                        edge2.setX(pointArrow[j].x()-25);
                    }
                    else
                    {
                        edge1.setX(pointArrow[i].x()+18);
                        edge2.setX(pointArrow[j].x()-18);
                    }
                }
                if(edge1.x() > edge2.x())
                {
                    if(edge1.y() == edge2.y())
                    {
                        edge1.setX(pointArrow[i].x()-25);
                        edge2.setX(pointArrow[j].x()+25);
                    }
                    else
                    {
                        edge1.setX(pointArrow[i].x()-18);
                        edge2.setX(pointArrow[j].x()+18);
                    }
                }
                if(edge1.y() < edge2.y())
                {
                    if(edge1.x() == edge2.x())
                    {
                        edge1.setY(pointArrow[i].y()+25);
                        edge2.setY(pointArrow[j].y()-25);
                    }
                    else
                    {
                        edge1.setY(pointArrow[i].y()+18);
                        edge2.setY(pointArrow[j].y()-18);
                    }
                }
                if(edge1.y() > edge2.y())
                {
                    if(edge1.x() == edge2.x())
                    {
                        edge1.setY(pointArrow[i].y()-25);
                        edge2.setY(pointArrow[j].y()+25);
                    }
                    else
                    {
                        edge1.setY(pointArrow[i].y()-18);
                        edge2.setY(pointArrow[j].y()+18);
                    }
                }
                QLineF line(edge2,edge1);
                qreal arrowSize = 10;
                double angle = std::atan2(-line.dy(), line.dx());
                QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
                QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
                QPolygonF arrowHead;
                arrowHead.clear();
                arrowHead << line.p1() << arrowP1 << arrowP2;
                painter->drawLine(edge1,edge2);
                painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
                painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
                if(i!=j)
                {
                    painter->drawPolygon(arrowHead);
                }
            }
        }
    }

    delete [] pointArrow;
}
