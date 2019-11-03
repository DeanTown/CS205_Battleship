//
// Created by Oliver Reckord Groten on 10/22/19.
//

#include "Ship.h"
using namespace std;

/* Constructor */
Ship::Ship(int size) {
    this->size = size;
}

/* Getters */
int Ship::getSize() {
    return size;
}
bool Ship::getDestroyed() {
    return destroyed;
}

/* Setters */
void Ship::setSize(int s) {
    size = s;
}
void Ship::setDestroyed(bool d) {
    destroyed = d;
}

void Ship::addHit() {
    hits++;
}
