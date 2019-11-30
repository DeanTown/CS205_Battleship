#include "UBattleship.h"
#include "graphics.h"

int UBattleship::getCenterX() const {
    return centerX;
}
int UBattleship::getCenterY() const {
    return centerY;
}
int UBattleship::getLeftX() const {
    return getCenterX() - width / 2;
}
int UBattleship::getRightX() const {
    return getCenterX() + width / 2;
}
int UBattleship::getTopY() const {
    return getCenterY() - height / 2;
}
int UBattleship::getBottomY() const {
    return getCenterY() + height / 2;
}
int UBattleship::getHeight() const {
    return height;
}
int UBattleship::getWidth() const {
    return width;
}

void UBattleship::setCenterX(int x) {
    centerX = x;
}
void UBattleship::setCenterY(int y) {
    centerY = y;
}
void UBattleship::setWidth(int wi) {
    width = wi;
}
void UBattleship::setHeight(int he) {
    height = he;
}

void UBattleship::draw() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

bool UBattleship::inBoard(int lx, int rx, int ty, int by) {
    return getLeftX() > lx && getRightX() < rx && getTopY() > ty && getBottomY() < by;
}

UBattleship* UBattleship::drag(UBattleship* ub, int x, int y) {
    ub->centerX = x;
    ub->centerY = y;
    return ub;
}
