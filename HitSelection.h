//
// Created by Oliver Reckord Groten on 11/21/19.
//

#ifndef CS205_FINAL_PROJECT_HITSELECTION_H
#define CS205_FINAL_PROJECT_HITSELECTION_H


#include "Board.h"
#include "Shapes.h"
#include "graphics.h"

class HitSelection {
private:
    Board board;
    vector<Tangle> hitOptions;
public:
    HitSelection();
    void draw(int width, int height);
    point getCell(int x, int y);
};


#endif //CS205_FINAL_PROJECT_HITSELECTION_H
