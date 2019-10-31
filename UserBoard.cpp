//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "UserBoard.h"

UserBoard::UserBoard() : Board() {}

bool UserBoard::compMove() {
    regex r ("(*)(Hit)");
    srand(time(nullptr));
    int randRow = rand() % 10;
    int randCol = rand() % 10;

    // TODO: this compare doesn't work because the board object return an enum type
    // TODO: which can't be compared to a regex string
    if (board[randRow][randCol] == r) {
        return false;
    }

    if (hits.size() == 0) {
        // create random position
        // check if the position is a hit
        // if it is then update the board and add to hit vector
    }

    if (hits.size() == 1) {
        // pick a random direction
        // see if its a hit
        // if it is a hit then add to hit vector
        // if not a hit, add to attemps vector
    }

    if (hits.size() > 1) {
        // find the direction of the hits
        // keep going in that direction, unless the position next in line is in the attempts vector
        // if next in line in attempts vector, go the opposite direction
    }


    return true;
}

void UserBoard::placePieces(){

}

void UserBoard::printBoard() {}