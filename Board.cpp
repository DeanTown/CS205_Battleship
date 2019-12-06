//
// Created by Oliver Reckord Groten on 10/21/19.
//

#include "Board.h"
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

/* Constructor */
Board::Board() {
    fleet= Fleet();
    cols = 10;
    rows = 10;
    board.resize(rows);
    for(int i=0; i< rows ; i++){
        for(int j=0; j<cols; j++){
            board[i].push_back(Nothing);
        }
    }

}

Fleet Board::getFleet() {
    return fleet;
}
// enum toString helper method
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
// updates cell statuses of the board to reflect hits
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
// updates ship so it knows how many times it's been hit
void Board::updateShip(cellStatus c) {
    switch(c) {
        case Destroyer:
            fleet.updateShip(1);
            break;
        case Sub:
            fleet.updateShip(2);
            break;
        case Carrier:
            fleet.updateShip(3);
            break;
        case Cruiser:
            fleet.updateShip(4);
            break;
        case Battleship:
            fleet.updateShip(5);
            break;
    }
}


int Board::getIntInput(string input){
    input = "";
    int returnVal = 0;
    while(true) {
        getline(cin, input);
        stringstream strToInt(input);
        if (strToInt >> returnVal) {
            return returnVal;
        }
        cout << "Please enter a valid input" << endl;
    }
}

cellStatus Board::getCell(int row, int col) {
    return board[row][col];
}
