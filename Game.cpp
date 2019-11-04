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

//To Begin and end games
bool Game::startGame(){
    int choice;
    string junk="";
    cout<<"Hello Welcome to BattleShip"<<endl;
    cout<<"Do you want to play a game 0=NO 1=YES: ";
    choice=getIntInput(junk);
    if(choice==1){
        cout<<"Enter starting position in row, col then the direction the ship will be placed from that point"<<endl;
        userBoard.printBoard();
        userBoard.placePieces();
        compBoard.placePieces();
        return true;
    }else{
        return false;
    }
}

void Game::resetGame(){
    userBoard= UserBoard();
    compBoard= ComputerBoard();
}
void Game::endGame(){
    if(compBoard.getFleet().sunk()){
        cout<<"Congrats you beat the computer!"<<endl;
    }else{
        cout<<"You lost to the computer..."<<endl;
    }

}



void Game::playGame(){
    int row;
    int col;
    string s="";

    cout<<"OK now that the pieces are placed, lets begin the game\n";

    while(!compBoard.getFleet().sunk() and !userBoard.getFleet().sunk()){

        cout<<"OPPONENT BOARD\n-----------------------------------"<<endl;
        compBoard.printHiddenBoard();

        cout<<"USER BOARD\n-----------------------------------"<<endl;
        userBoard.printBoard();

        cout<<"Time to FIRE!"<<endl;
        cout<<"What row?"<<endl;
        row = getIntInput(s);
        while (row < 0 or row > 9) {
            cout << "Invalid Row #" << endl;
            row = getIntInput(s);
        }
        cout<<"What col?"<<endl;
        col = getIntInput(s);
        while (row < 0 or row > 9) {
            cout << "Invalid Col #" << endl;
            col = getIntInput(s);
        }


        while(!compBoard.userMove(row,col)){
            cout<<"Invalid Move"<<endl;
            cout<<"What row?"<<endl;
            row = getIntInput(s);
            while (row < 0 or row > 9) {
                cout << "Invalid Row #" << endl;
                row = getIntInput(s);
            }
            cout<<"What col?"<<endl;
            col = getIntInput(s);
            while (row < 0 or row > 9) {
                cout << "Invalid Col #" << endl;
                col = getIntInput(s);
            }
        }

        wait(new int(1));

        while(!userBoard.compMove());

        cout<<"Computer has made a move! \n"<<endl;

    }



}
