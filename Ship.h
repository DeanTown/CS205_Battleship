//
// Created by Oliver Reckord Groten on 10/22/19.
//

#ifndef CS205_FINALPROJECT_SHIP_H
#define CS205_FINALPROJECT_SHIP_H

#include <vector>

class Ship {
private:
    int size;
    int hits;
    bool destroyed;
public:
    /* Constructor */
    Ship(int size);
    /* Getters */
    int getSize();
    bool getDestroyed();
    /* Setters */
    void setSize(int s);
    void setDestroyed(bool d);
};


#endif //CS205_FINALPROJECT_SHIP_H
