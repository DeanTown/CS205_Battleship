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

public:
    // constructor
    HitSelection();
    // draw method
    void draw(int width, int height);
    // method to get the cell on the board that was clicked
    point getCell(int x, int y);
    // method to update the board to reflect the cell chosen
    void update(Board b);
};


#endif //CS205_FINAL_PROJECT_HITSELECTION_H
