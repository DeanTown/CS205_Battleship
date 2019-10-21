//
// Created by Oliver Reckord Groten on 10/21/19.
//

#include "Cell.h"
using namespace std;

/* Constructors */
Cell::Cell() {
    selected = false;
    position.resize(2);
    status = empty;
}

/* Getters */
bool Cell::getSelected() {
    return selected;
}
vector<int> Cell::getPosition() {
    return position;
}
cellStatus Cell::getStatus() {
    return status;
}

/* Setters */
void Cell::setSelected(bool sel) {
    this->selected = sel;
}
void Cell::setPosition(int row, int col) {
    position[0] = row;
    position[1] = col;
}
void Cell::setStatus(cellStatus stat) {
    this->status = stat;
}