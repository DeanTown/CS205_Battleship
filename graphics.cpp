#include "graphics.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include "algorithm"
#include "cstdlib"
#include "ctime"


#include "ComputerBoard.h"
#include "UserBoard.h"
#include "User2Board.h"
#include "Ship.h"
#include "Game.h"
#include "HitSelection.h"
#include <sstream>
#include "UserBoard.h"


using namespace std;
GLdouble width, height;
int wd;
Board board;
HitSelection hs;
Game g = Game();
Tangle startButton;
Tangle helpButton;
Tangle hhButton;
Tangle hcButton;
Tangle hMenu;
Tangle legend;
UserBoard userboard;
User2Board user2Board;
Tangle exitButton;
Tangle infoButton;
Tangle iMenu;


Tangle nuke;
Tangle nukeSelect;

Tangle finishPlacing;

Fleet fleet;


bool moveSelected;

int numOfShipsPlaced;

enum gameState{menu,mode,hhGame,shipPosition,hitSelection,bye,help,info,idleGame,PVP,setPlayerOne, setPlayerTwo};

gameState screen;
bool dragging;
bool draggingD;

void init() {
    moveSelected=false;
    dragging=false;
    numOfShipsPlaced=0;
    fleet=Fleet();

    screen= menu;
    width = 900;
    height = 600;
    fleet.setCarrierStatus(unselected);
    fleet.setBattleStatus(unselected);
    fleet.setDestroyerStatus(unselected);
    fleet.setSubStatus(unselected);
    fleet.setCruiserStatus(unselected);
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */

void startMenu(){
    startButton.setDimensions(100, 100);
    startButton.setFillColor(0, 0, 0);
    startButton.setBorderColor(0,255,0);
    startButton.setCenter(235, 300);

    startButton.draw();

    helpButton.setDimensions(40, 40);
    helpButton.setFillColor(0, 0, 0);
    helpButton.setBorderColor(0,255,0);
    helpButton.setCenter(30, 30);

    helpButton.draw();

    infoButton.setDimensions(40, 40);
    infoButton.setFillColor(0, 0, 0);
    infoButton.setBorderColor(0,255,0);
    infoButton.setCenter(80, 30);

    infoButton.draw();

    glColor3f(0,255,0);


    glBegin(GL_TRIANGLES);

    glVertex2f(215,270);
    glVertex2f(260,300);
    glVertex2f(215,330);

    glEnd();


    string title = "Battleship";

    string help = "?";
    string info = "i";


    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(190, 175);
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(25, 35);
    for (char h :help) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(78, 35);
    for (char h :info) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h);
    }

}

