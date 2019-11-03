//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "Fleet.h"

Fleet::Fleet() {}

bool Fleet::sunk() {
    return carrier.getDestroyed() &&
           battleship.getDestroyed() &&
           destroyer.getDestroyed() &&
           sub.getDestroyed() &&
           cruiser.getDestroyed();
}