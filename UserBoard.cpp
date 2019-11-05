//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include "UserBoard.h"
#include <iostream>

using namespace std;
UserBoard::UserBoard() : Board() {
    possiblePositions;
    position temp;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            temp.row=i;
            temp.col=j;
            possiblePositions.push_back(temp);
        }
    }
}

bool UserBoard::compMove() {
    srand(time(nullptr));
    int randRow,randCol;
    int randDirection;
    bool used=false;

    // Check to see if that square has already been clicked
    // if it has, then the move is invalid; return false
    position pos;
    int index= rand()% possiblePositions.size();
    pos= possiblePositions[index];
    possiblePositions.erase(possiblePositions.begin()+index);

    randRow=pos.row;
    randCol=pos.col;

    if(board[randRow][randCol]!=Nothing){
        updateBoard(randRow,randCol);
        cout<<"COMPUTER HIT"<<endl;
        attempts.push_back(pos);
    }else{
        updateBoard(randRow,randCol);
        cout<<"COMPUTER MISSED"<<endl;
        attempts.push_back(pos);
        return true;
    }


//---------------------------------------------------------------------------
//    if (alreadyHit(randRow, randCol)) {
//        return false;
//    }else if(hits.size()==1){
//        randDirection= rand() %4;
//        if(directionTries.empty()){
//            directionTries.push_back(randDirection);
//        }else if(directionTries.size() > 1 && directionTries.size() < 4){
//            bool inVec;
//            do{
//                randDirection= rand() %4;
//                inVec=false;
//                for(int i : directionTries){
//                    if (randDirection==i){
//                        inVec=true;
//                    }
//                }
//
//            }while(inVec);
//            directionTries.push_back(randDirection);
//        }
//
//        switch(randDirection){
//            //North
//            case 0:
//
//                break;
//            //South
//            case 1:
//                break;
//
//            //East
//            case 2:
//                break;
//            //West
//            case 3:
//                break;
//        }
//
//
//    }else if(board[randRow][randCol]!= Nothing && hits.empty()){
//        hits.push_back(pos);
//        updateBoard(randRow,randCol);
//        return true;
//
//
//    }else{
//
//        updateBoard(randRow,randCol);
//        return true;
//    }
//-------------------------------------------------------------------------------
//    // If the hits vector is empty, we don't have any previous moves
//    // to go off of, so we pick a random square. If the random square has
//    // not already been hit, then we "hit" it by updating the board,
//    // updating the ship hit, and adding it to the hits vector
//    if (hits.size() == 0) {
//        updateBoard(randRow, randCol);
//    }
//    else if (hits.size() == 1) {
//        randDirection = rand() % 4;
//        position miss;
//
//        switch (randDirection) {
//            case 0: // north
//
//                if(randRow!=0){
//                    randRow-=1;
//                }else{
//                    return false;
//                }
//                miss.row = randRow;
//                miss.col = randCol;
//                for(position m: attempts){
//                    if (m.row==randRow and m.col==randCol){
//                        return false;
//                    }
//                }
//                if(!alreadyHit(randRow,randCol) && board[randRow][randCol]==Nothing){
//                    attempts.push_back(miss);
//                }else if (!alreadyHit(randRow, randCol)) {
//                    updateBoard(randRow, randCol);
//                } else {
//                    return false;
//                }
//                break;
//            case 1: // east
//                if(randCol!=9){
//                    randCol += 1;
//                }else{
//                    return false;
//                }
//                miss.row = randRow;
//                miss.col = randCol;
//                for(position m: attempts){
//                    if (m.row==randRow and m.col==randCol){
//                        return false;
//                    }
//                }
//                if(!alreadyHit(randRow,randCol) && board[randRow][randCol]==Nothing){
//                    attempts.push_back(miss);
//                }else if (!alreadyHit(randRow, randCol)) {
//                    updateBoard(randRow, randCol);
//                } else {
//                    return false;
//                }
//                break;
//            case 2: // south
//                if(randRow!=9){
//                    randRow += 1;
//                }else{
//                    return false;
//                }
//
//                miss.row = randRow;
//                miss.col = randCol;
//                for(position m: attempts){
//                    if (m.row==randRow and m.col==randCol){
//                        return false;
//                    }
//                }
//                if(!alreadyHit(randRow,randCol) && board[randRow][randCol]==Nothing){
//                    attempts.push_back(miss);
//                }else if (!alreadyHit(randRow, randCol)) {
//                    updateBoard(randRow, randCol);
//                } else {
//                    return false;
//                }
//                break;
//            case 3: // west
//                if(randCol!=0){
//                    randCol -= 1;
//                }else{
//                    return false;
//                }
//
//                miss.row = randRow;
//                miss.col = randCol;
//                for(position m: attempts){
//                    if (m.row==randRow and m.col==randCol){
//                        return false;
//                    }
//                }
//                if(!alreadyHit(randRow,randCol) && board[randRow][randCol]==Nothing){
//                    attempts.push_back(miss);
//                }else if (!alreadyHit(randRow, randCol)) {
//                    updateBoard(randRow, randCol);
//                } else {
//                    return false;
//                }
//                break;
//        }
//        // pick a random direction
//        // see if its a hit
//        // if it is a hit then add to hit vector
//        // if not a hit, add to attempts vector
//    }
//    else if (hits.size() > 1) {
//        int hitsSize = hits.size();
//        position to = hits[hitsSize];
//        position from = hits[hitsSize - 1];
//        // position to check if the next logical move is in the attempts vector
//        bool inAttempts;
//        position check;
//        // NORTH
//        check.row = hits[hitsSize].row - 2;
//        check.col = hits[hitsSize].col;
//        for (position p : attempts) {
//            if (p.row == check.row && p.col == check.col) {
//                inAttempts = true;
//            }
//        }
//        if ((from.row - to.row == -1) && (from.col - to.col == 0) && !inAttempts) {
//            // north
//            updateBoard(check.row, check.col);
//
//        }
//        // EAST
//        check.row = hits[hitsSize].row;
//        check.col = hits[hitsSize].col + 2;
//        for (position p : attempts) {
//            if (p.row == check.row && p.col == check.col) {
//                inAttempts = true;
//            }
//        }
//        if ((from.row - to.row == 0) && (from.col - to.col == 1) && !inAttempts) {
//            // east
//            updateBoard(check.row, check.col);
//        }
//        // SOUTH
//        check.row = hits[hitsSize].row + 2;
//        check.col = hits[hitsSize].col;
//        for (position p : attempts) {
//            if (p.row == check.row && p.col == check.col) {
//                inAttempts = true;
//            }
//        }
//        if ((from.row - to.row == 1) && (from.col - to.col == 0) && !inAttempts) {
//            // south
//            updateBoard(check.row, check.col);
//        }
//        // WEST
//        check.row = hits[hitsSize].row;
//        check.col = hits[hitsSize].col - 2;
//        for (position p : attempts) {
//            if (p.row == check.row && p.col == check.col) {
//                inAttempts = true;
//            }
//        }
//        if ((from.row - to.row == 0) && (from.col - to.col == -1) && !inAttempts) {
//            // west
//            updateBoard(check.row, check.col);
//        }
//        // find the direction of the hits
//        // keep going in that direction, unless the position next in line is in the attempts vector
//        // if next in line in attempts vector, go the opposite direction
//    }
//

    return true;
}

