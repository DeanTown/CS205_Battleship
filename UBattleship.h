#ifndef CS205_FINALPROJECT_UBATTLESHIP_H
#define CS205_FINALPROJECT_UBATTLESHIP_H

#include "Fleet.h"

class UBattleship : public Fleet{
private:
    int width = 30, height = 119;
    int centerX = 160, centerY = 500;
public:
    // getters
    int getCenterX() const;
    int getCenterY() const;
    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;
    int getWidth() const;
    int getHeight() const;

    // setters
    void setCenterX(int x);
    void setCenterY(int y);
    void setWidth(int wi);
    void setHeight(int he);

    void draw();
    bool inBoard(int lx, int rx, int ty, int by);
    UBattleship* drag(UBattleship* ub, int x, int y);

};



#endif //CS205_FINALPROJECT_UBATTLESHIP_H
