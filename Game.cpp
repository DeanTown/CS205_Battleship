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

bool Game::userMove(int row, int col){
    return compBoard.userMove(row,col);
}

bool Game::user1Move(int row, int col){
    return user2Board.humanMove(row,col);
}

bool Game::user2Move(int row, int col){
    return userBoard.humanMove(row,col);
}

void Game::compMove(){
    userBoard.compMove();
}
void Game::placePiecesDebug(){
    compBoard.placePieces();
}


//To Begin and end games
//bool Game::startGame(){
//    int choice;
//    string junk="";
//    cout<<"Hello Welcome to BattleShip"<<endl;
//    cout<<"Do you want to play a game 0=NO 1=YES: ";
//    choice=getIntInput(junk);
//    if(choice==1){
//        cout<<"Enter starting position in row, col then the direction the ship will be placed from that point"<<endl;
//        userBoard.printBoard();
//        userBoard.placePieces();
//        compBoard.placePieces();
//        return true;
//    }else{
//        return false;
//    }
//}

//void Game::resetGame(){
//    userBoard= UserBoard();
//    compBoard= ComputerBoard();
//}
//void Game::endGame(){
//    if(compBoard.getFleet().sunk()){
//        cout<<"Congrats you beat the computer!"<<endl;
//    }else{
//        cout<<"You lost to the computer..."<<endl;
//    }
//
//}



//void Game::playGame(){
//    int row;
//    int col;
//    string s="";
//
//    cout<<"OK now that the pieces are placed, lets begin the game\n";
//
//    while(!compBoard.getFleet().sunk() and !userBoard.getFleet().sunk()){
//
//        cout<<"OPPONENT BOARD\n-----------------------------------"<<endl;
//        compBoard.printHiddenBoard();
//
//
//        cout<<"USER BOARD\n-----------------------------------"<<endl;
//        userBoard.printBoard();
//
//        cout<<"Time to FIRE!"<<endl;
//        cout<<"What row?"<<endl;
//        row = getIntInput(s);
//        while (row < 0 or row > 9) {
//            cout << "Invalid Row #" << endl;
//            row = getIntInput(s);
//        }
//        cout<<"What col?"<<endl;
//        col = getIntInput(s);
//        while (row < 0 or row > 9) {
//            cout << "Invalid Col #" << endl;
//            col = getIntInput(s);
//        }
//
//
//        while(!compBoard.userMove(row,col)){
//            cout<<"Invalid Move"<<endl;
//            cout<<"What row?"<<endl;
//            row = getIntInput(s);
//            while (row < 0 or row > 9) {
//                cout << "Invalid Row #" << endl;
//                row = getIntInput(s);
//            }
//            cout<<"What col?"<<endl;
//            col = getIntInput(s);
//            while (row < 0 or row > 9) {
//                cout << "Invalid Col #" << endl;
//                col = getIntInput(s);
//            }
//        }
//
//        wait(new int(1));
//
//        while(!userBoard.compMove());
//    }
//}

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