//
// Created by Oliver Reckord Groten on 10/22/19.
//

#ifndef CS205_FINALPROJECT_PLAYER_H
#define CS205_FINALPROJECT_PLAYER_H

#include "Ship.h"
#include <vector>

class Player {
private:
    std::vector<Ship> ships;
public:
    /* Constructor */
    Player();
    /* Player move function
     * virtual function (overridden in child classes) */
    virtual void move();
};


#endif //CS205_FINALPROJECT_PLAYER_H
