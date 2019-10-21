//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_CELL_H
#define CS205_FINALPROJECT_CELL_H

#include <vector>

enum cellStatus {empty, occupied, adjacent};

class Cell {
private:
    bool selected;
    std::vector<int> position;
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
    void setPosition(std::vector<int> &position);
    void setStatus(cellStatus status);
};


#endif //CS205_FINALPROJECT_CELL_H
