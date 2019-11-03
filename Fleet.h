//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_FLEET_H
#define CS205_FINAL_PROJECT_FLEET_H

#include "Ship.h"
using namespace std;

class Fleet {
private:
    Ship carrier = Ship(5);
    Ship battleship = Ship(4);
    Ship destroyer = Ship(3);
    Ship sub = Ship(3);
    Ship cruiser = Ship(2);
public:
    Fleet();
    void updateShip(int ship);
    bool sunk();
};


#endif //CS205_FINAL_PROJECT_FLEET_H
