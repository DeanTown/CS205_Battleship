//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_USERBOARD_H
#define CS205_FINAL_PROJECT_USERBOARD_H

#include "Board.h"
#include <regex>

class UserBoard : public Board{
private:
    vector<position> hits;
    vector<position> attempts;
public:
    UserBoard();
    bool compMove();
    bool alreadyHit(int row, int col);
    void updateBoard(int row, int col);
    void placePieces();
    int getDirection(int row, int col, int size);
    bool checkClear(int row, int col, int size, int direction);
    position newPosition();
    void setBoardValues(cellStatus shipType,position pos, int size, int direction);
};


#endif //CS205_FINAL_PROJECT_USERBOARD_H
