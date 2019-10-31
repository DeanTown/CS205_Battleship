//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Ship.h"
#include "graphics.h"
#include <vector>
using namespace std;

enum cellStatus {Destroyer, DestroyerHit, DestroyerSunk};

class Board {
private:
    std::vector<std::vector<cellStatus>> board;
    int cols;
    int rows;
    Fleet fleet;
public:
    /* Constructor */
    Board();
//    void draw_board();
};


#endif //CS205_FINALPROJECT_BOARD_H
