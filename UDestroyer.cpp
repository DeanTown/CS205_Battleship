#include "UDestroyer.h"
#include "graphics.h"

int UDestroyer::getCenterX() const {
    return centerX;
}
int UDestroyer::getCenterY() const {
    return centerY;
}
int UDestroyer::getLeftX() const {
    return getCenterX() - width / 2;
}
int UDestroyer::getRightX() const {
    return getCenterX() + width / 2;
}
int UDestroyer::getTopY() const {
    return getCenterY() - height / 2;
}
int UDestroyer::getBottomY() const {
    return getCenterY() + height / 2;
}
int UDestroyer::getHeight() const {
    return height;
}
int UDestroyer::getWidth() const {
    return width;
}

void UDestroyer::setCenterX(int x) {
    centerX = x;
}
void UDestroyer::setCenterY(int y) {
    centerY = y;
}
void UDestroyer::setWidth(int wi) {
    width = wi;
}
void UDestroyer::setHeight(int he) {
    height = he;
}

void UDestroyer::draw() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

void UDestroyer::drawHit(int num) {
    glColor3f(0.0,0.0,1.0);
    switch (num){
        default:
            break;
        case 1:
            glBegin(GL_QUADS);
            glVertex2d(getLeftX() + 1,getTopY() + 1);
            glVertex2d(getRightX() - 1,getTopY() + 1);
            glVertex2d(getRightX() - 1,getTopY() + 31);
            glVertex2d(getLeftX() + 1,getTopY() + 31);
            glEnd();
            break;
        case 2:
            glBegin(GL_QUADS);
            glVertex2d(getLeftX() + 1,getTopY() + 1);
            glVertex2d(getRightX() - 1,getTopY() + 1);
            glVertex2d(getRightX() - 1,getTopY() + 61);
            glVertex2d(getLeftX() + 1,getTopY() + 61);
            glEnd();
            break;
        case 3:
            glBegin(GL_QUADS);
            glVertex2d(getLeftX() + 1,getTopY() + 1);
            glVertex2d(getRightX() - 1,getTopY() + 1);
            glVertex2d(getRightX() - 1,getBottomY() - 1);
            glVertex2d(getLeftX() + 1,getBottomY() - 1);
            glEnd();
            break;
    }
}

bool UDestroyer::inBoard(int lx, int rx, int ty, int by) {
    return getLeftX() > lx && getRightX() < rx && getTopY() > ty && getBottomY() < by;
}

UDestroyer* UDestroyer::drag(UDestroyer* ud, int x, int y) {
    ud->centerX = x;
    ud->centerY = y;
    return ud;
}
