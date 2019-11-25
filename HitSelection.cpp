//
// Created by Oliver Reckord Groten on 11/21/19.
//

#include "HitSelection.h"

HitSelection::HitSelection() {
    // TODO: draw board cells according to whether they're hits, misses or untouched
    // draw background
    window = Tangle(1000,1000);
    window.setFillColor({0.8,0.8,0.8});
    // create each cell for hit options
    Tangle cell;
    vector<Tangle> temp;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            point p = {i,j};
            cell = Tangle(50, 50, {i*60+50,j*60+50},p);
            temp.push_back(cell);
        }
        hitOptions.push_back(temp);
        temp.clear();
    }
}

void HitSelection::draw(int width, int height) {
    window.draw();
    for (vector<Tangle> row : hitOptions) {
        for (Tangle cell : row) {
            cell.draw();
        }
    }
}

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

bool HitSelection::isOverlapping(const point &p) const {
    return window.isOverlapping(p);
}

void HitSelection::update(Board b) {
    cellStatus c;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            c = b.getCell(i,j);
            if (c == DestroyerHit || c == SubHit || c == CarrierHit
                || c == CruiserHit || c == BattleshipHit) {
                hitOptions[i][j].setFillColor({1,0,0});
            } else if (c == NothingHit) {
                hitOptions[i][j].setFillColor({0,1,0});
            }
        }
    }
}