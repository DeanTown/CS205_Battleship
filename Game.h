//
// Created by Harry Makovsky on 10/22/19.
//

#ifndef CS205_FINALPROJECT_GAME_H
#define CS205_FINALPROJECT_GAME_H

#include "UserBoard.h"
#include "User2Board.h"
#include "ComputerBoard.h"
using namespace std;

class Game {
private:

    UserBoard userBoard;
    User2Board user2Board;
    ComputerBoard compBoard;

public:
    /* Constructor */
    Game();
    // Get boards
    UserBoard getUserBoard();
    User2Board getUser2Board();
    ComputerBoard getComputerBoard();
    // Place ship method
    void placeShip(cellStatus ship, int x, int y, int direction);
    void placePlayer2(cellStatus ship, int x, int y, int direction);
    //To Begin and end games
    bool userMove(int row, int col);
    void compMove();
    void placePiecesDebug();
//    bool startGame();
//    void resetGame();
//    void endGame();
//    void playGame();
};


#endif //CS205_FINALPROJECT_GAME_H
