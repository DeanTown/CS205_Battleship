//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_COMPUTERBOARD_H
#define CS205_FINAL_PROJECT_COMPUTERBOARD_H

#include "Board.h"

class ComputerBoard : public Board {
private:
public:
    ComputerBoard();
    bool userMove(int row, int col);
    void placePieces();
    void printBoard();
};


#endif //CS205_FINAL_PROJECT_COMPUTERBOARD_H
