#include "Board.h"

int Board::getLeftX() const {
    return leftX;
}
int Board::getRightX() const {
    return rightX;
}
int Board::getTopY() const {
    return topY;
}
int Board::getBottomY() const {
    return bottomY;
}
int Board::getCellX(int cellNum) const {
    return cellVector[cellNum].cellX;
}
int Board::getCellY(int cellNum) const {
    return cellVector[cellNum].cellY;
}
void Board::setBoardElement(int x, int y, int cellNum) {
    bde.cellX = x;
    bde.cellY = y;
    bde.cellNum = cellNum;
//    bde.stat = stat;
}

void Board::drawBoard() {
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
            setBoardElement(j,i,cellNumber);
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

int Board::cellNum(int x, int y) {
    int num = 0;
    for (auto & i : cellVector) {
        if (x <= i.cellX + 15 && x >= i.cellX - 15 && y >= i.cellY - 15 && y <= i.cellY + 15) {
            num = i.cellNum;
        }
    }
    return num;
}
