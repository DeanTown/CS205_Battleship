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

    bool isVertical;


public:
    Tangle carrierShipTang;
    Tangle battleShipTang;
    Tangle destroyerShipTang;
    Tangle cruiserShipTang;
    Tangle subShipTang;


    /* Constructor */
    Ship();
    Ship(int size);
    /* Getters */
    int getSize();
    bool getDestroyed();
    /* Setters */
    void setSize(int s);
    void setDestroyed(bool d);

    bool getVert();
    void setVert(bool vert);
    void rotate();

    int getCenterX_car() const;
    int getCenterY_car() const;

    void setCenterCarrier(int x,int y);
    void setCenterDestroyer(int x,int y);
    void setCenterCruiser(int x,int y);
    void setCenterSub(int x,int y);
    void setCenterBattle(int x,int y);
    void setCenterY(int y);

    void addHit();
    void drawShip_car();
    void drawShip_battle();
    void drawShip_destroyer();
    void drawShip_cruiser();
    void drawShip_sub();

};


#endif //CS205_FINALPROJECT_SHIP_H
