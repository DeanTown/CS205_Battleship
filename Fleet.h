#ifndef CS205_FINALPROJECT_FLEET_H
#define CS205_FINALPROJECT_FLEET_H

#include <string>

enum fleetStat{
    moveable, // after click, start drag the object
    selected, // after click, place the object
    placed, // object on board, can be click to move
    placedHo, // object is placed horizontally
    placedVe, // object is placed vertically
    ready, //\\\|--> finish dragging object, object stay at the position and can't be dragged again
    addNull, ///|
    No, // while working on place a ship, other types of ship can't be selected
    out, // message for ship being placed out of board
    working, // message for which ship is being working on
    overlapping, // message for ship get overlapping
    noWord // erase message
};

class Fleet {
private:
    fleetStat fs = moveable, fsTwo, fsThree, fsFour, fsFive = noWord;
public:
    fleetStat getFleetStat() const;
    fleetStat getAdditionStat() const;
    fleetStat getThirdStat() const;
    fleetStat getForthStat() const;
    fleetStat getFifthStat() const;
    void setFleetStat(fleetStat fs);
    void setAdditionStat(fleetStat fs);
    void setThirdStat(fleetStat fs);
    void setForthStat(fleetStat fs);
    void setFifthStat(fleetStat fs);

    void outBoard(std::string label);
    void focus(std::string label);
    void overlap(std::string label);
    void drawSunk(std::string label);
};


#endif //CS205_FINALPROJECT_FLEET_H
