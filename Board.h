//
// Created by Oliver Reckord Groten on 10/21/19.
//

#ifndef CS205_FINALPROJECT_BOARD_H
#define CS205_FINALPROJECT_BOARD_H

#include "Ship.h"
#include "graphics.h"
#include "Fleet.h"
#include <vector>
#include "string"
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

struct position {
    int row;
    int col;
};

class Board {
protected:
    vector<vector<cellStatus>> board;
    int cols;
    int rows;
    Fleet fleet;
public:
    /* Constructor */
    Board();
    Fleet getFleet();
    string cellStatusToString(cellStatus c);
    cellStatus cellStatusUpdater(cellStatus c);
    void updateShip(cellStatus c);
    void printBoard();
    int getIntInput(string input);

};


#endif //CS205_FINALPROJECT_BOARD_H
