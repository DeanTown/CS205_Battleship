//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include <string>
#include "Fleet.h"

Fleet::Fleet() {}

void Fleet::updateShip(int ship) {
    switch(ship) {
        case 1:
            destroyer.addHit();
            break;
        case 2:
            sub.addHit();
            break;
        case 3:
            carrier.addHit();
            break;
        case 4:
            cruiser.addHit();
            break;
        case 5:
            battleship.addHit();
            break;
    }
}

bool Fleet::sunk() {
    return carrier.getDestroyed() &&
           battleship.getDestroyed() &&
           destroyer.getDestroyed() &&
           sub.getDestroyed() &&
           cruiser.getDestroyed();
}