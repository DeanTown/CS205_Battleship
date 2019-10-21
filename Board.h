//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Cell.h"
#include <vector>

class Board {
private:
    std::vector<std::vector<Cell>> board;
    int cols;
    int rows;
public:
    /* Constructor */
    Board();
};


#endif //CS205_FINALPROJECT_BOARD_H
