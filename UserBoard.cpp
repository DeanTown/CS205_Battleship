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

    // Check to see if that square has already been clicked
    // if it has, then the move is invalid; return false
    if (isHit(randRow, randCol)) {
        return false;
    }

    // If the hits vector is empty, we don't have any previous moves
    // to go off of, so we pick a random square. If the random square has
    // not already been hit, then we "hit" it by updating the board,
    // updating the ship hit, and adding it to the hits vector
    if (hits.size() == 0) {
        if (!isHit(randRow, randCol)) {
            // update board
            cellStatus tempStat = board[randRow][randCol];
            cellStatus updated = cellStatusUpdater(tempStat);
            board[randRow][randCol] = updated;
            // update ship hit
            updateShip(tempStat);
            position tempPos;
            tempPos.row = randRow;
            tempPos.col = randCol;
            hits.push_back(tempPos);
        }
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

bool UserBoard::isHit(int row, int col) {
    regex r ("(*)(Hit)");
    if (regex_match(cellStatusToString(board[row][col]), r)) {
        return true;
    }
    return false;
}

void UserBoard::placePieces(){

}

void UserBoard::printBoard() {}