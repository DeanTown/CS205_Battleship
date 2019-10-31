//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_CELL_H
#define CS205_FINALPROJECT_CELL_H

#include <vector>
#include "graphics.h"

enum cellStatus {empty, occupied, adjacent};

struct color {
    double red;
    double green;
    double blue;
};

struct point {
    double x;
    double y;
};

class Cell {
private:
    // Holds whether the tile has been selected before
    bool selected;
    // A vector that contains the cells position on the board
    std::vector<int> position;
    // The status of the tile
    cellStatus status;
    int length, width;
    color fill;
    point center;
public:
    /* Constructors */
    Cell();
    /* Getters */
    bool getSelected();
    std::vector<int> getPosition();
    cellStatus getStatus();
    double getLength() const;
    double getWidth() const;
    double getCenterX() const;
    double getCenterY() const;
    double getLeftX() const;
    double getRightX() const;
    double getTopY() const;
    double getBottomY() const;
    /* Setters */
    void setSelected(bool selection);
    void setPosition(int row, int col);
    void setStatus(cellStatus status);
    void setLength(int length);
    void setWidth(int width);

    void draw_shape();
};


#endif //CS205_FINALPROJECT_CELL_H
