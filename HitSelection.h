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
    vector<vector<Tangle>> hitOptions;
    Tangle window;
public:
    HitSelection();
    void draw(int width, int height);
    point getCell(int x, int y);
    bool isOverlapping(const point &p) const;
    void update(Board b);
};


#endif //CS205_FINAL_PROJECT_HITSELECTION_H