bool UserBoard::alreadyHit(int row, int col) {
    cellStatus temp = board[row][col];
    switch(temp) {
        case DestroyerHit:
            return true;
        case SubHit:
            return true;
        case CarrierHit:
            return true;
        case CruiserHit:
            return true;
        case BattleshipHit:
            return true;
        case NothingHit:
            return true;
        default:
            return false;
    }
}

void UserBoard::updateBoard(int row, int col) {
    // update board
    cellStatus tempStat = board[row][col];
    cellStatus updated = cellStatusUpdater(tempStat);
    board[row][col] = updated;
    // update ship hit
    updateShip(tempStat);
    position tempPos;
    tempPos.row = row;
    tempPos.col = col;
    // add to hits vector
    if(tempStat!=Nothing){
        hits.push_back(tempPos);
    }
}

void UserBoard::placePieces() {

    int randomRow, randomCol;
    position randomPos;
    int currSize;
    cellStatus currShip;

    // Initialize random object
    srand(time(nullptr));
    int placed = 0;

    while (placed < 5) {
        int direction= -1;
        string junk="";
        switch(placed){
            case 0:
                currSize=5;
                currShip=Carrier;
                cout<<"Carrier\n--------"<<endl;
                randomPos= newPosition();
                cout<<"What Direction (0=North, 1=South, 2=East, 3= West)"<<endl;
                direction=getIntInput(junk);
                while(direction<0 or direction >3){
                    cout<<"Invalid Number"<<endl;
                    direction=getIntInput(junk);
                }
                break;
            case 1:
                currSize=4;
                currShip=Battleship;
                cout<<"BattleShip\n--------"<<endl;
                randomPos= newPosition();
                cout<<"What Direction (0=North, 1=South, 2=East, 3= West)"<<endl;
                direction=getIntInput(junk);
                while(direction<0 or direction >3){
                    cout<<"Invalid Number"<<endl;
                    direction=getIntInput(junk);
                }
                break;
            case 2:
                currSize=3;
                currShip=Destroyer;
                cout<<"Destroyer\n--------"<<endl;
                randomPos= newPosition();
                cout<<"What Direction (0=North, 1=South, 2=East, 3= West)"<<endl;
                direction=getIntInput(junk);
                while(direction<0 or direction >3){
                    cout<<"Invalid Number"<<endl;
                    direction=getIntInput(junk);
                }
                break;
            case 3:
                currSize=3;
                currShip=Sub;
                cout<<"Sub\n--------"<<endl;
                randomPos= newPosition();
                cout<<"What Direction (0=North, 1=South, 2=East, 3= West)"<<endl;
                direction=getIntInput(junk);
                while(direction<0 or direction >3){
                    cout<<"Invalid Number"<<endl;
                    direction=getIntInput(junk);
                }
                break;
            case 4:
                currSize=2;
                currShip=Cruiser;
                cout<<"Cruiser\n--------"<<endl;
                randomPos= newPosition();
                cout<<"What Direction (0=North, 1=South, 2=East, 3= West)"<<endl;
                direction=getIntInput(junk);
                while(direction<0 or direction >3){
                    cout<<"Invalid Number"<<endl;
                    direction=getIntInput(junk);
                }
                break;
        }
        randomRow=randomPos.row;
        randomCol=randomPos.col;

        while(!checkClear(randomRow,randomCol,currSize,direction)){
            cout<<"Invalid Placement"<<endl;
            randomPos= newPosition();
            cout<<"What Direction (0=North, 1=South, 2=East, 3= West)"<<endl;

            direction=getIntInput(junk);
            while(direction<0 or direction >3){
                cout<<"Invalid Number"<<endl;
                direction=getIntInput(junk);
            }
            randomRow=randomPos.row;
            randomCol=randomPos.col;
        }

        setBoardValues(currShip,randomPos,currSize,direction);

        placed++;
    }
}

