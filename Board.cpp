#include "Board.h"
using namespace std;

/* Constructor */
Board::Board() {
    cols = 10;
    rows = 10;
//    for (int i = 0; i < rows; i ++) {
//        temp.clear();
//        for (int j = 0; j < cols; j++) {
//            cell.setPosition(i, j);
//            temp.push_back(cell);
//        }
//        board.push_back(temp);
//    }
}

// getters
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
int Board::getCellX() const {
    return bde.cellX;
}
int Board::getCellY() const {
    return bde.cellY;
}
int Board::getCellNum() const {
    return bde.cellNum;

}
int Board::getCellWidth() const {
    return cellWidth;
}
cellStatus Board::getCellStat() const {
    return bde.stat;
}

// setters
void Board::setBoardElement(int x, int y, int cellNum, cellStatus stat) {
    bde.cellX = x;
    bde.cellY = y;
    bde.cellNum = cellNum;
    bde.stat = stat;
}

void Board::drawBoard() {
    cellVector.clear();
    leftX = 100;
    topY = 100;
    cellNumber = 1;
    cols = 10;
    rows = 10;

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

bool Board::updateStat(int cellNum) {
//    cout << cellVector[cellNum].cellX << "," << cellVector[cellNum].cellY << "," << cellVector[cellNum].cellNum << "," << cellVector[cellNum].stat << endl;
    setBoardElement(cellVector[cellNum].cellX,cellVector[cellNum].cellY,cellNumber,occupied);
    ocCell.push_back(bde);
    return true;
}

void Board::updateBoard() {
    for (auto & i : ocCell) {
        cell.setPosition(i.cellX,i.cellY);
        cell.setLength(cellWidth);
        cell.setWidth(cellWidth);
        if (i.stat == 0) {
            cell.drawShapeDefault();
        } else {
            cell.drawShapeOc();
        }
    }
}

int Board::cellNum(int x, int y) {
    int num = 0;
    for (auto & i : cellVector) {
        if (x < i.cellX + 15 && x > i.cellX - 15 && y > i.cellY - 15 && y < i.cellY + 15) {
            num = i.cellNum;
        }
    }
    return num;
}


//void Board::display() {
//    for (int i = 0; i < cellVector.size(); ++i) {
//        cout << cellVector[i] << endl;
//    }
//}
//
//ostream &operator << (ostream &os, const boardElement& obj) {
//    os << "cell number: " << obj.cellNum << "| cell x: " << obj.cellX << "| cell y: " << obj.cellY << "| cell stat: " << obj.stat << endl;
//    return os;
//}