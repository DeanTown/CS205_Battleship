//
// Created by Oliver Reckord Groten on 10/22/19.
//

#ifndef CS205_FINALPROJECT_SHIP_H
#define CS205_FINALPROJECT_SHIP_H

#include <vector>

class Ship {
private:
    int size;
    bool destroyed;
    std::vector<std::vector<int>> coords;
public:
    /* Constructor */
    Ship();
    /* Getters */
    int getSize();
    bool getDestroyed();
    std::vector<std::vector<int>> getCoords();
    /* Setters */
    void setSize(int s);
    void setDestroyed(bool d);
    void setCoords(std::vector<std::vector<int>> c);
};


#endif //CS205_FINALPROJECT_SHIP_H
