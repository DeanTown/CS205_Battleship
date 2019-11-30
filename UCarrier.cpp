#include "UCarrier.h"
#include "graphics.h"

int UCarrier::getCenterX() const {
    return centerX;
}
int UCarrier::getCenterY() const {
    return centerY;
}
int UCarrier::getLeftX() const {
    return getCenterX() - width / 2;
}
int UCarrier::getRightX() const {
    return getCenterX() + width / 2;
}
int UCarrier::getTopY() const {
    return getCenterY() - height / 2;
}
int UCarrier::getBottomY() const {
    return getCenterY() + height / 2;
}
int UCarrier::getWidth() const {
    return width;
}
int UCarrier::getHeight() const {
    return height;
}

void UCarrier::setCenterX(int x) {
    centerX = x;
}
void UCarrier::setCenterY(int y) {
    centerY = y;
}
void UCarrier::setWidth(int wi) {
    width = wi;
}
void UCarrier::setHeight(int he) {
    height = he;
}

void UCarrier::draw() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

bool UCarrier::inBoard(int lx, int rx, int ty, int by) {
    return getLeftX() > lx && getRightX() < rx && getTopY() > ty && getBottomY() < by;
}

UCarrier* UCarrier::drag(UCarrier* uc, int x, int y) {
    uc->centerX = x;
    uc->centerY = y;
    return uc;
}