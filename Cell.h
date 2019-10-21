//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_CELL_H
#define CS205_FINALPROJECT_CELL_H

#include <vector>

enum cellStatus {empty, occupied, adjacent};

class Cell {
private:
    // Holds whether the tile has been selected before
    bool selected;
    // A vector that contains the cells position on the board
    std::vector<int> position;
    // The status of the tile
    cellStatus status;
public:
    /* Constructors */
    Cell();
    /* Getters */
    bool getSelected();
    std::vector<int> getPosition();
    cellStatus getStatus();
    /* Setters */
    void setSelected(bool selection);
    void setPosition(int row, int col);
    void setStatus(cellStatus status);
};


#endif //CS205_FINALPROJECT_CELL_H
