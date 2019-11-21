#ifndef CS205_FINALPROJECT_SHIP_H
#define CS205_FINALPROJECT_SHIP_H

#include <vector>
#include <iostream>
#include "Cell.h"
#include "Board.h"

using namespace std;

struct Point {
    int x;
    int y;

};

struct ShipInfo {
    Point point;
    int shipNum;
};

class Ship {
private:
    Cell cell;
    vector<Point> ship;
    int cellSize = 30, boardLength = 0, boardWidth = 0;
    Point shipCenter;
    ShipInfo info;
public:
    int getCenterX() const;
    int getCenterY() const;

    void setCenterX(int x);
    void setCenterY(int y);
    void setShipInfo(Point point, int Num);
    void createShip(int x, int y, int size, int num);
    void createCarrier();
    void createBattleship();
    void createCruiser();
    void createSub();
    void createDestroyer();
};


#endif //CS205_FINALPROJECT_SHIP_H
