#ifndef PASSANGER_H
#define PASSANGER_H

#include <random>

enum direction {
    LAST,
    FIRST
};

class Passanger
{
    int currentFloor;
    int destinationFloor;
    direction where;

public:
    Passanger();
    Passanger(int c, direction w);
    void setDestinationFloor(int d);
    int getDestFloor();
    direction getDirection() const; // Метод для получения направления
};

#endif // PASSANGER_H
