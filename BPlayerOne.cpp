#include "BPlayerOne.h"

int BPlayerOne::getLeftX() const {
    return leftX;
}
int BPlayerOne::getRightX() const {
    return rightX;
}
int BPlayerOne::getTopY() const {
    return topY;
}
int BPlayerOne::getBottomY() const {
    return bottomY;
}
int BPlayerOne::getCellX(int cellNum) const {
    return cellVector[cellNum].cellX;
}
int BPlayerOne::getCellY(int cellNum) const {
    return cellVector[cellNum].cellY;
}
void BPlayerOne::setBoardElement(int x, int y, int cellNum, cellStatus stat) {
    bde.cellX = x;
    bde.cellY = y;
    bde.cellNum = cellNum;
    bde.stat = stat;
}

void BPlayerOne::drawBoard() {
    cellVector.clear();
    leftX = 100;
    topY = 100;
    cellNumber = 1;

    for (int i = topY; i < topY + cellWidth * cols; i += cellWidth) {
        for (int j = leftX; j < leftX + cellWidth * rows; j += cellWidth) {
            cell.setPosition(j,i);
            cell.setWidth(cellWidth);
            cell.setLength(cellWidth);
            cell.drawShapeDefault();
            setBoardElement(j,i,cellNumber,empty);
            cellVector.push_back(bde);
            ++cellNumber;
            bottomY = j;
        }
        rightX = i;
    }
    leftX -= cellWidth / 2;
    topY -= cellWidth / 2;
    bottomY += cellWidth / 2;
    rightX += cellWidth / 2;
}

int BPlayerOne::cellNum(int x, int y) {
    int num = 0;
    for (auto & i : cellVector) {
        if (x <= i.cellX + 15 && x >= i.cellX - 15 && y >= i.cellY - 15 && y <= i.cellY + 15) {
            num = i.cellNum;
        }
    }
    return num;
}
