#ifndef CS205_FINAL_PROJECT_BPLAYERONE_H
#define CS205_FINAL_PROJECT_BPLAYERONE_H


#include "Board.h"

class BPlayerOne : public Board{
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

    void setBoardElement(int x, int y, int cellNum, cellStatus stat);

    int cellNum(int x, int y);

    void drawBoard() override;
};


#endif //CS205_FINAL_PROJECT_BPLAYERONE_H
