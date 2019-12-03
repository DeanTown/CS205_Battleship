//
// Created by Oliver Reckord Groten on 10/22/19.
//

#include "Ship.h"
using namespace std;

/* Constructor */
Ship::Ship(int size) {
    this->size = size;
    hits=0;
    carrierShip = Tangle(30*5,30);
    carrierShip.setCenter(100, 470);
}

/* Getters */
int Ship::getSize() {
    return size;
}
bool Ship::getDestroyed() {
    return size==hits;
}

int Ship::getCenterX_car() const {
    return shipCenter.x;
}
int Ship::getCenterY_car() const {
    return shipCenter.y;
}

/* Setters */
void Ship::setSize(int s) {
    size = s;
}
void Ship::setDestroyed(bool d) {
    destroyed = d;
}

// setters
void Ship::setCenterX(int x) {
    shipCenter.x = x;
}
void Ship::setCenterY(int y) {
    shipCenter.y = y;
}

void Ship::addHit() {
    hits++;
}

void Ship::drawShip_car(){

    int l = 5;
//    carrierShip.setDimensions(30*l,30);
    int xC = 100;
    int yC = 470;
    carrierShip.setCenter(xC, yC);
    carrierShip.setFillColor(100,0,0);
    carrierShip.draw();
}

