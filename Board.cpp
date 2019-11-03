//
// Created by Oliver Reckord Groten on 10/21/19.
//

#include "Board.h"
using namespace std;

/* Constructor */
Board::Board() {
    fleet= Fleet();
    cols = 10;
    rows = 10;
    board.resize(rows);
    for (vector<cellStatus> row : board) {
        row.resize(cols);
    }
}

Fleet Board::getFleet() {
    return fleet;
}

string Board::cellStatusToString(cellStatus c) {
    switch(c) {
        case Destroyer: return "Destroyer";
        case Sub: return "Sub";
        case Carrier: return "Carrier";
        case Cruiser: return "Cruiser";
        case Battleship: return "Battleship";
        case Nothing: return "Nothing";
    }
    return "";
}

cellStatus Board::cellStatusUpdater(cellStatus c) {
    switch(c) {
        case Destroyer: return DestroyerHit;
        case Sub: return SubHit;
        case Carrier: return CarrierHit;
        case Cruiser: return CruiserHit;
        case Battleship: return BattleshipHit;
        case Nothing: return NothingHit;
    }
    return Nothing;
}

void Board::updateShip(cellStatus c) {
    switch(c) {
        case Destroyer:
            fleet.updateShip(1);
        case Sub:
            fleet.updateShip(2);
        case Carrier:
            fleet.updateShip(3);
        case Cruiser:
            fleet.updateShip(4);
        case Battleship:
            fleet.updateShip(5);
    }
}

void printBoard(){

}
