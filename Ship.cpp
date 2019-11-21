#include "Ship.h"
#include "Shapes.h"

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


void Ship::createCarrier(){
    Tangle box;
    box.setDimensions(75,22);
    box.setFillColor(112,128,144);
    box.setBorderColor(105,105,105);
    box.setCenter(160, 500);
    box.draw();


}
void Ship::createBattleship(){

    Tangle box;
    box.setDimensions(75,22);
    box.setFillColor(112,128,144);
    box.setBorderColor(105,105,105);
    box.setCenter(160, 500);
    box.draw();
}
void createCruiser();
void createSub();
void createDestroyer();