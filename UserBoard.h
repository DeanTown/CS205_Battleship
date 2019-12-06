//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_USERBOARD_H
#define CS205_FINAL_PROJECT_USERBOARD_H

#include "Board.h"
#include <regex>
#include "Shapes.h"

/*
 * This class holds a userBoard which keeps track of the state of the players board as well
 * as having methods for the computer to make a move on it.
 */

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
    // helper function for the players move
    bool humanMove(int row, int col);
    // helper function for drawing the board
    void square(int x, int y);
    void draw(int width, int height);
    // method to move the board
    void move(int displace);
    // helper methods for PVP mode so the players don't see each others boards
    void drawP2game();
    void drawHidden();
    // method to handle the computer move
    bool compMove();
    // helper method for compMove to determine if the attempted hit cell has already been hit.
    bool alreadyHit(int row, int col);
    // updates userBoard with according hit based on the computer move
    void updateBoard(int row, int col);
    // method for user to place pieces
    void placePieces();
    // helper methods for the placePieces method
    int getDirection(int row, int col, int size);
    bool checkClear(int row, int col, int size, int direction);
    position newPosition();
    void setBoardValues(cellStatus shipType,position pos, int size, int direction);
};


#endif //CS205_FINAL_PROJECT_USERBOARD_H
