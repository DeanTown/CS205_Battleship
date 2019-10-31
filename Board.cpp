//
// Created by Oliver Reckord Groten on 10/21/19.
//

#include "Board.h"
using namespace std;

/* Constructor */
Board::Board() {
    fleet= Fleet();
    cols = 10;
    rows = 10;
    board.resize(rows);
    for (vector<cellStatus> row : board) {
        row.resize(cols);
    }
}

void printBoard(){

}
