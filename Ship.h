//
// Created by Oliver Reckord Groten on 10/22/19.
//

#ifndef CS205_FINALPROJECT_SHIP_H
#define CS205_FINALPROJECT_SHIP_H

#include <vector>
#include "Shapes.h"

/*
 * This class holds the ships object, which a user places and can attack.
 */

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

    Tangle carrierShipP2;
    Tangle battleShipP2;
    Tangle destroyerShipP2;
    Tangle cruiserShipP2;
    Tangle subShipP2;


    /* Constructor */
    Ship();
    Ship(int size);
    /* Getters */
    int getSize();
    bool getDestroyed();
    /* Setters */
    void setSize(int s);
    void setDestroyed(bool d);
    // gets vertical state of a ship when placing
    bool getVert();
    void setVert(bool vert);
    // allows the user to rotate a ship when placing
    void rotate();

    int getCenterX_car() const;
    int getCenterY_car() const;
    // methods to cet the center of each ship (used for dragging)
    void setCenterCarrier(int x,int y);
    void setCenterDestroyer(int x,int y);
    void setCenterCruiser(int x,int y);
    void setCenterSub(int x,int y);
    void setCenterBattle(int x,int y);
    void setCenterCarrier2(int x,int y);
    void setCenterDestroyer2(int x,int y);
    void setCenterCruiser2(int x,int y);
    void setCenterSub2(int x,int y);
    void setCenterBattle2(int x,int y);
    void setCenterY(int y);
    // adds a hit to the ship
    void addHit();
    // methods to draw each type of ship
    void drawShip_car();
    void drawShip_battle();
    void drawShip_destroyer();
    void drawShip_cruiser();
    void drawShip_sub();
    void drawShip_car2();
    void drawShip_battle2();
    void drawShip_destroyer2();
    void drawShip_cruiser2();
    void drawShip_sub2();

};


#endif //CS205_FINALPROJECT_SHIP_H
