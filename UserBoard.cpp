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
    int randDirection;

    // Check to see if that square has already been clicked
    // if it has, then the move is invalid; return false
    if (alreadyHit(randRow, randCol)) {
        return false;
    }

    // If the hits vector is empty, we don't have any previous moves
    // to go off of, so we pick a random square. If the random square has
    // not already been hit, then we "hit" it by updating the board,
    // updating the ship hit, and adding it to the hits vector
    if (hits.size() == 0) {
        updateBoard(randRow, randCol);
    }

    if (hits.size() == 1) {
        randDirection = rand() % 4;
        position miss;
        switch (randDirection) {
            case 0: // north
                randRow -= 1;
                miss.row = randRow;
                miss.col = randCol;
                if (!alreadyHit(randRow, randCol)) {
                    updateBoard(randRow, randCol);
                } else {
                    attempts.push_back(miss);
                }
                break;
            case 1: // east
                randCol += 1;
                miss.row = randRow;
                miss.col = randCol;
                if (!alreadyHit(randRow, randCol)) {
                    updateBoard(randRow, randCol);
                } else {
                    attempts.push_back(miss);
                }
                break;
            case 2: // south
                randRow += 1;
                miss.row = randRow;
                miss.col = randCol;
                if (!alreadyHit(randRow, randCol)) {
                    updateBoard(randRow, randCol);
                } else {
                    attempts.push_back(miss);
                }
                break;
            case 3: // west
                randCol -= 1;
                miss.row = randRow;
                miss.col = randCol;
                if (!alreadyHit(randRow, randCol)) {
                    updateBoard(randRow, randCol);
                } else {
                    attempts.push_back(miss);
                }
                break;
        }
        // pick a random direction
        // see if its a hit
        // if it is a hit then add to hit vector
        // if not a hit, add to attempts vector
    }

    if (hits.size() > 1) {
        int hitsSize = hits.size();
        position to = hits[hitsSize];
        position from = hits[hitsSize - 1];
        // position to check if the next logical move is in the attempts vector
        bool inAttempts;
        position check;
        // NORTH
        check.row = hits[hitsSize].row - 2;
        check.col = hits[hitsSize].col;
        for (position p : attempts) {
            if (p.row == check.row && p.col == check.col) {
                inAttempts = true;
            }
        }
        if ((from.row - to.row == -1) && (from.col - to.col == 0) && !inAttempts) {
            // north
            updateBoard(check.row, check.col);

        }
        // EAST
        check.row = hits[hitsSize].row;
        check.col = hits[hitsSize].col + 2;
        for (position p : attempts) {
            if (p.row == check.row && p.col == check.col) {
                inAttempts = true;
            }
        }
        if ((from.row - to.row == 0) && (from.col - to.col == 1) && !inAttempts) {
            // east
            updateBoard(check.row, check.col);
        }
        // SOUTH
        check.row = hits[hitsSize].row + 2;
        check.col = hits[hitsSize].col;
        for (position p : attempts) {
            if (p.row == check.row && p.col == check.col) {
                inAttempts = true;
            }
        }
        if ((from.row - to.row == 1) && (from.col - to.col == 0) && !inAttempts) {
            // south
            updateBoard(check.row, check.col);
        }
        // WEST
        check.row = hits[hitsSize].row;
        check.col = hits[hitsSize].col - 2;
        for (position p : attempts) {
            if (p.row == check.row && p.col == check.col) {
                inAttempts = true;
            }
        }
        if ((from.row - to.row == 0) && (from.col - to.col == -1) && !inAttempts) {
            // west
            updateBoard(check.row, check.col);
        }
        // find the direction of the hits
        // keep going in that direction, unless the position next in line is in the attempts vector
        // if next in line in attempts vector, go the opposite direction
    }


    return true;
}

bool UserBoard::alreadyHit(int row, int col) {
    regex r ("(*)(Hit)");
    if (regex_match(cellStatusToString(board[row][col]), r)) {
        return true;
    }
    return false;
}

void UserBoard::updateBoard(int row, int col) {
    // update board
    cellStatus tempStat = board[row][col];
    cellStatus updated = cellStatusUpdater(tempStat);
    board[row][col] = updated;
    // update ship hit
    updateShip(tempStat);
    position tempPos;
    tempPos.row = row;
    tempPos.col = col;
    // add to hits vector
    hits.push_back(tempPos);
}

void UserBoard::placePieces(){

}

void UserBoard::printBoard() {}