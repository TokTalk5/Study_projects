#include "eventcontrol.h"

eventControl::eventControl(Elevator* elev, display *hall) : QWidget{}{
    this->elevator = elev;
    this->hall = hall;

    this->floorLab.setText("Floor:");
    this->floorLab.setAlignment(Qt::AlignRight);
    this->floorSpinBox.setMinimum(1);
    this->floorSpinBox.setMaximum(9);
    this->layout.addWidget(&(this->floorLab), 0, 0);
    this->layout.addWidget(&(this->floorSpinBox), 0, 1);

    this->upLab.setText("Up:");
    this->upLab.setAlignment(Qt::AlignRight);
    this->upSpinBox.setMinimum(0);
    this->upSpinBox.setMaximum(6);
    this->layout.addWidget(&(this->upLab), 1, 0);
    this->layout.addWidget(&(this->upSpinBox), 1, 1);

    this->downLab.setText("Down:");
    this->downLab.setAlignment(Qt::AlignRight);
    this->downSpinBox.setMinimum(0);
    this->downSpinBox.setMaximum(0);
    this->layout.addWidget(&(this->downLab), 2, 0);
    this->layout.addWidget(&(this->downSpinBox), 2, 1);

    this->destFloorSpinBox.setMinimum(1);
    this->destFloorSpinBox.setMaximum(9);
    this->layout.addWidget(&(this->destFloorSpinBox), 3, 0); // Добавляем поле этажа назначения в макет

    this->confirmButton.setText("OK");

    this->layout.addWidget(&(this->confirmButton), 4, 1);

    this->setLayout(&(this->layout));

    QObject::connect(&(this->confirmButton), SIGNAL(clicked()), this, SLOT(generatePassangers()));
    QObject::connect(&(this->floorSpinBox), SIGNAL(valueChanged(int)), this, SLOT(extremeFloors(int)));
}

void eventControl::extremeFloors(int i){
    switch (i) {
        case (9):
            this->upSpinBox.setMaximum(0);
            break;
        case (1):
            this->downSpinBox.setMaximum(0);
            break;
        default:
            this->upSpinBox.setMaximum(6);
            this->downSpinBox.setMaximum(6);
    }
}

void eventControl::generatePassangers(){
    int upCount, downCount, currentFloor;
    upCount = this->upSpinBox.value();
    downCount = this->downSpinBox.value();
    currentFloor = this->floorSpinBox.value()-1;
    for (int i = 0; i < upCount; i++){
        Passanger Bob(currentFloor, LAST);
        elevator->queue[currentFloor].push_back(Bob);
        this->elevator->floors[currentFloor].setCountUp(this->elevator->floors[currentFloor].getCountUp()+1);
        Bob.setDestinationFloor(destFloorSpinBox.value()); // Установка этажа назначения для пассажира
    }

    for (int i = 0; i < downCount; i++){
        Passanger Bob(currentFloor, FIRST);
        elevator->queue[currentFloor].push_back(Bob);
        this->elevator->floors[currentFloor].setCountDown(this->elevator->floors[currentFloor].getCountDown()+1);
        Bob.setDestinationFloor(destFloorSpinBox.value()); // Установка этажа назначения для пассажира
    }
    this->hall->display1.setItem(8-currentFloor, 1,
            new QTableWidgetItem("UP: " + QString::number(this->elevator->floors[currentFloor].getCountUp()) +
                    " DOWN:" + QString::number(this->elevator->floors[currentFloor].getCountDown())));
}