void modeMenu(){
    hhButton.setDimensions(100, 100);
    hhButton.setFillColor(0, 0, 0);
    hhButton.setBorderColor(0,255,0);
    hhButton.setCenter(170, 300);

    hhButton.draw();

    hcButton.setDimensions(100, 100);
    hcButton.setFillColor(0, 0, 0);
    hcButton.setBorderColor(0,255,0);
    hcButton.setCenter(330, 300);

    hcButton.draw();

    string hhTitle = "vs. Human";

    string hcTitle = "vs. Computer";

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(140, 300);
    for (char c : hhTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }


    glRasterPos2i(293, 300);
    for (char c : hcTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

}

void humanStart() {
    string hhTitle = "Human";

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(140, 300);
    for (char c : hhTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void compStart() {
    string hhTitle = "computer";

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(140, 300);
    for (char c : hhTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void helpMenu() {
    hMenu.setDimensions(160, 400);
    hMenu.setFillColor(0, 0, 0);
    hMenu.setBorderColor(0,255,0);
    hMenu.setCenter(250, 180);

    hMenu.draw();

    exitButton.setDimensions(30, 30);
    exitButton.setFillColor(0, 0, 0);
    exitButton.setBorderColor(0,255,0);
    exitButton.setCenter(470, 30);

    exitButton.draw();

    char exit = 'X';
    string help = "Help";
    string instructions = "Begin by placing your ships onto the board. You can choose what ";
    string instructions2 = "direction you want the ship to be facing. Once your board is ready ";
    string instructions3 = "to go guess where your opponents ship is by clicking on a square. ";
    string instructions4 = "You will either hit or miss their ship. The first to sink all their ";
    string instructions5 = "opponents ships will win.";


    glColor3f(0, 255, 0);
    glRasterPos2i(463, 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);


    glColor3f(0, 255, 0);
    glRasterPos2i(230, 130);
    for (char c : help) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(60, 160);
    for (char c : instructions) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(60, 175);
    for (char c : instructions2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(60, 190);
    for (char c : instructions3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(60, 205);
    for (char c : instructions4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(60, 220);
    for (char c : instructions5) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void infoMenu() {
    iMenu.setDimensions(160, 400);
    iMenu.setFillColor(0, 0, 0);
    iMenu.setBorderColor(0,255,0);
    iMenu.setCenter(250, 180);

    iMenu.draw();

    helpButton.setDimensions(30, 30);
    helpButton.setFillColor(0, 0, 0);
    helpButton.setBorderColor(0,255,0);
    helpButton.setCenter(470, 30);

    helpButton.draw();

    char exit = 'X';
    string info = "Battleship was programmed by Oliver Groten, Harry Makovsky, ";
    string info2 = "Hannah Meharg, and Teemo Xu for our final project in CS205. ";
    string info3 = "We hope you have fun playing!";

    glColor3f(0, 255, 0);
    glRasterPos2i(463, 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);

    glColor3f(0, 255, 0);
    glRasterPos2i(60, 145);
    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(60, 160);
    for (char c : info2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(60, 175);
    for (char c : info3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

}

void selectPosition() {
    g.getUserBoard().draw(300,300);

    finishPlacing.setDimensions(40,80);
    finishPlacing.setBorderColor({0,255,0});
    finishPlacing.setCenter({470,350});
    finishPlacing.draw();

    string fin="DONE";

    glColor3f(0,255,0);
    glRasterPos2i(450,350);

    for(char c : fin){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    if(numOfShipsPlaced<5){
        string message="MUST PLACE ALL SHIPS BEFORE CONTINUING";

        glColor3f(0,255,0);
        glRasterPos2i(500,300);

        for(char c : message){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
        }
    }




    fleet.getCarrier().drawShip_car();
    fleet.getBattle().drawShip_battle();
    fleet.getCruiser().drawShip_cruiser();
    fleet.getSub().drawShip_sub();
    fleet.getDestroyer().drawShip_destroyer();

}

void selectPosition2() {
    numOfShipsPlaced = 0;
    g.getUserBoard().draw(300,300);

    finishPlacing.setDimensions(40,80);
    finishPlacing.setBorderColor({0,255,0});
    finishPlacing.setCenter({470,350});
    finishPlacing.draw();

    string fin="DONE";

    glColor3f(0,255,0);
    glRasterPos2i(450,350);

    for(char c : fin){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    if(numOfShipsPlaced<5){
        string message="MUST PLACE ALL SHIPS BEFORE CONTINUING";

        glColor3f(0,255,0);
        glRasterPos2i(500,300);

        for(char c : message){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
        }
    }




    fleet.getCarrier2().drawShip_car2();
    fleet.getBattle2().drawShip_battle2();
    fleet.getCruiser2().drawShip_cruiser2();
    fleet.getSub2().drawShip_sub2();
    fleet.getDestroyer2().drawShip_destroyer2();

}


void display(){
    glViewport(0, 0, width, height);
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    switch(screen) {

        case menu:
//            glColor3f(1.0,0.0,0.0);
//            glBegin(GL_QUADS);
//            glVertex2d(0.0,0.0);
//            glVertex2d(100.0,0.0);
//            glVertex2d(100.0,100.0);
//            glVertex2d(0.0,100.0);
//            glEnd();
//            glColor3f(0.0,1.0,0.0);
//            glBegin(GL_QUADS);
//            glVertex2d(10.0,10.0);
//            glVertex2d(90.0,10.0);
//            glVertex2d(90.0,90.0);
//            glVertex2d(10.0,90.0);
//            glEnd();
            startMenu();
            break;
        case mode:
            modeMenu();
            break;
        case hhGame:
            humanStart();
            break;
        case shipPosition:
            selectPosition();
            break;
        case PVP:
            g.getUserBoard().draw(900,600);
            g.getUser2Board().draw(900,600);
            break;
        case setPlayerOne:
            selectPosition();
            break;
        case setPlayerTwo:
            selectPosition2();
            break;
        case idleGame: {
            g.getUserBoard().draw(900, 600);
            g.getComputerBoard().draw();

            if(g.getComputerBoard().getFleet().sunk() or g.getUserBoard().getFleet().sunk()){
                screen=menu;
                if(g.getComputerBoard().getFleet().sunk()){
                    cout<<"USER WON"<<endl;
                }else{
                    cout<<"COMP WON"<<endl;
                }
            }

            nuke.setDimensions(40, 80);
            nuke.setBorderColor({0, 255, 0});
            nuke.setCenter({600, 500});
            nuke.draw();

            string fin = "PEARL";

            glColor3f(0, 255, 0);
            glRasterPos2i(600, 500);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }


            break;
        }
        case hitSelection: {
            //hs.draw(width, height);
            hs.draw(width, height);

            nukeSelect.setDimensions(40, 80);
            nukeSelect.setBorderColor({0, 255, 0});
            nukeSelect.setCenter({800, 300});
            nukeSelect.draw();

            string fin = "DONE";

            glColor3f(0, 255, 0);
            glRasterPos2i(800, 300);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
            // get cell clicked
            // update hitSelection board
            //hs.update(g.getComputerBoard());
            break;
        }
        case bye:
            break;
        case help:
            helpMenu();
            break;
        case info:
            infoMenu();
            break;

    }

    glEnd();
    glFlush();  // Render now
}


// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    //escape key exits window
    if (key == 27) {

        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 112) {
        g.placePiecesDebug();

    }
    if (key == 114 && dragging==true) {
        cout<<"rotate"<<endl;

        if (fleet.getCarrierStatus() == selected) {
            int w=fleet.getCarrier().carrierShipTang.getLength();
            int l=fleet.getCarrier().carrierShipTang.getWidth();
            Ship n= fleet.getCarrier();
            n.carrierShipTang.setDimensions(l,w);
            n.rotate();

            fleet.setCarrier(n);
        }

        if (fleet.getCarrierStatus() == selected) {
            int w=fleet.getCarrier2().carrierShipP2.getLength();
            int l=fleet.getCarrier2().carrierShipP2.getWidth();
            Ship n= fleet.getCarrier2();
            n.carrierShipP2.setDimensions(l,w);
            n.rotate();

            fleet.setCarrier2(n);
        }

        if (fleet.getBattleStatus() == selected) {
            int w=fleet.getBattle().battleShipTang.getLength();
            int l=fleet.getBattle().battleShipTang.getWidth();

            Ship n= fleet.getBattle();
            n.battleShipTang.setDimensions(l,w);
            n.rotate();

            fleet.setBattle(n);
        }

        if (fleet.getCruiserStatus() == selected) {
            int w=fleet.getCruiser().cruiserShipTang.getLength();
            int l=fleet.getCruiser().cruiserShipTang.getWidth();

            Ship n= fleet.getCruiser();
            n.cruiserShipTang.setDimensions(l,w);
            n.rotate();

            fleet.setCruiser(n);
        }

        if (fleet.getSubStatus() == selected) {
            int w=fleet.getSub().subShipTang.getLength();
            int l=fleet.getSub().subShipTang.getWidth();

            Ship n= fleet.getSub();
            n.subShipTang.setDimensions(l,w);
            n.rotate();

            fleet.setSub(n);
        }

        if (fleet.getDestroyerStatus() == selected) {
            int w=fleet.getDestroyer().destroyerShipTang.getLength();
            int l=fleet.getDestroyer().destroyerShipTang.getWidth();

            Ship n= fleet.getDestroyer();
            n.destroyerShipTang.setDimensions(l,w);
            n.rotate();

            fleet.setDestroyer(n);
        }


    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {


        case GLUT_KEY_DOWN:

            break;

        case GLUT_KEY_LEFT:

            break;

        case GLUT_KEY_RIGHT:

            break;

        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}



// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {


    if(button==GLUT_LEFT_BUTTON && state== GLUT_DOWN && screen== hitSelection && x> 175 && x<675 && y>50 && y<550 && !moveSelected){
        point p=hs.getCell(x,y);

        if(g.userMove(p.x,p.y)){
            hs.update(g.getComputerBoard());
            moveSelected=true;
        }
        //g.userMove(p.x,p.y);
//        hs.update(g.getComputerBoard());
//        moveSelected=true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 184 && x < 286 && y > 249 && y < 351 && screen == menu ){
        screen = mode;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 9 && x < 51 && y > 9 && y < 51 && screen == menu ){
        screen = help;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 59 && x < 101 && y > 9 && y < 51 && screen == menu ){
        screen = info;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 454 && x < 486 && y > 14 && y < 46 && screen == help ){
        screen = menu;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 454 && x < 486 && y > 14 && y < 46 && screen == info ){
        screen = menu;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 121 && x < 219 && y > 251 && y < 349 && screen == mode ){
        screen = setPlayerOne;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 281 && x < 381 && y > 249 && y < 351 && screen == mode ){
        screen = shipPosition;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 410 && x < 490 && y > 330 && y < 370 && screen == shipPosition && numOfShipsPlaced==5) {
        g.placePiecesDebug();
        screen = idleGame;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 410 && x < 490 && y > 330 && y < 370 && screen == setPlayerOne && numOfShipsPlaced==5) {
        g.placePiecesDebug();
        screen = setPlayerTwo;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 410 && x < 490 && y > 330 && y < 370 && screen == setPlayerTwo && numOfShipsPlaced==5) {
        g.placePiecesDebug();
        screen = PVP;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 560 && x < 640 && y > 480 && y < 520 && screen == idleGame){
        screen = hitSelection;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 760 && x < 840 && y > 280 && y < 320 && screen == hitSelection && moveSelected){
        screen = idleGame;
        g.compMove();
        moveSelected=false;
    }

    // check if cursor is overlapping chip store bool
    // if it is store ship type
    // create variable isOverlappoingASHip?
    // if it is go in and
    // set status to whatever ship
    // select unselect

    // for carrier
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getCarrier().carrierShipTang.isOverlapping({x,y})
        && (screen == shipPosition || screen == setPlayerOne) && fleet.getCarrierStatus() == unselected){
        cout << "DRAGGABLE carrier" << endl;
        fleet.setCarrierStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getCarrier().carrierShipTang.isOverlapping({x,y})
        && (screen == shipPosition || screen == setPlayerOne) && fleet.getCarrierStatus() == selected) {
        cout << "UNSELECTED" << endl;
        fleet.setCarrierStatus(unselected);
        dragging=false;

        //get top or side pos


        for (vector<Tangle> row : g.getUserBoard().cells) {
            for (Tangle c : row) {
                if(fleet.getCarrier().getVert()){
                    if (c.isOverlapping({x,y-60})) {
                        point p = c.getBoardCell();

                        if(g.getUserBoard().checkClear(p.x,p.y,5,2)){
                            g.placeShip(Carrier, p.x, p.y,2);
                            Ship n= fleet.getCarrier();
                            n.carrierShipTang.setDimensions(0,0);
                            fleet.setCarrier(n);
                            numOfShipsPlaced++;
                        }

                    }
                }else{
                    if (c.isOverlapping({x+60,y})) {
                        point p = c.getBoardCell();
                        if(g.getUserBoard().checkClear(p.x,p.y,5,0)){
                            g.placeShip(Carrier, p.x, p.y,0);
                            Ship n= fleet.getCarrier();
                            n.carrierShipTang.setDimensions(0,0);
                            fleet.setCarrier(n);
                            numOfShipsPlaced++;
                        }

                    }
                }
            }
        }

//        point p = g.getUserBoard().cells[5][5].getBoardCell();
//        g.placeShip(Carrier,p.x,p.y,0);
    }


//    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getCarrier().carrierShipTang.isOverlapping({x,y})
//        && screen == setPlayerOne && fleet.getCarrierStatus() == unselected){
//        cout << "DRAGGABLE carrier" << endl;
//        fleet.setCarrierStatus(selected);
//        wait((int*)1);
//        dragging=true;
//    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getCarrier().carrierShipTang.isOverlapping({x,y})
//              && screen == setPlayerOne && fleet.getCarrierStatus() == selected) {
//        cout << "UNSELECTED" << endl;
//        fleet.setCarrierStatus(unselected);
//        dragging=false;
//
//        //get top or side pos
//
//
//        for (vector<Tangle> row : g.getUserBoard().cells) {
//            for (Tangle c : row) {
//                if(fleet.getCarrier().getVert()){
//                    if (c.isOverlapping({x,y-60})) {
//                        point p = c.getBoardCell();
//
//                        if(g.getUserBoard().checkClear(p.x,p.y,5,2)){
//                            g.placeShip(Carrier, p.x, p.y,2);
//                            Ship n= fleet.getCarrier();
//                            n.carrierShipTang.setDimensions(0,0);
//                            fleet.setCarrier(n);
//                            numOfShipsPlaced++;
//                        }
//
//                    }
//                }else{
//                    if (c.isOverlapping({x+60,y})) {
//                        point p = c.getBoardCell();
//                        if(g.getUserBoard().checkClear(p.x,p.y,5,0)){
//                            g.placeShip(Carrier, p.x, p.y,0);
//                            Ship n= fleet.getCarrier();
//                            n.carrierShipTang.setDimensions(0,0);
//                            fleet.setCarrier(n);
//                            numOfShipsPlaced++;
//                        }
//
//                    }
//                }
//            }
//        }
//
////        point p = g.getUserBoard().cells[5][5].getBoardCell();
////        g.placeShip(Carrier,p.x,p.y,0);
//    }


    // do if else for battle
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getBattle().battleShipTang.isOverlapping({x,y})
        && (screen == shipPosition || screen == setPlayerOne) && fleet.getBattleStatus() == unselected){
        cout << "DRAGGABLE sub" << endl;
        fleet.setBattleStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getBattle().battleShipTang.isOverlapping({x,y})
              && (screen == shipPosition || screen == setPlayerOne) && fleet.getBattleStatus() == selected) {
        cout << "UNSELECTED" << endl;
        fleet.setBattleStatus(unselected);
        dragging=false;

        for (vector<Tangle> row : g.getUserBoard().cells) {
            for (Tangle c : row) {
                if(fleet.getBattle().getVert()){
                    if (c.isOverlapping({x,y-45})) {
                        point p = c.getBoardCell();

                        if(g.getUserBoard().checkClear(p.x,p.y,4,2)){
                            g.placeShip(Battleship, p.x, p.y,2);
                            Ship n= fleet.getBattle();
                            n.battleShipTang.setDimensions(0,0);
                            fleet.setBattle(n);
                            numOfShipsPlaced++;
                        }

                    }
                }else{
                    if (c.isOverlapping({x+45,y})) {
                        point p = c.getBoardCell();
                        if(g.getUserBoard().checkClear(p.x,p.y,4,0)){
                            g.placeShip(Battleship, p.x, p.y,0);
                            Ship n= fleet.getBattle();
                            n.battleShipTang.setDimensions(0,0);
                            fleet.setBattle(n);
                            numOfShipsPlaced++;
                        }

                    }
                }
            }
        }
    }



    // do if else for cruiser
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getCruiser().cruiserShipTang.isOverlapping({x,y})
        && (screen == shipPosition || screen == setPlayerOne) && fleet.getCruiserStatus() == unselected){
        cout << "DRAGGABLE sub" << endl;
        fleet.setCruiserStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getCruiser().cruiserShipTang.isOverlapping({x,y})
              && (screen == shipPosition || screen == setPlayerOne) && fleet.getCruiserStatus() == selected) {
        cout << "UNSELECTED" << endl;
        fleet.setCruiserStatus(unselected);
        dragging=false;

        for (vector<Tangle> row : g.getUserBoard().cells) {
            for (Tangle c : row) {
                if(fleet.getCruiser().getVert()){
                    if (c.isOverlapping({x,y-15})) {
                        point p = c.getBoardCell();

                        if(g.getUserBoard().checkClear(p.x,p.y,2,2)){
                            g.placeShip(Cruiser, p.x, p.y,2);
                            Ship n= fleet.getCruiser();
                            n.cruiserShipTang.setDimensions(0,0);
                            fleet.setCruiser(n);
                            numOfShipsPlaced++;
                        }

                    }
                }else{
                    if (c.isOverlapping({x+15,y})) {
                        point p = c.getBoardCell();
                        if(g.getUserBoard().checkClear(p.x,p.y,2,0)){
                            g.placeShip(Cruiser, p.x, p.y,0);
                            Ship n= fleet.getCruiser();
                            n.cruiserShipTang.setDimensions(0,0);
                            fleet.setCruiser(n);
                            numOfShipsPlaced++;
                        }

                    }
                }
            }
        }
    }

    // do if else for sub
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getSub().subShipTang.isOverlapping({x,y})
        && (screen == shipPosition || screen == setPlayerOne) && fleet.getSubStatus() == unselected){
        cout << "DRAGGABLE sub" << endl;
        fleet.setSubStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getSub().subShipTang.isOverlapping({x,y})
              && (screen == shipPosition || screen == setPlayerOne) && fleet.getSubStatus() == selected) {
        cout << "UNSELECTED" << endl;
        fleet.setSubStatus(unselected);
        dragging=false;

        for (vector<Tangle> row : g.getUserBoard().cells) {
            for (Tangle c : row) {
                if(fleet.getSub().getVert()){
                    if (c.isOverlapping({x,y-30})) {
                        point p = c.getBoardCell();

                        if(g.getUserBoard().checkClear(p.x,p.y,3,2)){
                            g.placeShip(Sub, p.x, p.y,2);
                            Ship n= fleet.getSub();
                            n.subShipTang.setDimensions(0,0);
                            fleet.setSub(n);
                            numOfShipsPlaced++;
                        }

                    }
                }else{
                    if (c.isOverlapping({x+30,y})) {
                        point p = c.getBoardCell();
                        if(g.getUserBoard().checkClear(p.x,p.y,3,0)){
                            g.placeShip(Sub, p.x, p.y,0);
                            Ship n= fleet.getSub();
                            n.subShipTang.setDimensions(0,0);
                            fleet.setSub(n);
                            numOfShipsPlaced++;
                        }

                    }
                }
            }
        }
    }

    // do if else for destroyer
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getDestroyer().destroyerShipTang.isOverlapping({x,y})
        && (screen == shipPosition || screen == setPlayerOne) && fleet.getDestroyerStatus() == unselected){
        cout << "DRAGGABLE destroyer" << endl;
        fleet.setDestroyerStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getDestroyer().destroyerShipTang.isOverlapping({x,y})
              && (screen == shipPosition || screen == setPlayerOne) && fleet.getDestroyerStatus() == selected) {
        cout << "UNSELECTED" << endl;
        fleet.setDestroyerStatus(unselected);
        dragging=false;
        for (vector<Tangle> row : g.getUserBoard().cells) {
            for (Tangle c : row) {
                if(fleet.getDestroyer().getVert()){
                    if (c.isOverlapping({x,y-30})) {
                        point p = c.getBoardCell();

                        if(g.getUserBoard().checkClear(p.x,p.y,3,2)){
                            g.placeShip(Destroyer, p.x, p.y,2);
                            Ship n= fleet.getDestroyer();
                            n.destroyerShipTang.setDimensions(0,0);
                            fleet.setDestroyer(n);
                            numOfShipsPlaced++;
                        }

                    }
                }else{
                    if (c.isOverlapping({x+30,y})) {
                        point p = c.getBoardCell();
                        if(g.getUserBoard().checkClear(p.x,p.y,3,0)){
                            g.placeShip(Destroyer, p.x, p.y,0);
                            Ship n= fleet.getDestroyer();
                            n.destroyerShipTang.setDimensions(0,0);
                            fleet.setDestroyer(n);
                            numOfShipsPlaced++;
                        }

                    }
                }
            }
        }
    }





//    while (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == shipPosition ){
//        cout << x << endl;
//        cout << y << endl;
//        fleet.drag(x,y);
//
//    }
//

    glutPostRedisplay();

}

void cursor(int x, int y) {

    if (fleet.getCarrierStatus() == selected) {
        fleet.dragCarrier(x, y);
    }
    if (fleet.getCarrier2Status() == selected) {
        fleet.dragCarrier2(x, y);
    }

    if (fleet.getBattleStatus() == selected) {
        fleet.dragBattle(x, y);
    }

    if (fleet.getCruiserStatus() == selected) {
        fleet.dragCruiser(x, y);
    }

    if (fleet.getSubStatus() == selected) {
        fleet.dragSub(x, y);
    }

    if (fleet.getDestroyerStatus() == selected) {
        fleet.dragDestroyer(x, y);
    }

    glutPostRedisplay();

}
void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}



/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

//    Game game= Game();
//    if(game.startGame()){
//        game.playGame();
//        game.endGame();
//    }

//    UserBoard user;
//    user.placePieces();
//    user.printBoard();
//
//    cout<<"---------------------------------\n";
//    for(int i= 0; i< 99 ; i++){
//        cout<<i<<endl;
//        //wait(new int(1));
//        while(!user.compMove());
//    }
//    user.printBoard();

//    ComputerBoard comp;
//
//    comp.printBoard();
//    cout<<"---------------------------------\n";
//    comp.placePieces();
//    comp.printBoard();
//
//    int row;
//    int col;
//    string s="";
//
//    while(!comp.getFleet().sunk()) {
//        cout << "Row?" << endl;
//        row = getIntInput(s);
//        while (row < 0 or row > 9) {
//            cout << "Invalid Number" << endl;
//          row = getIntInput(s);
//        }
//
//        cout << "Col?" << endl;
//        col = getIntInput(s);
//        while (col < 0 or col > 9) {
//            cout << "Invalid Number" << endl;
//            col = getIntInput(s);
//        }
//
//        while (!comp.userMove(row, col)) {
//            cout << "INVALID MOVE" << endl;
//            cout << "Row?" << endl;
//            row = getIntInput(s);
//            while (row < 0 or row > 9) {
//                cout << "Invalid Number" << endl;
//                row = getIntInput(s);
//            }
//
//            cout << "Col?" << endl;
//            col = getIntInput(s);
//            while (col < 0 or col > 9) {
//                cout << "Invalid Number" << endl;
//                col = getIntInput(s);
//            }
//        }
//    }
//    comp.printBoard();
//
//    UserBoard user;
//    user.printBoard();
//    cout<<"---------------------------------\n";
//    user.placePieces();
//    user.printBoard();
//    cout<<"---------------------------------\n";
//    for(int i=0;i<5;i++){
//        while(!user.compMove());
//    }
//    user.printBoard();



    init();

    // Initialize GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);

    // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    glutInitWindowPosition(200,100);

    wd = glutCreateWindow("BATTLESHIP" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.

    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}