void UserBoard::setBoardValues(cellStatus shipType,position pos, int size, int direction){
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

bool UserBoard::checkClear(int row, int col, int size, int direction){
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

position UserBoard::newPosition(){
    position pos;
    int randomRow = rand() % 10;
    // generate random number between 0 and 9 for col
    int randomCol = rand() % 10;
    string junk="";

    cout<<"What Row?"<<endl;
    randomRow=getIntInput(junk);
    while(randomRow<0 or randomRow> 9){
        cout<<"Invalid Number"<<endl;
        randomRow=getIntInput(junk);
    }
    cout<<"What Col?"<<endl;
    randomCol=getIntInput(junk);
    while(randomCol<0 or randomCol> 9){
        cout<<"Invalid Number"<<endl;
        randomCol=getIntInput(junk);
    }

    while (board[randomRow][randomCol] != Nothing) {
        cout<<"Invalid"<<endl;
        cout<<"What Row?"<<endl;
        randomRow=getIntInput(junk);
        while(randomRow<0 or randomRow> 9){
            cout<<"Invalid Number"<<endl;
            randomRow=getIntInput(junk);
        }
        cout<<"What Col?"<<endl;
        randomCol=getIntInput(junk);
        while(randomCol<0 or randomCol> 9){
            cout<<"Invalid Number"<<endl;
            randomCol=getIntInput(junk);
        }
    }

    pos.row=randomRow;
    pos.col=randomCol;

    return pos;
}

int UserBoard::getDirection(int row, int col, int size){
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

