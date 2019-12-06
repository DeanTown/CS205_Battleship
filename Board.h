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
 * Main Board class which is inherited by UserBoard and ComputerBoard. This class provides the base for
 * functionality on the whole game.
 */

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
    // enum helper method
    string cellStatusToString(cellStatus c);
    // method to update the cellStatus for a particular board cell
    cellStatus cellStatusUpdater(cellStatus c);
    // method to update ship to contain correct number of hits
    void updateShip(cellStatus c);
//    void printBoard();
//    void printHiddenBoard();
    // method to get a specific board cell
    cellStatus getCell(int row, int col);
    // method for getting input (deprecated now that we have a GUI)
    int getIntInput(string input);

};


#endif //CS205_FINALPROJECT_BOARD_H
