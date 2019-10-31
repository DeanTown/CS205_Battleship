//
// Created by Oliver Reckord Groten on 10/21/19.
//

#include "Board.h"
using namespace std;

/* Constructor */
Board::Board() {
    cols = 10;
    rows = 10;
    board.resize(rows);
}

//void Board::draw_board() {
//    Cell cell;
////    for (int i = 5; i < 50; i += 5) {
////        for (int j = 5; j < 50; j += 5) {
////            cell.setPosition(i,j);
////            cell.draw_shape();
////        }
////    }
//
//    for (int i = 100; i < 390; i += 30) {
//        for (int j = 100; j < 390; j += 30) {
//            cell.setPosition(i,j);
//            cell.setWidth(30);
//            cell.setLength(30);
//            cell.draw_shape();
//        }
//    }
////    cell.setPosition(100,100);
////    cell.setLength(50);
////    cell.setWidth(50);
////    cell.draw_shape();
//}