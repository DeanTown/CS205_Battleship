//
// Created by Harry Makovsky on 10/22/19.
//

#ifndef CS205_FINALPROJECT_GAME_H
#define CS205_FINALPROJECT_GAME_H

#include "UserBoard.h"
#include "ComputerBoard.h"
using namespace std;

class Game {
private:

    UserBoard userBoard;
    ComputerBoard compBoard;

public:
    /* Constructor */
    Game();
    //To Begin and end games
    bool startGame();
    void resetGame();
    void endGame();
    void playGame();
};


#endif //CS205_FINALPROJECT_GAME_H
