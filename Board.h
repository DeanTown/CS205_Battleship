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

/*
 * Carrier size: 5
 * Battleship size: 4
 * Destroyer size: 3
 * Sub size: 3
 * Cruiser size: 2
 */
enum cellStatus {Destroyer, DestroyerHit, DestroyerSunk,
                Sub, SubHit, SubSunk,
                Carrier, CarrierHit, CarrierSunk,
                Cruiser, CruiserHit, CruiserSunk,
                Battleship, BattleshipHit, BattleshipSunk,
                Nothing, NothingHit};

class Board {
protected:
    vector<vector<cellStatus>> board;
    int cols;
    int rows;
    Fleet fleet;
public:
    /* Constructor */
    Board();

    void printBoard();
};


#endif //CS205_FINALPROJECT_BOARD_H
