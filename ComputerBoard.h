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
    int getDirection(int row, int col, int size);
    bool checkClear(int row, int col, int size, int direction);
    position newPosition();
    void setBoardValues(cellStatus shipType,position pos, int size, int direction);
};


#endif //CS205_FINAL_PROJECT_COMPUTERBOARD_H
