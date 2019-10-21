//
// Created by Oliver Reckord Groten on 10/21/19.
//

#include "Board.h"
using namespace std;

/* Constructor */
Board::Board() {
    cols = 10;
    rows = 10;
    Cell cell;
    vector<Cell> temp;
    for (int i = 0; i < rows; i ++) {
        temp.clear();
        for (int j = 0; j < cols; j++) {
            cell.setPosition(i, j);
            temp.push_back(cell);
        }
        board.push_back(temp);
    }
}