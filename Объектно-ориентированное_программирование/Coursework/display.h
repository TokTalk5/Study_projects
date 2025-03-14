#ifndef DISPLAY_H
#define DISPLAY_H

#include <QTableWidget>
#include <QHeaderView>
#include "elevator.h"

class display : public QWidget
{
    Q_OBJECT

    Elevator *first;
    QHBoxLayout layout;
public:
    QTableWidget display1;
    display(Elevator *uno);

public slots:
    void redraw(int floor, int dir);
    void release(int floor, int dir);
    void take(int floor);
};

#endif // DISPLAY_H
