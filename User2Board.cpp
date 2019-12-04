#include "User2Board.h"
#include "Shapes.h"
#include <iostream>

using namespace std;
User2Board::User2Board() : Board() {
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
void User2Board::draw(int width, int height) {
    int i = 0;
    for (vector<Tangle> row : cells) {
        int j = 0;
        for (Tangle cell : row) {
            if(board[i][j] == Carrier) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == Cruiser) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == Battleship) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == Sub) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == Destroyer) {
                cell.setFillColor({1,0,0});
            }
            if(board[i][j] == CarrierHit) {
                cell.setFillColor({1,0,1});
            }
            if(board[i][j] == CruiserHit) {
                cell.setFillColor({1,0,1});
            }
            if(board[i][j] == BattleshipHit) {
                cell.setFillColor({1,0,1});
            }
            if(board[i][j] == SubHit) {
                cell.setFillColor({1,0,1});
            }
            if(board[i][j] == DestroyerHit) {
                cell.setFillColor({1,0,1});
            }
            if(board[i][j] == NothingHit) {
                cell.setFillColor({1,1,1});
            }



            cell.draw();
            j++;
        }
        i++;
    }
}


bool User2Board::compMove() {
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

    bool sunk=false;

    switch(lastHit){
        case Carrier:
            sunk= fleet.getCarrier().getDestroyed();
            break;
        case Battleship:
            sunk= fleet.getBattle().getDestroyed();
            break;
        case Destroyer:
            sunk= fleet.getDestroyer().getDestroyed();
            break;
        case Sub:
            sunk= fleet.getSub().getDestroyed();
            break;
        case Cruiser:
            sunk= fleet.getCruiser().getDestroyed();
            break;
        default:
            break;
    }
    if(sunk) {
        hits.clear();
        lastHit=Nothing;
        return false;
    }

    if(board[randRow][randCol]!=Nothing && hits.empty()){
        lastHit=board[randRow][randCol];
        updateBoard(randRow,randCol);
        cout<<"COMPUTER HIT"<<endl;
        hits.push_back(pos);
        return true;
    }else if(hits.size()==1 && lastHit !=Nothing){
        cout<<"hits has size one"<<endl;
        for(int i=0; i<10;i++){
            for(int j=0; j<10; j++){
                if(board[i][j]==lastHit){
                    position temp;
                    temp.row=i;
                    temp.col=j;
                    possibleHits.push_back(temp);
                }
            }
        }
        int index= rand()% possibleHits.size();
        position temp2= possibleHits[index];
        possibleHits.erase(possibleHits.begin()+index);
        updateBoard(temp2.row,temp2.col);
        hits.push_back(temp2);
        possiblePositions.push_back(pos);
        for(int i=0; i<possiblePositions.size();i++){
            if(possiblePositions[i].col==temp2.col && possiblePositions[i].row==temp2.row){
                possiblePositions.erase(possiblePositions.begin()+i);
            }

        }

        return true;

    }else if(hits.size()>=2 && lastHit !=Nothing) {
        int index= rand()% possibleHits.size();
        position temp2= possibleHits[index];
        possibleHits.erase(possibleHits.begin()+index);
        updateBoard(temp2.row,temp2.col);
        hits.push_back(temp2);
        possiblePositions.push_back(pos);
        for(int i=0; i<possiblePositions.size();i++){
            if(possiblePositions[i].col==temp2.col && possiblePositions[i].row==temp2.row){
                possiblePositions.erase(possiblePositions.begin()+i);
            }

        }

        return true;
    }else{
        updateBoard(randRow,randCol);
        cout<<"COMPUTER MISSED"<<endl;

        return true;
    }

}

bool User2Board::alreadyHit(int row, int col) {
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

void User2Board::updateBoard(int row, int col) {
    // update board
    cellStatus tempStat = board[row][col];
    cellStatus updated = cellStatusUpdater(tempStat);
    board[row][col] = updated;
    // update ship hit
    updateShip(tempStat);
    position tempPos;
    tempPos.row = row;
    tempPos.col = col;
}

void User2Board::placePieces() {

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

void User2Board::setBoardValues(cellStatus shipType,position pos, int size, int direction){
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

bool User2Board::checkClear(int row, int col, int size, int direction){
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

position User2Board::newPosition(){
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

int User2Board::getDirection(int row, int col, int size){
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

