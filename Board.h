//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Cell.h"
#include "Ship.h"
#include "graphics.h"
#include <vector>

using namespace std;

class Board {
private:
    std::vector<std::vector<Cell>> board;
    int cols;
    int rows;
    vector<Ship> p1Ships;
    vector<Ship> p2Ships;
    vector<Cell> temp;


public:
    /* Constructor */
    Board();

    void draw_board();
};


#endif //CS205_FINALPROJECT_BOARD_H
