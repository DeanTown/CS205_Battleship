//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_USERBOARD_H
#define CS205_FINAL_PROJECT_USERBOARD_H

#include "Board.h"


class UserBoard : public Board{
private:
public:
    UserBoard();
    void placePieces();
    bool compMove();



};


#endif //CS205_FINAL_PROJECT_USERBOARD_H
