#ifndef CS205_FINALPROJECT_UCARRIER_H
#define CS205_FINALPROJECT_UCARRIER_H

#include "Fleet.h"

class UCarrier : public Fleet{
private:
    int width = 30, height = 149;
    int centerX = 100, centerY = 500;
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
    void drawHit(int num);
    bool inBoard(int lx, int rx, int ty, int by);
    UCarrier* drag(UCarrier* uc, int x, int y);


};


#endif //CS205_FINALPROJECT_UCARRIER_H
