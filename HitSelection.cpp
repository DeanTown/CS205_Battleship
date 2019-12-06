//
// Created by Oliver Reckord Groten on 11/21/19.
//

#include "HitSelection.h"
/*
 * This method is similar to the way the userBoard and ComputerBoards are constructed.
 * They are made of rectangles with their colors representing the state that any give cell is in
 */
HitSelection::HitSelection() {
    Tangle cell;
    vector<Tangle> temp;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            point p = {i,j};
            cell = Tangle(50, 50, {i*50+200,j*50+75},p); // x: i * 30 + 115
            cell.setFillColor(0.0f, 0.5f, 1.0f);
            temp.push_back(cell);
        }
        hitOptions.push_back(temp);
        temp.clear();
    }
}
// method to draw the hitSelection board
void HitSelection::draw(int width, int height) {

    for (vector<Tangle> row : hitOptions) {
        for (Tangle cell : row) {
            cell.draw();
        }
    }
}
// method to get the cell clicked
point HitSelection::getCell(int x, int y) {
    for (vector<Tangle> row : hitOptions) {
        for (Tangle t : row) {
            if (t.isOverlapping({x, y})) {
                return t.getBoardCell();
            }
        }
    }
    return {-1,-1};
}
// method to update the board so it properly displays state of the board
void HitSelection::update(Board b) {
    cellStatus c;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            c = b.getCell(i, j);
            if (c == DestroyerHit || c == SubHit || c == CarrierHit
                || c == CruiserHit || c == BattleshipHit) {
                hitOptions[i][j].setFillColor({100, 0, 0});

            } else if (c == NothingHit) {
                hitOptions[i][j].setFillColor({0, 0, 100});

            }

        }
    }
    
}