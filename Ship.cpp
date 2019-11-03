#include "Ship.h"

// getters
int Ship::getCenterX() const {
    return shipCenter.x;
}
int Ship::getCenterY() const {
    return shipCenter.y;
}

// setters
void Ship::setCenterX(int x) {
    shipCenter.x = x;
}
void Ship::setCenterY(int y) {
    shipCenter.y = y;
}

void Ship::createShip(int x, int y,int size, int num) {
    for (int i = 0; i < cellSize * size; i += 30) {
        cell.setPosition(x,y + i);
        cell.setWidth(cellSize);
        cell.setLength(cellSize);
        cell.drawShapeDefault();
    }
    setCenterX(x);
    setCenterY((y - 15) + (cellSize * size / 2));
}