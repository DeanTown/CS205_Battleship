#ifndef CS205_FINALPROJECT_CELL_H
#define CS205_FINALPROJECT_CELL_H

#include <vector>
#include "graphics.h"

enum cellStatus {empty, occupied};

class Cell {
private:
    // Holds whether the tile has been selected before
    bool selected;
    // A vector that contains the cells position on the board
    std::vector<int> position;
    // The status of the tile
    cellStatus status;
    int length, width, cellNumber;
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
    int getCellNumber() const;
    /* Setters */
    void setSelected(bool selection);
    void setPosition(int row, int col);
    void setStatus(cellStatus status);
    void setLength(int length);
    void setWidth(int width);

    void drawShapeDefault();
    void drawShapeOc();
};


#endif //CS205_FINALPROJECT_CELL_H
