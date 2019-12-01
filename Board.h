#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Cell.h"
#include "graphics.h"
#include <vector>
#include <iostream>
using namespace std;

struct boardElement {
    int cellNum;
    int cellX;
    int cellY;
    cellStatus stat;
};

class Board {
private:

    vector<boardElement> ocCell;


public:

    virtual void drawBoard() = 0;
//    void display();
};

#endif //CS205_FINALPROJECT_BOARD_H
