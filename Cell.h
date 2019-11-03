#ifndef CS205_FINALPROJECT_CELL_H
#define CS205_FINALPROJECT_CELL_H

#include <vector>
#include "graphics.h"

enum cellStatus {empty, occupied};

struct color {
    double red;
    double green;
    double blue;
};

struct point {
    double x;
    double y;

    point() { x = 0.0; y = 0.0; } // constructor

    point(float _x, float _y) : x(_x), y(_y) {}
};

class Cell {
private:
    bool selected;
    // A vector that contains the cells position on the board
    std::vector<int> position;
    // The status of the tile
    cellStatus status;
    int length, width, cellNumber;
    color fill;
public:
    point pts[4]; // square structure
    Cell(); // initialize constructor
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
    void draw(Cell *c); // draw square
    void drawShapeDefault();
    void drawShapeOc();
    point mouse(int x, int y); // get mouse coordintaes
    Cell* drag(Cell *c, point *mouse); // change points of sqr
};


//class Cell {
//private:
//    // Holds whether the tile has been selected before
//    bool selected;
//    // A vector that contains the cells position on the board
//    std::vector<int> position;
//    // The status of the tile
//    cellStatus status;
//    int length, width, cellNumber;
//    color fill;
//public:
//    point pts[4];
//
//    /* Constructors */
//    Cell();
//    /* Getters */
//    bool getSelected();
//    std::vector<int> getPosition();
//    cellStatus getStatus();
//    double getLength() const;
//    double getWidth() const;
//    double getCenterX() const;
//    double getCenterY() const;
//    double getLeftX() const;
//    double getRightX() const;
//    double getTopY() const;
//    double getBottomY() const;
//    int getCellNumber() const;
//    /* Setters */
//    void setSelected(bool selection);
//    void setPosition(int row, int col);
//    void setStatus(cellStatus status);
//    void setLength(int length);
//    void setWidth(int width);
//
//    void drawShapeDefault();
//    void drawShapeOc();
//};



#endif //CS205_FINALPROJECT_CELL_H
