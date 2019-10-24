//
// Created by Harry Makovsky on 10/22/19.
//

#ifndef CS205_FINALPROJECT_GAME_H
#define CS205_FINALPROJECT_GAME_H

#include "Player.h"
#include "Board.h"
using namespace std;

class Game {
private:
    Player player1;
    Player player2;
    Board gameBoard;
    bool p1Turn;
    bool p2Turn;
public:
    /* Constructor */
    Game();
    //To Begin and end games
    void startGame();
    void resetGame();
    void endGame();
    void playGame();
};


#endif //CS205_FINALPROJECT_GAME_H
