#include "passanger.h"
#include <random>

Passanger::Passanger() : currentFloor(0), destinationFloor(0), where(LAST) {} // Предполагается, что пассажиры всегда движутся к последнему этажу, если этаж назначения не указан

Passanger::Passanger(int c, direction w) : currentFloor(c), where(w), destinationFloor(0) {} // Этаж назначения теперь не генерируется

void Passanger::setDestinationFloor(int d) {
    destinationFloor = d;
}

int Passanger::getDestFloor() {
    return destinationFloor;
}

direction Passanger::getDirection() const {
    return where;
}
