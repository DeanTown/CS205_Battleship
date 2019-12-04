//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "ComputerBoard.h"
#include <iostream>

/*
 * This method handles the user move on the computers board.
 * The basic logic which is repeated is to check if the cell clicked contains something.
 * If it does, then it marks it as hit. If it has already been hit, it rejects the move
 * and returns false.
 *
 */
ComputerBoard::ComputerBoard(): Board(){
    Tangle cell;
    vector<Tangle> temp;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            point p = {i,j};
            cell = Tangle(30, 30, {i*30+515,j*30+115},p);
            cell.setBorderColor(0,100,0);
            temp.push_back(cell);
        }
        cells.push_back(temp);
        temp.clear();
    }

}
void ComputerBoard::draw() {
    int i = 0;
    for (vector<Tangle> row : cells) {
        int j = 0;
        for (Tangle cell : row) {
            if(board[i][j] == CarrierHit) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == CruiserHit) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == BattleshipHit) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == SubHit) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == DestroyerHit) {
                cell.setFillColor({1,0,0});
            }
            cell.draw();
            j++;
        }
        i++;
    }
}
bool ComputerBoard::userMove(int row, int col) {
    // get cell status
    cellStatus c = board[row][col];
    // cell contains destroyer
    if (c == Destroyer) {
        board[row][col] = DestroyerHit;
        updateShip(Destroyer);
        // go into ship class and increment hit
    } else if (c == DestroyerHit) {
        return false;
    }
    // cell contains sub
    if (c == Sub) {
        board[row][col] = SubHit;
        updateShip(Sub);
    } else if (c == SubHit) {
        return false;
    }
    // cell contains carrier
    if (c == Carrier) {
        board[row][col] = CarrierHit;
        updateShip(Carrier);
    } else if (c == CarrierHit) {
        return false;
    }
    // cell contains cruiser
    if (c == Cruiser) {
        board[row][col] = CruiserHit;
        updateShip(Cruiser);
    } else if (c == CruiserHit) {
        return false;
    }
    // cell contains battleship
    if (c == Battleship) {
        board[row][col] = BattleshipHit;
        updateShip(Battleship);
    } else if (c == BattleshipHit) {
        return false;
    }
    // cell contains nothing
    if (c == Nothing) {
        board[row][col] = NothingHit;
    } else if (c == NothingHit) {
        return false;
    }
    return true;
}

/*
 * generate some random integers for the row and column
 * if the cell at that integer is Nothing AND all the cells surrounding it within
 * the length of the ship placed is Nothing, then change all the cells to be that
 * specific ship.
 * Another random int to determine direction that the ship is generated in. if the random
 * position of the ship is too close to one side for it to face that way, then narrow the
 * choices for facing direction.
 */
void ComputerBoard::placePieces() {

    int randomRow, randomCol;
    position randomPos;
    int currSize;
    cellStatus currShip;

    // Initialize random object
    srand(time(nullptr));
    int placed = 0;

    while (placed < 5) {
        int direction= -1;

        randomPos= newPosition();
        randomRow=randomPos.row;
        randomCol=randomPos.col;

        int cap=0;
        switch(placed){
            case 0:
                currSize=5;
                currShip=Carrier;
                break;
            case 1:
                currSize=4;
                currShip=Battleship;
                break;
            case 2:
                currSize=3;
                currShip=Destroyer;
                break;
            case 3:
                currSize=3;
                currShip=Sub;
                break;
            case 4:
                currSize=2;
                currShip=Cruiser;
                break;
        }
        cap=0;
        direction=getDirection(randomRow,randomCol,currSize);

        while(!checkClear(randomRow,randomCol,currSize,direction)){
            if(cap==4){
                randomPos= newPosition();
                randomRow=randomPos.row;
                randomCol=randomPos.col;
                cap=0;
            }
            direction=getDirection(randomRow,randomCol,currSize);
            cap++;
        }
        setBoardValues(currShip,randomPos,currSize,direction);

        placed++;
    }
}

void ComputerBoard::setBoardValues(cellStatus shipType,position pos, int size, int direction){
    int row=pos.row;
    int col=pos.col;

    switch(direction){
        case 0:
            for(int i=row;i>=row-size+1;i--){
                board[i][col]=shipType;
            }
            break;
        case 1:
            for(int i=row;i<=row+size-1;i++){
                board[i][col]=shipType;
            }
            break;
        case 2:
            for(int i=col;i<=col+size-1;i++){
                board[row][i]=shipType;
            }
            break;
        case 3:
            for(int i=col;i>=col-size+1;i--){
                board[row][i]=shipType;
            }
            break;
    }
}

bool ComputerBoard::checkClear(int row, int col, int size, int direction){
    bool valid=true;
    switch(direction){
        case 0:
            for(int i=row;i>=row-size+1;i--){
                if(board[i][col]!= Nothing){
                    valid=false;
                }
            }
            break;
        case 1:
            for(int i=row;i<=row+size-1;i++){
                if(board[i][col]!= Nothing){
                    valid=false;
                }
            }
            break;
        case 2:
            for(int i=col;i<=col+size-1;i++){
                if(board[row][i]!= Nothing){
                    valid=false;
                }
            }
            break;
        case 3:
            for(int i=col;i>=col-size+1;i--){
                if(board[row][i]!= Nothing){
                    valid=false;
                }
            }
            break;
    }
    return valid;
}

position ComputerBoard::newPosition(){
    position pos;
    int randomRow = rand() % 10;
    // generate random number between 0 and 9 for col
    int randomCol = rand() % 10;

    while (board[randomRow][randomCol] != Nothing) {
        randomRow = rand() % 10;
        randomCol = rand() % 10;
    }

    pos.row=randomRow;
    pos.col=randomCol;

    return pos;
}

int ComputerBoard::getDirection(int row, int col, int size){
    int northDist=0;
    int southDist=0;
    int eastDist=0;
    int westDist=0;
    bool northValid=false;
    bool southValid=false;
    bool eastValid=false;
    bool westValid=false;

    northDist= row;
    southDist= 9 - row;
    eastDist= 9 - col;
    westDist= col;

    if(northDist>=size-1){
        northValid=true;
    }if(southDist>=size-1){
        southValid=true;
    }if(eastDist>=size-1){
        eastValid= true;
    }if(westDist>=size-1){
        westValid=true;
    }
    bool found=false;
    int direction=-1;

    while(!found){
        direction = rand() % 4;
        switch(direction){
            case 0:
                if(northValid){
                    found=true;
                }
                break;
            case 1:
                if(southValid){
                    found=true;
                }
                break;
            case 2:
                if(eastValid){
                    found=true;
                }
                break;
            case 3:
                if(westValid){
                    found=true;
                }
                break;
        }
    }

    return direction;
}

