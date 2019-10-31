//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "ComputerBoard.h"
#include <iostream>

/*
 * This method handles the user move on the computers board.
 * The basic logic which is repeated is to check if the cell clicked contains something.
 * If it does, then it marks it as hit. If it has already been hit, it rejects the move
 * and returns false.
 */
bool ComputerBoard::userMove(int row, int col) {
    // get cell status
    cellStatus c = board[row][col];
    // cell contains destroyer
    if (c == Destroyer) {
        board[row][col] = DestroyerHit;
        // go into ship class and increment hit
    } else if (c == DestroyerHit) {
        return false;
    }
    // cell contains sub
    if (c == Sub) {
        board[row][col] = SubHit;
    } else if (c == SubHit) {
        return false;
    }
    // cell contains carrier
    if (c == Carrier) {
        board[row][col] = CarrierHit;
    } else if (c == CarrierHit) {
        return false;
    }
    // cell contains cruiser
    if (c == Cruiser) {
        board[row][col] = CruiserHit;
    } else if (c == CruiserHit) {
        return false;
    }
    // cell contains battleship
    if (c == Battleship) {
        board[row][col] = BattleshipHit;
    } else if (c == BattleshipHit) {
        return false;
    }
    // cell contains nothing
    if (c == Nothing) {
        board[row][col] = NothingHit;
    } else if (c == NothingHit) {
        return false;
    }
    return true;
}

/*
 * generate some random integers for the row and column
 * if the cell at that integer is Nothing AND all the cells surrounding it within
 * the length of the ship placed is Nothing, then change all the cells to be that
 * specific ship.
 * Another random int to determine direction that the ship is generated in. if the random
 * position of the ship is too close to one side for it to face that way, then narrow the
 * choices for facing direction.
 */
void ComputerBoard::placePieces() {
    // Initialize random object
    srand(time(nullptr));
    int placed = 0;
    while (placed < 5) {
        // generate random number between 0 and 9 for row
        int randomRow = rand() % 10;
        // generate random number between 0 and 9 for col
        int randomCol = rand() % 10;
        if (board[randomRow][randomCol] == Nothing) {

        }
        placed++;
    }
}

void ComputerBoard::printBoard() {
    for (vector<cellStatus> row : board) {
        for (cellStatus col : row) {
            cout << " | " << col << " | " << endl;
        }
    }
}