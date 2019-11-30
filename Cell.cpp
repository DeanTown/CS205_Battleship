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

//int Cell::getcellNumber() const {
//    return cellNumber;
//}

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

void Cell::drawShapeDefault() {
    // outer
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX(),getTopY());
    glVertex2d(getRightX(),getTopY());
    glVertex2d(getRightX(),getBottomY());
    glVertex2d(getLeftX(),getBottomY());
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

void Cell::drawShapeOc() {
    // outer
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX(),getTopY());
    glVertex2d(getRightX(),getTopY());
    glVertex2d(getRightX(),getBottomY());
    glVertex2d(getLeftX(),getBottomY());
    glEnd();

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

void Cell::drawButton(string label) {
    // outer
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(400,150);
    glVertex2d(560,150);
    glVertex2d(560,200);
    glVertex2d(400,200);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(410,160);
    glVertex2d(550,160);
    glVertex2d(550,190);
    glVertex2d(410,190);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(420,180);
    for (char &le : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,le);
    }
}
bool Cell::inButton(int x, int y) {
    return x > 400 && x < 560 && y > 150 && y < 200;
}

void Cell::drawDone(string label) {
    // outer
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(400,250);
    glVertex2d(560,250);
    glVertex2d(560,300);
    glVertex2d(400,300);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(410,260);
    glVertex2d(550,260);
    glVertex2d(550,290);
    glVertex2d(410,290);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(465,280);
    for (char &le : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,le);
    }
}

void Cell::hoverDone(string label){
    // outer
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(390,338);
    glVertex2d(670,338);
    glVertex2d(670,340);
    glVertex2d(390,340);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(390,335);
    for (char &le : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,le);
    }
}

bool Cell::inDone(int x, int y) {
    return x > 400 && x < 560 && y > 250 && y < 300;
}