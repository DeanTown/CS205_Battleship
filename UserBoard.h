//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_USERBOARD_H
#define CS205_FINAL_PROJECT_USERBOARD_H

#include "Board.h"
#include <regex>
#include "Shapes.h"

class UserBoard : public Board{
private:
    int x = 50, y = 50;
    bool isBlack = true;
    vector<position> hits;
    vector<position> attempts;
    cellStatus lastHit;
    vector<position> possiblePositions;
    vector<position> possibleHits;
//    vector<vector<Tangle>> cells;
public:
    vector<vector<Tangle>> cells;
    UserBoard();
    bool humanMove(int row, int col);
    void square(int x, int y);
    void draw(int width, int height);
    void move(int displace);

    void drawP2game();
    void drawHidden();

    bool compMove();
    bool alreadyHit(int row, int col);
    void updateBoard(int row, int col);
    void placePieces();
    int getDirection(int row, int col, int size);
    bool checkClear(int row, int col, int size, int direction);
    position newPosition();
    void setBoardValues(cellStatus shipType,position pos, int size, int direction);
};


#endif //CS205_FINAL_PROJECT_USERBOARD_H
