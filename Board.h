//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Ship.h"
#include "graphics.h"
#include "Fleet.h"
#include <vector>
using namespace std;

enum cellStatus {Destroyer, DestroyerHit, DestroyerSunk,
                Sub, SubHit, SubSunk,
                Carrier, CarrierHit, CarrierSunk,
                Cruiser, CruiserHit, CruiserSunk,
                Battleship, BattleshipHit, BattleshipSunk,
                Nothing, NothingHit};

class Board {
private:
    vector<vector<cellStatus>> board;
    int cols;
    int rows;
    Fleet fleet;
public:
    /* Constructor */
    Board();
};


#endif //CS205_FINALPROJECT_BOARD_H
