//
// Created by Oliver Reckord Groten on 10/22/19.
//

#ifndef CS205_FINALPROJECT_SHIP_H
#define CS205_FINALPROJECT_SHIP_H

#include <vector>
#include "Shapes.h"

struct Point {
    int x;
    int y;

};

class Ship {
private:
    int size;
    int hits;
    bool destroyed;
    Point shipCenter;

public:
    Tangle carrierShip;
    /* Constructor */
    Ship(int size);
    /* Getters */
    int getSize();
    bool getDestroyed();
    /* Setters */
    void setSize(int s);
    void setDestroyed(bool d);

    int getCenterX_car() const;
    int getCenterY_car() const;

    void setCenter(int x,int y);
    void setCenterY(int y);

    void addHit();
    void drawShip_car();

};


#endif //CS205_FINALPROJECT_SHIP_H
