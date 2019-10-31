//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "ComputerBoard.h"

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

void ComputerBoard::placePieces() {
    int placed = 0;
    while (placed < 5) {
        placed++;
    }
}