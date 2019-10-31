//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "Fleet.h"

Fleet::Fleet() {}

bool Fleet::sunk() {
    if (carrier.getDestroyed() &&
        battleship.getDestroyed() &&
        destroyer.getDestroyed() &&
        sub.getDestroyed() &&
        cruiser.getDestroyed()) {
        return true;
    }
    return false;
}