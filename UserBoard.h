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
    void placePieces();
    void printBoard();
};


#endif //CS205_FINAL_PROJECT_USERBOARD_H
