#include "UCruiser.h"
#include "graphics.h"

int UCruiser::getCenterX() const {
    return centerX;
}
int UCruiser::getCenterY() const {
    return centerY;
}
int UCruiser::getLeftX() const {
    return getCenterX() - width / 2;
}
int UCruiser::getRightX() const {
    return getCenterX() + width / 2;
}
int UCruiser::getTopY() const {
    return getCenterY() - height / 2;
}
int UCruiser::getBottomY() const {
    return getCenterY() + height / 2;
}
int UCruiser::getHeight() const {
    return height;
}
int UCruiser::getWidth() const {
    return width;
}

void UCruiser::setCenterX(int x) {
    centerX = x;
}
void UCruiser::setCenterY(int y) {
    centerY = y;
}
void UCruiser::setWidth(int wi) {
    width = wi;
}
void UCruiser::setHeight(int he) {
    height = he;
}

void UCruiser::draw() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

bool UCruiser::inBoard(int lx, int rx, int ty, int by) {
    return getLeftX() > lx && getRightX() < rx && getTopY() > ty && getBottomY() < by;
}

UCruiser* UCruiser::drag(UCruiser* ur, int x, int y) {
    ur->centerX = x;
    ur->centerY = y;
    return ur;
}

