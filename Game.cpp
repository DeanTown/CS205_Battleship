//
// Created by Harry Makovsky on 10/22/19.


#include "Game.h"
#include "stdio.h"
#include "iostream"

using namespace std;

Game::Game(){
    compBoard= ComputerBoard();
    userBoard= UserBoard();
}

//To Begin and end games
void Game::startGame(){

    string enter;
    cout<<"Hello Welcome to BattleShip"<<endl;
    cout<<"Press enter to start loading pieces";
    cin>> enter;
    userBoard.placePieces();
    compBoard.placePieces();
}

void Game::resetGame(){

}
void Game::endGame(){

}

void Game::playGame(){
    int row;
    int col;
    cout<<"OK now that the pieces are placed, lets begin the game\n";

    while(!compBoard.getFleet().sunk() and !userBoard.getFleet().sunk()){
        compBoard.printBoard();

        cout<<"What row?"<<endl;
        cin>> row;
        cout<<"What col?"<<endl;
        cin>> col;

        compBoard.userMove(row,col);

        wait(new int(3));


    }



}
