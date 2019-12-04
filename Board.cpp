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

//void Board::printBoard() {
//    for(int i=0; i< rows ; i++){
//        for(int j=0; j<cols; j++){
//
//            //cout<<cellStatusToString(board[i][j]).substr(0,2)<<cellStatusToString(board[i][j]).substr(cellStatusToString(board[i][j]).length()-3,3)+" ";
//
//            switch(board[i][j]){
//                case Nothing:
//                    cout<<"o   ";
//                    break;
//                case NothingHit:
//                    cout<<"x   ";
//                    break;
//                case Battleship:
//                    cout<<"b   ";
//                    break;
//                case BattleshipHit:
//                    cout<<"B   ";
//                    break;
//                case Cruiser:
//                    cout<<"cr  ";
//                    break;
//                case CruiserHit:
//                    cout<<"CR  ";
//                    break;
//                case Sub:
//                    cout<<"s   ";
//                    break;
//                case SubHit:
//                    cout<<"S   ";
//                    break;
//                case Destroyer:
//                    cout<<"d   ";
//                    break;
//                case DestroyerHit:
//                    cout<<"D   ";
//                    break;
//                case Carrier:
//                    cout<<"c   ";
//                    break;
//                case CarrierHit:
//                    cout<<"C   ";
//                    break;
//                default:
//                    cout<<"0   ";
//                    break;
//
//            }
//
//
//        }
//        cout<<"\n";
//    }
//}
//void Board::printHiddenBoard() {
//    for(int i=0; i< rows ; i++){
//        for(int j=0; j<cols; j++){
//
//
//            switch(board[i][j]){
//                case Nothing:
//                    cout<<"o   ";
//                    break;
//                case NothingHit:
//                    cout<<"+   ";
//                    break;
//                case Battleship:
//                    cout<<"o   ";
//                    break;
//                case BattleshipHit:
//                    cout<<"X   ";
//                    break;
//                case Cruiser:
//                    cout<<"o   ";
//                    break;
//                case CruiserHit:
//                    cout<<"X   ";
//                    break;
//                case Sub:
//                    cout<<"o   ";
//                    break;
//                case SubHit:
//                    cout<<"X   ";
//                    break;
//                case Destroyer:
//                    cout<<"o   ";
//                    break;
//                case DestroyerHit:
//                    cout<<"X   ";
//                    break;
//                case Carrier:
//                    cout<<"o   ";
//                    break;
//                case CarrierHit:
//                    cout<<"X   ";
//                    break;
//                default:
//                    cout<<"0   ";
//                    break;
//
//            }
//
//
//        }
//        cout<<"\n";
//    }
//}

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
