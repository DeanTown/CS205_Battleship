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
    UserBoard user2Board;
    ComputerBoard compBoard;

public:
    /* Constructor */
    Game();
    Game(int i);
    // Get boards
    UserBoard getUserBoard();
    UserBoard getUser2Board();
    ComputerBoard getComputerBoard();
    void setUser2Board(UserBoard temp);
    // Place ship method
    void placeShip(cellStatus ship, int x, int y, int direction);
    void placePlayer2(cellStatus ship, int x, int y, int direction);
    // To Begin and end games
    // Methods to handle userMoves
    bool userMove(int row, int col);
    bool user2Move(int row, int col);
    bool user1Move(int row, int col);

    bool compMove();
    void placePiecesDebug();
//    bool startGame();
//    void resetGame();
//    void endGame();
//    void playGame();
};


#endif //CS205_FINALPROJECT_GAME_H
