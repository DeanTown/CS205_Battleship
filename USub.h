#ifndef CS205_FINALPROJECT_USUB_H
#define CS205_FINALPROJECT_USUB_H

#include "Fleet.h"

class USub : public Fleet{
private:
    int width = 30, height = 89;
    int centerX = 280, centerY = 500;
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
    USub* drag(USub* us, int x, int y);
};


#endif //CS205_FINALPROJECT_USUB_H