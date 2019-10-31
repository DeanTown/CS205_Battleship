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

double Cell::getLength() const {
    return length;
}

double Cell::getWidth() const {
    return width;
}

double Cell::getCenterX() const {
    return position[0];
}

double Cell::getCenterY() const {
    return position[1];
}

double Cell::getLeftX() const {
    return position[0] - (getWidth() / 2.0);
}

double Cell::getRightX() const {
    return position[0] + (getWidth() / 2.0);
}

double Cell::getTopY() const {
    return position[1] - (getLength() / 2.0);
}

double Cell::getBottomY() const {
    return position[1] + (getLength() / 2.0);
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

void Cell::setLength(int len) {
    this->length = len;
}

void Cell::setWidth(int wid) {
    this->width = wid;
}

void Cell::draw_shape() {
    // outer
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX(),getTopY());
    glVertex2d(getRightX(),getTopY());
    glVertex2d(getRightX(),getBottomY());
    glVertex2d(getLeftX(),getBottomY());
    glEnd();

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 3,getTopY() + 3);
    glVertex2d(getRightX() - 3,getTopY() + 3);
    glVertex2d(getRightX() - 3,getBottomY() - 3);
    glVertex2d(getLeftX() + 3,getBottomY() - 3);
    glEnd();
}