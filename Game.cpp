//
// Created by Harry Makovsky on 10/22/19.


#include "Game.h"
#include "stdio.h"
#include "iostream"
#include <sstream>
#include "graphics.h"

using namespace std;



int getIntInput(string input){
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

Game::Game(){
    compBoard= ComputerBoard();
    userBoard= UserBoard();
}

Game::Game(int i) {
    userBoard = UserBoard();
    user2Board = UserBoard();

}



ComputerBoard Game::getComputerBoard() {
    return compBoard;
}

UserBoard Game::getUserBoard() {
    return userBoard;
}

UserBoard Game::getUser2Board() {
    return user2Board;
}

void Game::setUser2Board(UserBoard temp) {
    user2Board=temp;
}
// Helper functions that call the real userMove method from within the compBoard object
bool Game::userMove(int row, int col){
    return compBoard.userMove(row,col);
}

bool Game::user1Move(int row, int col){
    return user2Board.humanMove(row,col);
}

bool Game::user2Move(int row, int col){
    return userBoard.humanMove(row,col);
}
// Helper function that calls the real compMove method from within the userBoard object
void Game::compMove(){
    userBoard.compMove();
}
// Helper function that calls the method to place pieces on the computer board
void Game::placePiecesDebug(){
    compBoard.placePieces();
}


// Method to for user to place ship on their board.
// Checks the direction and makes sure those spaces are clear before placing
void Game::placeShip(cellStatus ship, int x, int y, int direction) {
    switch(ship) {
        case Destroyer:
            if(userBoard.checkClear(x,y,3,direction)) {
                userBoard.setBoardValues(Destroyer,{x,y},3,direction);
            }
            break;
        case Sub:
            if(userBoard.checkClear(x,y,3,direction)) {
                userBoard.setBoardValues(Sub,{x,y},3,direction);
            }
            break;
        case Carrier:

            if(userBoard.checkClear(x,y,5,direction)) {
                userBoard.setBoardValues(Carrier,{x,y},5,direction);
            }
            break;
        case Cruiser:
            if(userBoard.checkClear(x,y,2,direction)) {
                userBoard.setBoardValues(Cruiser,{x,y},2,direction);
            }
            break;
        case Battleship:
            if(userBoard.checkClear(x,y,4,direction)) {
                userBoard.setBoardValues(Battleship,{x,y},4,direction);
            }
            break;
    }
}

void Game::placePlayer2(cellStatus ship, int x, int y, int direction) {
    switch (ship) {
        case Destroyer:
            if(user2Board.checkClear(x,y,3,direction)) {
                user2Board.setBoardValues(Destroyer,{x,y},3,direction);
            }
            break;
        case Sub:
            if(user2Board.checkClear(x,y,3,direction)) {
                user2Board.setBoardValues(Sub,{x,y},3,direction);
            }
            break;
        case Carrier:

            if(user2Board.checkClear(x,y,5,direction)) {
                user2Board.setBoardValues(Carrier,{x,y},5,direction);
            }
            break;
        case Cruiser:
            if(user2Board.checkClear(x,y,2,direction)) {
                user2Board.setBoardValues(Cruiser,{x,y},2,direction);
            }
            break;
        case Battleship:
            if(user2Board.checkClear(x,y,4,direction)) {
                user2Board.setBoardValues(Battleship,{x,y},4,direction);
            }
            break;
    }
}