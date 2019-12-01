#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Cell.h"
#include "graphics.h"
#include <vector>
#include <iostream>
using namespace std;

struct boardElement {
    int cellNum;
    int cellX;
    int cellY;
};


class Board{
private:
    const int cols = 10, rows = 10;
    int cellWidth = 30, cellNumber;
    int leftX, rightX, topY, bottomY;
    Cell cell;
    vector<boardElement> cellVector;
    boardElement bde;
public:
    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;
    int getCellX(int cellNum) const;
    int getCellY(int cellNum) const;

    void setBoardElement(int x, int y, int cellNum);

    int cellNum(int x, int y);

    void drawBoard();
};


#endif //CS205_FINALPROJECT_BOARD_H
