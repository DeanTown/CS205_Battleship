//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_COMPUTERBOARD_H
#define CS205_FINAL_PROJECT_COMPUTERBOARD_H

#include "Board.h"
/*
 * This class handles the ComputerBoard and the user moves
 */
class ComputerBoard : public Board {
private:
public:
    vector<vector<Tangle>> cells;
    ComputerBoard();
    // alternate constructor for secondary game mode
    ComputerBoard(int forPlayer2);
    // method that handles a user move, including all exception handling
    bool userMove(int row, int col);
    // method to automatically place computer's pieces on the board
    void placePieces();
    void draw();
    // helper methods for placePieces
    int getDirection(int row, int col, int size);
    bool checkClear(int row, int col, int size, int direction);
    position newPosition();
    void setBoardValues(cellStatus shipType,position pos, int size, int direction);
};


#endif //CS205_FINAL_PROJECT_COMPUTERBOARD_H
