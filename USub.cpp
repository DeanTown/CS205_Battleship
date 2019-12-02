#include "USub.h"
#include "graphics.h"

int USub::getCenterX() const {
    return centerX;
}
int USub::getCenterY() const {
    return centerY;
}
int USub::getLeftX() const {
    return getCenterX() - width / 2;
}
int USub::getRightX() const {
    return getCenterX() + width / 2;
}
int USub::getTopY() const {
    return getCenterY() - height / 2;
}
int USub::getBottomY() const {
    return getCenterY() + height / 2;
}
int USub::getHeight() const {
    return height;
}
int USub::getWidth() const {
    return width;
}

void USub::setCenterX(int x) {
    centerX = x;
}
void USub::setCenterY(int y) {
    centerY = y;
}
void USub::setWidth(int wi) {
    width = wi;
}
void USub::setHeight(int he) {
    height = he;
}

void USub::draw() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

void USub::drawHit(int num) {
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

bool USub::inBoard(int lx, int rx, int ty, int by) {
    return getLeftX() > lx && getRightX() < rx && getTopY() > ty && getBottomY() < by;
}

USub* USub::drag(USub* us, int x, int y) {
    us->centerX = x;
    us->centerY = y;
    return us;
}

