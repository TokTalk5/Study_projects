#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <algorithm>
#include "display.h"
#include "passanger.h" // Убедитесь, что включили заголовочный файл Passanger

class eventControl : public QWidget
{
    Q_OBJECT
    Elevator *elevator;
    display *hall;
    QSpinBox upSpinBox;
    QSpinBox downSpinBox;
    QSpinBox floorSpinBox;
    QSpinBox destFloorSpinBox; // Новое поле для ввода этажа назначения
    QLabel floorLab, upLab, downLab;
    QGridLayout layout;
    QPushButton confirmButton;
public:
    eventControl(Elevator *elevator, display *hall);
public slots:
    void generatePassangers();
    void extremeFloors(int i);
};

#endif // EVENTCONTROL_H
