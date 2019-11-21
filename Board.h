#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Cell.h"
#include "Ship.h"
#include "graphics.h"
#include <vector>
#include <iostream>
using namespace std;

struct boardElement {
    int cellNum;
    int cellX;
    int cellY;
    cellStatus stat;
};

class Board {
private:
    vector<Cell> boardVector;
    int cols, rows;
    int leftX, rightX, topY, bottomY, cellWidth = 30, cellNumber;
    vector<boardElement> cellVector;
    vector<boardElement> ocCell;
    Cell cell;
    boardElement bde;
//    vector<Cell> temp;


public:
    /* Constructor */
    Board();

    // getters
    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;
    int getCellNum() const;
    int getCellX() const;
    int getCellY() const;
    int getCellWidth() const;
    cellStatus getCellStat() const;

    //settet
    void setBoardElement(int x, int y, int cellNum, cellStatus stat);
    void drawBoard();
    bool updateStat(int cellNum);
    void updateBoard();
    int cellNum(int x, int y);
//    void display();
};

//ostream &operator << (ostream &os, const boardElement& obj);


#endif //CS205_FINALPROJECT_BOARD_H
