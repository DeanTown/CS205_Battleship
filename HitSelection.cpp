//
// Created by Oliver Reckord Groten on 11/21/19.
//

#include "HitSelection.h"

HitSelection::HitSelection() {
    board = Board();
}

void HitSelection::draw() {
    // draw background
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1000,0);
    glVertex2i(1000,1000);
    glVertex2i(0,1000);
    glEnd();
    // drawn cells for hit selection
    Tangle cell;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cell = Tangle(50, 50, {i*60+52,j*60+52});
            cell.draw();
        }
    }
}