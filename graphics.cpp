#include "graphics.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include "algorithm"
#include "cstdlib"
#include "ctime"

#include "ComputerBoard.h"
#include "UserBoard.h"
#include "Ship.h"
#include "Game.h"
#include "Background.h"
#include "HitSelection.h"
#include <sstream>


using namespace std;
GLdouble width, height;
int wd;
Board board;
HitSelection hs;
HitSelection hsp1;
HitSelection hsp2;

Game pvc;
Game pvp;
Tangle startButton;
Tangle helpButton;
Tangle hhButton;
Tangle hcButton;
Tangle hMenu;
Tangle legend;
UserBoard userboard;
UserBoard user2Board;
Tangle exitButton;
Tangle exitButton2;
Tangle exitButton3;
Tangle infoButton;
Tangle iMenu;
Tangle square;
Tangle playGame;
Tangle b;
Background background;

Tangle nuke;
Tangle nukeSelect;

Tangle finishPlacing;

Fleet fleet;
Fleet user2fleet;

Tangle headerBox;



Tangle switchTurns;
Tangle nextTurn;

bool turnP1;

bool hovering;
bool placing;

bool p1MadeTurn;
bool p2MadeTurn;







bool moveSelected;

int numOfShipsPlaced, numOfShipsPlaced2;

enum gameState{menu,mode,hhGame,shipPosition,hitSelection,bye,help,info,idleGame,setPlayerOne, setPlayerTwo,p2turn,p1turn,p1hs,p2hs,middle};

gameState screen;
bool dragging;
bool draggingD;

void init() {
    background=Background();
    pvp=Game();
    pvc=Game();

    hovering=false;


    moveSelected=false;
    dragging=false;
    numOfShipsPlaced=0;
    fleet=Fleet();
    user2fleet=Fleet();
    placing=false;

    turnP1=false;
    p1MadeTurn=false;
    p2MadeTurn=false;

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
    b.startingScreen(b);

    startButton.setDimensions(100, 100);
    startButton.setFillColor(0, 0, 0);
    if(!hovering){
        startButton.setBorderColor(0,255,0);
    }
    startButton.setCenter(450, 300);

    startButton.draw();

    helpButton.setDimensions(40, 40);
    helpButton.setFillColor(0, 0, 0);
    if(!hovering){
        helpButton.setBorderColor(0,255,0);
    }
    helpButton.setCenter(30, 30);

    helpButton.draw();

    infoButton.setDimensions(40, 40);
    infoButton.setFillColor(0, 0, 0);
    if(!hovering){
        infoButton.setBorderColor(0,255,0);
    }
    infoButton.setCenter(80, 30);

    infoButton.draw();

    glColor3f(0,255,0);


    glBegin(GL_TRIANGLES);

    glVertex2f(425,270);
    glVertex2f(485,300);
    glVertex2f(425,330);


    glEnd();

    string help = "?";
    string info = "i";


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
    hhButton.setDimensions(50, 300);
    hhButton.setFillColor(0, 0, 0);

    if(!hovering){
        hhButton.setBorderColor(0,255,0);
    }

    hhButton.setCenter(450, 150);

    hhButton.draw();

    hcButton.setDimensions(50, 300);
    hcButton.setFillColor(0, 0, 0);

    if(!hovering){
        hcButton.setBorderColor(0,255,0);
    }

    hcButton.setCenter(450, 450);

    hcButton.draw();

    string hhTitle = "vs. Human";

    string hcTitle = "vs. Computer";

    glColor3f(0, 255, 0);
    glRasterPos2i(400, 157);
    for (char c : hhTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }


    glRasterPos2i(390, 457);
    for (char c : hcTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

}

void displaySunken(Fleet f){
    Tangle t= Tangle(100,200,{0,1,0},{0,0,0},{200,500});
    t.draw();

    string title = "Comp Ships Sunken";

    glColor3f(0, 1.0, 0);
    glRasterPos2i(146, 467);
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    string bar = "-------------------------";

    glColor3f(0, 1.0, 0);
    glRasterPos2i(101, 477);
    for (char c : bar) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    if(f.getCarrier().getDestroyed()){
        string ship = "o Carrier";

        glColor3f(0, 1.0, 0);
        glRasterPos2i(115, 493);
        for (char c : ship) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

    }
    if(f.getBattle().getDestroyed()){
        string ship = "o BattleShip";

        glColor3f(0, 1.0, 0);
        glRasterPos2i(115, 513);
        for (char c : ship) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

    }
    if(f.getSub().getDestroyed()){
        string ship = "o Submarine";

        glColor3f(0, 1.0, 0);
        glRasterPos2i(115, 537);
        for (char c : ship) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }
    if(f.getDestroyer().getDestroyed()){
        string ship = "o Destroyer";

        glColor3f(0, 1.0, 0);
        glRasterPos2i(200, 493);
        for (char c : ship) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

    }
    if(f.getCruiser().getDestroyed()){
        string ship = "o Cruiser";

        glColor3f(0, 1.0, 0);
        glRasterPos2i(200, 513);
        for (char c : ship) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

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
    hMenu.setDimensions(240, 600);
    hMenu.setFillColor(0, 0, 0);
    hMenu.setBorderColor(0,255,0);
    hMenu.setCenter(470, 235);

    hMenu.draw();

    exitButton.setDimensions(30, 30);
    exitButton.setFillColor(0, 0, 0);

    if(!hovering){
        exitButton.setBorderColor(0,255,0);
    }

    exitButton.setCenter(850, 30);

    exitButton.draw();

    char exit = 'X';
    string help = "Help";
    string instructions = "Begin by placing your ships onto the board. You can choose what ";
    string instructions2 = "direction you want the ship to be facing. Once your board is ready ";
    string instructions3 = "to go guess where your opponents ship is by clicking on a square. ";
    string instructions4 = "You will either hit or miss their ship. The first to sink all their ";
    string instructions5 = "opponents ships will win.";


    glColor3f(0, 255, 0);
    glRasterPos2i(843, 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);


    glColor3f(0, 255, 0);
    glRasterPos2i(430, 150);
    for (char c : help) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(195, 190);
    for (char c : instructions) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(195, 220);
    for (char c : instructions2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(195, 250);
    for (char c : instructions3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(195, 280);
    for (char c : instructions4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(195, 310);
    for (char c : instructions5) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void infoMenu() {
    iMenu.setDimensions(200, 600);
    iMenu.setFillColor(0, 0, 0);
    iMenu.setBorderColor(0,255,0);
    iMenu.setCenter(470, 205);

    iMenu.draw();

    helpButton.setDimensions(30, 30);
    helpButton.setFillColor(0, 0, 0);
    if(!hovering){
        helpButton.setBorderColor(0,255,0);
    }

    helpButton.setCenter(850, 30);

    helpButton.draw();

    char exit = 'X';
    string info = "Battleship was programmed by Oliver Groten, Harry Makovsky, ";
    string info2 = "Hannah Meharg, and Teemo Xu for our final project in CS205. ";
    string info3 = "We hope you have fun playing!";

    glColor3f(0, 255, 0);
    glRasterPos2i(843, 35);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);

    glColor3f(0, 255, 0);
    glRasterPos2i(195, 145);
    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(195, 175);
    for (char c : info2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glColor3f(0, 255, 0);
    glRasterPos2i(195, 205);
    for (char c : info3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

}

void selectPosition() {
    pvc.getUserBoard().draw(300,300);

    finishPlacing.setDimensions(40,80);

    if(!hovering){
        finishPlacing.setBorderColor({0,255,0});
    }

    finishPlacing.setCenter({470,350});
    finishPlacing.draw();

    string fin="DONE";
    string rotateString = "To rotate a ship, select it then click 'r' on your keyboard.";

    glColor3f(0,255,0);
    glRasterPos2i(450,350);

    for(char c : fin){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    string selectString = "Click once to select, then drag and click again to place it.";

    glColor3f(0,255,0);
    glRasterPos2i(50,90);

    for(char c : selectString){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(50, 415);
    for (char r : rotateString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, r);
    }

    if(numOfShipsPlaced<5){
        string message="MUST PLACE ALL SHIPS BEFORE CONTINUING";

        glColor3f(0,255,0);
        glRasterPos2i(420,300);

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

void resetGame() {
    board = Board();
    hs = HitSelection();
    hsp1 = HitSelection();
    hsp2 = HitSelection();

    pvc = Game();
    pvp = Game();
    userboard = UserBoard();
    user2Board = UserBoard();

    background=Background();

    hovering=false;


    moveSelected=false;
    dragging=false;
    numOfShipsPlaced=0;
    fleet=Fleet();
    user2fleet=Fleet();
    screen = bye;
    fleet.setCarrierStatus(unselected);
    fleet.setBattleStatus(unselected);
    fleet.setDestroyerStatus(unselected);
    fleet.setSubStatus(unselected);
    fleet.setCruiserStatus(unselected);

    init();
}

void selectPosition1() {
    pvp.getUserBoard().draw(300,300);

    finishPlacing.setDimensions(40,80);
    if(!hovering){
        finishPlacing.setBorderColor({0,255,0});
    }
    finishPlacing.setCenter({470,350});
    finishPlacing.draw();

    string fin="DONE";
    string rotateString = "*to rotate a ship, select it then click 'r' on your keyboard.";

    glColor3f(0,255,0);
    glRasterPos2i(450,350);

    for(char c : fin){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    glColor3f(0, 255, 0);
    glRasterPos2i(50, 415);
    for (char r : rotateString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, r);
    }


    headerBox.setDimensions(45,100);
    headerBox.setBorderColor({0,255,0});
    headerBox.setCenter({460,50});
    headerBox.draw();

    string p1H = "Player 1";
    glColor3f(0.0, 1.0, 0.0);
    glRasterPos2i(420, 55);
    for (char r : p1H) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r);
    }

    string selectString = "Click once to select, then drag and click again to place it.";

    glColor3f(0,255,0);
    glRasterPos2i(50,90);

    for(char c : selectString){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    if(numOfShipsPlaced<5){
        string message="MUST PLACE ALL SHIPS BEFORE CONTINUING";

        glColor3f(0,255,0);
        glRasterPos2i(420,300);

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
    pvp.getUser2Board().draw(300,300);

    finishPlacing.setDimensions(40,80);
    if(!hovering){
        finishPlacing.setBorderColor({0,255,0});
    }
    finishPlacing.setCenter({470,350});
    finishPlacing.draw();

    string fin="DONE";

    glColor3f(0,255,0);
    glRasterPos2i(450,350);

    for(char c : fin){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    string rotateString = "*to rotate a ship, select it then click 'r' on your keyboard.";

    glColor3f(0, 255, 0);
    glRasterPos2i(50, 415);
    for (char r : rotateString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, r);
    }

    headerBox.setDimensions(45,100);
    headerBox.setBorderColor({0,255,0});
    headerBox.setCenter({460,50});
    headerBox.draw();

    string p1H = "Player 2";
    glColor3f(0.0, 1.0, 0.0);
    glRasterPos2i(420, 55);
    for (char r : p1H) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r);
    }

    string selectString = "Click once to select, then drag and click again to place it.";

    glColor3f(0,255,0);
    glRasterPos2i(50,90);

    for(char c : selectString){
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

    user2fleet.getCarrier().drawShip_car();
    user2fleet.getBattle().drawShip_battle();
    user2fleet.getCruiser().drawShip_cruiser();
    user2fleet.getSub().drawShip_sub();
    user2fleet.getDestroyer().drawShip_destroyer();

}


void display() {
    glViewport(0, 0, width, height);
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    switch (screen) {

        case menu:
            background.draw();
            background.scroll(1);
            background.drawShips();
            background.scrollShips(1);
            startMenu();
            break;
        case mode:
            background.draw();
            background.scroll(1);
            modeMenu();
            break;
        case hhGame:
            background.draw();
            background.scroll(1);
            humanStart();
            break;
        case shipPosition:
            background.draw();
            background.scroll(1);
            selectPosition();
            break;
        case setPlayerOne:
            background.draw();
            background.scroll(1);
            selectPosition1();
            break;
        case setPlayerTwo:
            background.draw();
            background.scroll(1);
            selectPosition2();
            break;
        case p1turn: {
            background.draw();
            background.scroll(1);
            pvp.getUserBoard().draw(900, 600);
            pvp.getUser2Board().drawHidden();

            if (pvp.getUser2Board().getFleet().sunk() or pvp.getUserBoard().getFleet().sunk()) {
                screen = bye;
            }

            nuke.setDimensions(40, 80);

            if (!hovering) {
                nuke.setBorderColor({0, 255, 0});
            }

            displaySunken(pvp.getUser2Board().getFleet());



            nuke.setCenter({600, 500});

            if (!p1MadeTurn) {
                nuke.draw();

                string fin = "ATTACK";

                glColor3f(0, 255, 0);
                glRasterPos2i(570, 500);
                for (char c : fin) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
                }
            }

            nextTurn.setDimensions(40, 80);
            if (!hovering) {
                nextTurn.setBorderColor({0, 255, 0});
            }
            nextTurn.setCenter({700, 500});

            if (p1MadeTurn) {
                nextTurn.draw();

                string next = "P2 TURN";

                glColor3f(0, 255, 0);
                glRasterPos2i(670, 500);
                for (char c : next) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
                }
            }

            headerBox.setDimensions(45,100);
            headerBox.setBorderColor({0,255,0});
            headerBox.setCenter({460,50});
            headerBox.draw();

            string p1H = "Player 1";
            glColor3f(0.0, 1.0, 0.0);
            glRasterPos2i(420, 55);
            for (char r : p1H) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r);
            }

            break;
        }
        case p2turn: {
            background.draw();
            background.scroll(1);
            pvp.getUser2Board().draw(900, 600);
            pvp.getUserBoard().drawHidden();

            if (pvp.getUser2Board().getFleet().sunk() or pvp.getUserBoard().getFleet().sunk()) {
                screen = bye;

            }

            nuke.setDimensions(40, 80);
            if (!hovering) {
                nuke.setBorderColor({0, 255, 0});
            }
            nuke.setCenter({600, 500});

            if (!p2MadeTurn) {
                nuke.draw();

                string fin = "ATTACK";

                glColor3f(0, 255, 0);
                glRasterPos2i(570, 500);
                for (char c : fin) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
                }
            }

            displaySunken(pvp.getUserBoard().getFleet());

            nextTurn.setDimensions(40, 80);

            if (!hovering) {
                nextTurn.setBorderColor({0, 255, 0});
            }


            nextTurn.setCenter({700, 500});
            if (p2MadeTurn) {
                nextTurn.draw();

                string next = "P1 TURN";

                glColor3f(0, 255, 0);
                glRasterPos2i(670, 500);
                for (char c : next) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
                }
            }

            headerBox.setDimensions(45,100);
            headerBox.setBorderColor({0,255,0});
            headerBox.setCenter({460,50});
            headerBox.draw();

            string p2H = "Player 2";

            glColor3f(0.0, 1.0, 0.0);
            glRasterPos2i(420, 55);
            for (char r : p2H) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r);
            }

            break;
        }
        case p1hs: {
            background.draw();
            background.scroll(1);
            //hs.draw(width, height);
            hsp1.draw(width, height);

            nukeSelect.setDimensions(40, 80);

            if (!hovering) {
                nukeSelect.setBorderColor({0, 255, 0});
            }

            nukeSelect.setCenter({800, 300});
            nukeSelect.draw();

            string fin = "FIRE";

            glColor3f(0, 255, 0);
            glRasterPos2i(780, 300);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
            // get cell clicked
            // update hitSelection board
            //hs.update(g.getComputerBoard());
            break;
        }
        case p2hs: {
            background.draw();
            background.scroll(1);
            //hs.draw(width, height);
            hsp2.draw(width, height);

            nukeSelect.setDimensions(40, 80);
            if (!hovering) {
                nukeSelect.setBorderColor({0, 255, 0});
            }
            nukeSelect.setCenter({800, 300});
            nukeSelect.draw();

            string fin = "FIRE";

            glColor3f(0, 255, 0);
            glRasterPos2i(780, 300);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
            // get cell clicked
            // update hitSelection board
            //hs.update(g.getComputerBoard());
            break;
        }
        case middle: {
            background.draw();
            background.scroll(1);


            switchTurns.setDimensions(200, 200);
            switchTurns.setFillColor(0, 0, 0);
            switchTurns.setBorderColor(0, 255, 0);
            switchTurns.setCenter(450, 300);

            switchTurns.draw();

            string fin = "HIT ENTER";

            glColor3f(0, 255, 0);
            glRasterPos2i(400, 300);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }


            break;
        }
        case idleGame: {

            background.draw();
            background.scroll(1);
            pvc.getUserBoard().draw(900, 600);
            pvc.getComputerBoard().draw();

            if (pvc.getComputerBoard().getFleet().sunk() or pvc.getUserBoard().getFleet().sunk()) {
                screen = bye;

            }

            nuke.setDimensions(40, 80);
            if (!hovering) {
                nuke.setBorderColor({0, 255, 0});
            }
            nuke.setCenter({600, 500});
            nuke.draw();

            string fin = "ATTACK";

            glColor3f(0, 255, 0);
            glRasterPos2i(570, 500);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }

            displaySunken(pvc.getComputerBoard().getFleet());

//            string p1B = "Player Board";
//
//            glColor3f(1.0, 0.0, 0.0);
//            glRasterPos2i(140, 55);
//            for (char r : p1B) {
//                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, r);
//            }

            break;
        }
        case hitSelection: {
            background.draw();
            background.scroll(1);
            //hs.draw(width, height);
            hs.draw(width, height);

            nukeSelect.setDimensions(40, 80);

            if(!hovering){
                nukeSelect.setBorderColor({0, 255, 0});
            }

            nukeSelect.setCenter({800, 300});
            nukeSelect.draw();

            string fin = "FIRE";

            glColor3f(0, 255, 0);
            glRasterPos2i(780, 300);
            for (char c : fin) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
            // get cell clicked
            // update hitSelection board
            //hs.update(g.getComputerBoard());
            break;
        }
        case bye:
            background.draw();
            background.scroll(1);
            background.drawShips();
            background.scrollShips(1);
            if(pvc.getComputerBoard().getFleet().sunk()){
                // print user won on screen
                string ending = "USER WON!";
                glColor3f(0, 255, 0);
                glRasterPos2i(450, 300);
                for (char r : ending) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, r);
                }

                // exit button to return to main menu
                exitButton3.setDimensions(30, 30);
                exitButton3.setFillColor(0, 0, 0);

                if(!hovering){
                    exitButton3.setBorderColor(0,255,0);
                }

                exitButton3.setCenter(850, 30);

                exitButton3.draw();

                char exit = 'X';
                glColor3f(0, 255, 0);
                glRasterPos2i(843, 35);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);


            }else if(pvc.getUserBoard().getFleet().sunk()){
                // print computer won on screen
                string ending = "COMPUTER WON!";
                glColor3f(0, 255, 0);
                glRasterPos2i(450, 300);
                for (char r : ending) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, r);
                }

                // exit button to return to menu can start new game
                exitButton3.setDimensions(30, 30);
                exitButton3.setFillColor(0, 0, 0);
                if(!hovering){
                    exitButton3.setBorderColor(0,255,0);
                }
                exitButton3.setCenter(850, 30);

                exitButton3.draw();

                char exit = 'X';
                glColor3f(0, 255, 0);
                glRasterPos2i(843, 35);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);
            }else if(pvp.getUserBoard().getFleet().sunk()){
                // print computer won on screen
                string ending = "USER 2 WON!";
                glColor3f(0, 255, 0);
                glRasterPos2i(450, 300);
                for (char r : ending) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, r);
                }

                // exit button to return to menu can start new game
                exitButton3.setDimensions(30, 30);
                exitButton3.setFillColor(0, 0, 0);
                if(!hovering){
                    exitButton3.setBorderColor(0,255,0);
                }
                exitButton3.setCenter(850, 30);

                exitButton3.draw();

                char exit = 'X';
                glColor3f(0, 255, 0);
                glRasterPos2i(843, 35);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);

            }else if(pvp.getUser2Board().getFleet().sunk()){
                // print computer won on screen
                string ending = "USER 1 WON!";
                glColor3f(0, 255, 0);
                glRasterPos2i(450, 300);
                for (char r : ending) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, r);
                }

                // exit button to return to menu can start new game
                exitButton3.setDimensions(30, 30);
                exitButton3.setFillColor(0, 0, 0);
                if(!hovering){
                    exitButton3.setBorderColor(0,255,0);
                }
                exitButton3.setCenter(850, 30);

                exitButton3.draw();

                char exit = 'X';
                glColor3f(0, 255, 0);
                glRasterPos2i(843, 35);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, exit);
            }



            break;
        case help:
            background.draw();
            background.scroll(1);
            helpMenu();
            break;
        case info:
            background.draw();
            background.scroll(1);
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
        pvc.placePiecesDebug();

    }

    if(key==13){
        if (screen == middle){

            if(!placing) {
                if (turnP1) {
                    screen = p2turn;
                    p2MadeTurn = false;
                    turnP1 = false;
                } else {
                    screen = p1turn;
                    p1MadeTurn = false;
                    turnP1 = true;
                }
            }else{

                screen=setPlayerTwo;
            }
        }

    }


    if (key == 114 && dragging==true) {


        if (screen == setPlayerOne || screen == shipPosition) {
            if (fleet.getCarrierStatus() == selected) {
                int w = fleet.getCarrier().carrierShipTang.getLength();
                int l = fleet.getCarrier().carrierShipTang.getWidth();
                Ship n = fleet.getCarrier();
                n.carrierShipTang.setDimensions(l, w);
                n.rotate();

                fleet.setCarrier(n);
            }

            if (fleet.getBattleStatus() == selected) {
                int w = fleet.getBattle().battleShipTang.getLength();
                int l = fleet.getBattle().battleShipTang.getWidth();

                Ship n = fleet.getBattle();
                n.battleShipTang.setDimensions(l, w);
                n.rotate();

                fleet.setBattle(n);
            }

            if (fleet.getCruiserStatus() == selected) {
                int w = fleet.getCruiser().cruiserShipTang.getLength();
                int l = fleet.getCruiser().cruiserShipTang.getWidth();

                Ship n = fleet.getCruiser();
                n.cruiserShipTang.setDimensions(l, w);
                n.rotate();

                fleet.setCruiser(n);
            }

            if (fleet.getSubStatus() == selected) {
                int w = fleet.getSub().subShipTang.getLength();
                int l = fleet.getSub().subShipTang.getWidth();

                Ship n = fleet.getSub();
                n.subShipTang.setDimensions(l, w);
                n.rotate();

                fleet.setSub(n);
            }

            if (fleet.getDestroyerStatus() == selected) {
                int w = fleet.getDestroyer().destroyerShipTang.getLength();
                int l = fleet.getDestroyer().destroyerShipTang.getWidth();

                Ship n = fleet.getDestroyer();
                n.destroyerShipTang.setDimensions(l, w);
                n.rotate();

                fleet.setDestroyer(n);
            }

        }



//////////////////////////////////////////////

        else if (screen == setPlayerTwo) {
            if (user2fleet.getCarrierStatus() == selected) {
                int w = user2fleet.getCarrier().carrierShipTang.getLength();
                int l = user2fleet.getCarrier().carrierShipTang.getWidth();
                Ship n = user2fleet.getCarrier();
                n.carrierShipTang.setDimensions(l, w);
                n.rotate();

                user2fleet.setCarrier(n);
            }

            if (user2fleet.getBattleStatus() == selected) {
                int w = user2fleet.getBattle().battleShipTang.getLength();
                int l = user2fleet.getBattle().battleShipTang.getWidth();

                Ship n = user2fleet.getBattle();
                n.battleShipTang.setDimensions(l, w);
                n.rotate();

                user2fleet.setBattle(n);
            }

            if (user2fleet.getCruiserStatus() == selected) {
                int w = user2fleet.getCruiser().cruiserShipTang.getLength();
                int l = user2fleet.getCruiser().cruiserShipTang.getWidth();

                Ship n = user2fleet.getCruiser();
                n.cruiserShipTang.setDimensions(l, w);
                n.rotate();

                user2fleet.setCruiser(n);
            }

            if (user2fleet.getSubStatus() == selected) {
                int w = user2fleet.getSub().subShipTang.getLength();
                int l = user2fleet.getSub().subShipTang.getWidth();

                Ship n = user2fleet.getSub();
                n.subShipTang.setDimensions(l, w);
                n.rotate();

                user2fleet.setSub(n);
            }

            if (user2fleet.getDestroyerStatus() == selected) {
                int w = user2fleet.getDestroyer().destroyerShipTang.getLength();
                int l = user2fleet.getDestroyer().destroyerShipTang.getWidth();

                Ship n = user2fleet.getDestroyer();
                n.destroyerShipTang.setDimensions(l, w);
                n.rotate();

                user2fleet.setDestroyer(n);
            }

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

        if(pvc.userMove(p.x,p.y)){
            hs.update(pvc.getComputerBoard());
            moveSelected=true;
        }

    }

    if(button==GLUT_LEFT_BUTTON && state== GLUT_DOWN && screen== p1hs && x> 175 && x<675 && y>50 && y<550 && !moveSelected){
        point p=hsp1.getCell(x,y);

        if(pvp.user1Move(p.x,p.y)){
            hsp1.update(pvp.getUser2Board());
            moveSelected=true;
        }

    }
    if(button==GLUT_LEFT_BUTTON && state== GLUT_DOWN && screen== p2hs && x> 175 && x<675 && y>50 && y<550 && !moveSelected){
        point p=hsp2.getCell(x,y);

        if(pvp.user2Move(p.x,p.y)){
            hsp2.update(pvp.getUserBoard());
            moveSelected=true;
        }

    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 399 && x < 501 && y > 249 && y < 351 && screen == menu ){
        screen = mode;
        hovering=false;
    }


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 9 && x < 51 && y > 9 && y < 51 && screen == menu ){
        screen = help;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 59 && x < 101 && y > 9 && y < 51 && screen == menu ){
        screen = info;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 834 && x < 886 && y > 14 && y < 46 && screen == help ){
        screen = menu;
        hovering=false;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 834 && x < 886 && y > 14 && y < 46 && screen == bye ){
        resetGame();
        hovering=false;
//        screen = menu;
    }


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 834 && x < 886 && y > 14 && y < 46 && screen == info ){
        screen = menu;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 299 && x < 601 && y > 124 && y < 176 && screen == mode ){
        placing=true;
        screen = setPlayerOne;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 299 && x < 601 && y > 424 && y < 476 && screen == mode ){

        screen = shipPosition;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 410 && x < 490 && y > 330 && y < 370 && screen == shipPosition && numOfShipsPlaced==5) {
        pvc.placePiecesDebug();
        screen = idleGame;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 410 && x < 490 && y > 330 && y < 370 && screen == setPlayerOne && numOfShipsPlaced==5) {

        screen = middle;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 410 && x < 490 && y > 330 && y < 370 && screen == setPlayerTwo && numOfShipsPlaced2==5) {

        screen = p2turn;
        placing =false;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 560 && x < 640 && y > 480 && y < 520 && screen == idleGame){
        screen = hitSelection;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 660 && x < 740 && y > 480 && y < 520 && screen == p1turn){
        if(p1MadeTurn){
            screen=middle;
            hovering=false;
        }

    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 660 && x < 740 && y > 480 && y < 520 && screen== p2turn){
        if(p2MadeTurn){
            screen=middle;
            hovering=false;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 560 && x < 640 && y > 480 && y < 520 && screen == p1turn && !p1MadeTurn){
        screen = p1hs;
        hovering=false;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 560 && x < 640 && y > 480 && y < 520 && screen == p2turn && !p2MadeTurn){
        screen = p2hs;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 760 && x < 840 && y > 280 && y < 320 && screen == hitSelection && moveSelected){
        screen = idleGame;

        while(!pvc.compMove()){
        }
        moveSelected=false;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 760 && x < 840 && y > 280 && y < 320 && screen == p1hs && moveSelected){
        screen = p1turn;
        p1MadeTurn=true;
        moveSelected=false;
        hovering=false;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 760 && x < 840 && y > 280 && y < 320 && screen == p2hs && moveSelected){
        screen = p2turn;
        p2MadeTurn=true;

        moveSelected=false;
        hovering=false;
    }





    // check if cursor is overlapping chip store bool
    // if it is store ship type
    // create variable isOverlappoingASHip?
    // if it is go in and
    // set status to whatever ship
    // select unselect

    // for carrier
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && (fleet.getCarrier().carrierShipTang.isOverlapping({x,y}) || user2fleet.getCarrier().carrierShipTang.isOverlapping({x,y}))
        && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getCarrierStatus() == unselected || user2fleet.getCarrierStatus() == unselected)){

        fleet.setCarrierStatus(selected);
        user2fleet.setCarrierStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && (fleet.getCarrier().carrierShipTang.isOverlapping({x,y}) || user2fleet.getCarrier().carrierShipTang.isOverlapping({x,y}))
              && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getCarrierStatus() == selected || user2fleet.getCarrierStatus() == selected)) {

        fleet.setCarrierStatus(unselected);
        user2fleet.setCarrierStatus(unselected);
        dragging=false;

        //get top or side pos


        if (screen == shipPosition) {
            for (vector<Tangle> row : pvc.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getCarrier().getVert()){
                        if (c.isOverlapping({x,y-60})) {
                            point p = c.getBoardCell();

                            if(pvc.getUserBoard().checkClear(p.x,p.y,5,2)){
                                pvc.placeShip(Carrier, p.x, p.y,2);
                                Ship n= fleet.getCarrier();
                                n.carrierShipTang.setDimensions(0,0);
                                fleet.setCarrier(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+60,y})) {
                            point p = c.getBoardCell();
                            if(pvc.getUserBoard().checkClear(p.x,p.y,5,0)){
                                pvc.placeShip(Carrier, p.x, p.y,0);
                                Ship n= fleet.getCarrier();
                                n.carrierShipTang.setDimensions(0,0);
                                fleet.setCarrier(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerOne) {
            for (vector<Tangle> row : pvp.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getCarrier().getVert()){
                        if (c.isOverlapping({x,y-60})) {
                            point p = c.getBoardCell();

                            if(pvp.getUserBoard().checkClear(p.x,p.y,5,2)){
                                pvp.placeShip(Carrier, p.x, p.y,2);
                                Ship n= fleet.getCarrier();
                                n.carrierShipTang.setDimensions(0,0);
                                fleet.setCarrier(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+60,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUserBoard().checkClear(p.x,p.y,5,0)){
                                pvp.placeShip(Carrier, p.x, p.y,0);
                                Ship n= fleet.getCarrier();
                                n.carrierShipTang.setDimensions(0,0);
                                fleet.setCarrier(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerTwo) {
            for (vector<Tangle> row : pvp.getUser2Board().cells) {
                for (Tangle c : row) {
                    if(user2fleet.getCarrier().getVert()){
                        if (c.isOverlapping({x,y-60})) {
                            point p = c.getBoardCell();

                            if(pvp.getUser2Board().checkClear(p.x,p.y,5,2)){
                                pvp.placePlayer2(Carrier, p.x, p.y,2);
                                Ship n= user2fleet.getCarrier();
                                n.carrierShipTang.setDimensions(0,0);
                                user2fleet.setCarrier(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+60,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUser2Board().checkClear(p.x,p.y,5,0)){
                                pvp.placePlayer2(Carrier, p.x, p.y,0);
                                Ship n= user2fleet.getCarrier();
                                n.carrierShipTang.setDimensions(0,0);
                                user2fleet.setCarrier(n);
                                numOfShipsPlaced2++;
                            }
                        }
                    }
                }
            }
        }

//        point p = g.getUserBoard().cells[5][5].getBoardCell();
//        g.placeShip(Carrier,p.x,p.y,0);
    }

    // do if else for battle
    if (button == GLUT_LEFT_BUTTON && dragging==false && state == GLUT_DOWN && (fleet.getBattle().battleShipTang.isOverlapping({x,y}) || user2fleet.getBattle().battleShipTang.isOverlapping({x,y}))
        && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getBattleStatus() == unselected || user2fleet.getBattleStatus() == unselected)){
        fleet.setBattleStatus(selected);
        user2fleet.setBattleStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && (fleet.getBattle().battleShipTang.isOverlapping({x,y}) || user2fleet.getBattle().battleShipTang.isOverlapping({x,y}))
              && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getBattleStatus() == selected || user2fleet.getBattleStatus() == selected)) {
        fleet.setBattleStatus(unselected);
        user2fleet.setBattleStatus(unselected);

        dragging=false;

        if (screen == shipPosition) {
            for (vector<Tangle> row : pvc.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getBattle().getVert()){
                        if (c.isOverlapping({x,y-45})) {
                            point p = c.getBoardCell();

                            if(pvc.getUserBoard().checkClear(p.x,p.y,4,2)){
                                pvc.placeShip(Battleship, p.x, p.y,2);
                                Ship n= fleet.getBattle();
                                n.battleShipTang.setDimensions(0,0);
                                fleet.setBattle(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+45,y})) {
                            point p = c.getBoardCell();
                            if(pvc.getUserBoard().checkClear(p.x,p.y,4,0)){
                                pvc.placeShip(Battleship, p.x, p.y,0);
                                Ship n= fleet.getBattle();
                                n.battleShipTang.setDimensions(0,0);
                                fleet.setBattle(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerOne) {
            for (vector<Tangle> row : pvp.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getBattle().getVert()){
                        if (c.isOverlapping({x,y-45})) {
                            point p = c.getBoardCell();

                            if(pvp.getUserBoard().checkClear(p.x,p.y,4,2)){
                                pvp.placeShip(Battleship, p.x, p.y,2);
                                Ship n= fleet.getBattle();
                                n.battleShipTang.setDimensions(0,0);
                                fleet.setBattle(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+45,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUserBoard().checkClear(p.x,p.y,4,0)){
                                pvp.placeShip(Battleship, p.x, p.y,0);
                                Ship n= fleet.getBattle();
                                n.battleShipTang.setDimensions(0,0);
                                fleet.setBattle(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        }  else if (screen == setPlayerTwo) {
            for (vector<Tangle> row : pvp.getUser2Board().cells) {
                for (Tangle c : row) {
                    if(user2fleet.getBattle().getVert()){
                        if (c.isOverlapping({x,y-45})) {
                            point p = c.getBoardCell();

                            if(pvp.getUser2Board().checkClear(p.x,p.y,4,2)){
                                pvp.placePlayer2(Battleship, p.x, p.y,2);
                                Ship n= user2fleet.getBattle();
                                n.battleShipTang.setDimensions(0,0);
                                user2fleet.setBattle(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+45,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUser2Board().checkClear(p.x,p.y,4,0)){
                                pvp.placePlayer2(Battleship, p.x, p.y,0);
                                Ship n= user2fleet.getBattle();
                                n.battleShipTang.setDimensions(0,0);
                                user2fleet.setBattle(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }
                }
            }
        }
    }



    // do if else for cruiser
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && (fleet.getCruiser().cruiserShipTang.isOverlapping({x,y}) || user2fleet.getCruiser().cruiserShipTang.isOverlapping({x,y}))
        && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getCruiserStatus() == unselected || user2fleet.getCruiserStatus() == unselected)){
        fleet.setCruiserStatus(selected);
        user2fleet.setCruiserStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && (fleet.getCruiser().cruiserShipTang.isOverlapping({x,y}) || user2fleet.getCruiser().cruiserShipTang.isOverlapping({x,y}))
              && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getCruiserStatus() == selected || user2fleet.getCruiserStatus() == selected)) {
        fleet.setCruiserStatus(unselected);
        user2fleet.setCruiserStatus(unselected);
        dragging=false;

        if (screen == shipPosition) {
            for (vector<Tangle> row : pvc.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getCruiser().getVert()){
                        if (c.isOverlapping({x,y-15})) {
                            point p = c.getBoardCell();

                            if(pvc.getUserBoard().checkClear(p.x,p.y,2,2)){
                                pvc.placeShip(Cruiser, p.x, p.y,2);
                                Ship n= fleet.getCruiser();
                                n.cruiserShipTang.setDimensions(0,0);
                                fleet.setCruiser(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+15,y})) {
                            point p = c.getBoardCell();
                            if(pvc.getUserBoard().checkClear(p.x,p.y,2,0)){
                                pvc.placeShip(Cruiser, p.x, p.y,0);
                                Ship n= fleet.getCruiser();
                                n.cruiserShipTang.setDimensions(0,0);
                                fleet.setCruiser(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerOne) {
            for (vector<Tangle> row : pvp.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getCruiser().getVert()){
                        if (c.isOverlapping({x,y-15})) {
                            point p = c.getBoardCell();

                            if(pvp.getUserBoard().checkClear(p.x,p.y,2,2)){
                                pvp.placeShip(Cruiser, p.x, p.y,2);
                                Ship n= fleet.getCruiser();
                                n.cruiserShipTang.setDimensions(0,0);
                                fleet.setCruiser(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+15,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUserBoard().checkClear(p.x,p.y,2,0)){
                                pvp.placeShip(Cruiser, p.x, p.y,0);
                                Ship n= fleet.getCruiser();
                                n.cruiserShipTang.setDimensions(0,0);
                                fleet.setCruiser(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        }  else if (screen == setPlayerTwo) {
            for (vector<Tangle> row : pvp.getUser2Board().cells) {
                for (Tangle c : row) {
                    if(user2fleet.getCruiser().getVert()){
                        if (c.isOverlapping({x,y-15})) {
                            point p = c.getBoardCell();

                            if(pvp.getUser2Board().checkClear(p.x,p.y,2,2)){
                                pvp.placePlayer2(Cruiser, p.x, p.y,2);
                                Ship n= user2fleet.getCruiser();
                                n.cruiserShipTang.setDimensions(0,0);
                                user2fleet.setCruiser(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+15,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUser2Board().checkClear(p.x,p.y,2,0)){
                                pvp.placePlayer2(Cruiser, p.x, p.y,0);
                                Ship n= user2fleet.getCruiser();
                                n.cruiserShipTang.setDimensions(0,0);
                                user2fleet.setCruiser(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }
                }
            }
        }
    }

    // do if else for sub
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && (fleet.getSub().subShipTang.isOverlapping({x,y}) || user2fleet.getSub().subShipTang.isOverlapping({x,y}))
        && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getSubStatus() == unselected || user2fleet.getSubStatus() == unselected)){
        fleet.setSubStatus(selected);
        user2fleet.setSubStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && (fleet.getSub().subShipTang.isOverlapping({x,y}) || user2fleet.getSub().subShipTang.isOverlapping({x,y}))
              && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getSubStatus() == selected || user2fleet.getSubStatus() == selected)) {
        fleet.setSubStatus(unselected);
        user2fleet.setSubStatus(unselected);
        dragging=false;

        if (screen == shipPosition) {
            for (vector<Tangle> row : pvc.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getSub().getVert()){
                        if (c.isOverlapping({x,y-30})) {
                            point p = c.getBoardCell();

                            if(pvc.getUserBoard().checkClear(p.x,p.y,3,2)){
                                pvc.placeShip(Sub, p.x, p.y,2);
                                Ship n= fleet.getSub();
                                n.subShipTang.setDimensions(0,0);
                                fleet.setSub(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+30,y})) {
                            point p = c.getBoardCell();
                            if(pvc.getUserBoard().checkClear(p.x,p.y,3,0)){
                                pvc.placeShip(Sub, p.x, p.y,0);
                                Ship n= fleet.getSub();
                                n.subShipTang.setDimensions(0,0);
                                fleet.setSub(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerOne) {
            for (vector<Tangle> row : pvp.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getSub().getVert()){
                        if (c.isOverlapping({x,y-30})) {
                            point p = c.getBoardCell();

                            if(pvp.getUserBoard().checkClear(p.x,p.y,3,2)){
                                pvp.placeShip(Sub, p.x, p.y,2);
                                Ship n= fleet.getSub();
                                n.subShipTang.setDimensions(0,0);
                                fleet.setSub(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+30,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUserBoard().checkClear(p.x,p.y,3,0)){
                                pvp.placeShip(Sub, p.x, p.y,0);
                                Ship n= fleet.getSub();
                                n.subShipTang.setDimensions(0,0);
                                fleet.setSub(n);
                                numOfShipsPlaced++;
                            }
                        }
                    }
                }
            }
        }  else if (screen == setPlayerTwo) {
            for (vector<Tangle> row : pvp.getUser2Board().cells) {
                for (Tangle c : row) {
                    if(user2fleet.getSub().getVert()){
                        if (c.isOverlapping({x,y-30})) {
                            point p = c.getBoardCell();

                            if(pvp.getUser2Board().checkClear(p.x,p.y,3,2)){
                                pvp.placePlayer2(Sub, p.x, p.y,2);
                                Ship n= user2fleet.getSub();
                                n.subShipTang.setDimensions(0,0);
                                user2fleet.setSub(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+30,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUser2Board().checkClear(p.x,p.y,3,0)){
                                pvp.placePlayer2(Sub, p.x, p.y,0);
                                Ship n= user2fleet.getSub();
                                n.subShipTang.setDimensions(0,0);
                                user2fleet.setSub(n);
                                numOfShipsPlaced2++;
                            }
                        }
                    }
                }
            }
        }
    }

    // do if else for destroyer
    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && (fleet.getDestroyer().destroyerShipTang.isOverlapping({x,y}) || user2fleet.getDestroyer().destroyerShipTang.isOverlapping({x,y}))
        && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getDestroyerStatus() == unselected || user2fleet.getDestroyerStatus() == unselected)){
        fleet.setDestroyerStatus(selected);
        user2fleet.setDestroyerStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && (fleet.getDestroyer().destroyerShipTang.isOverlapping({x,y}) || user2fleet.getDestroyer().destroyerShipTang.isOverlapping({x,y}))
              && (screen == shipPosition ||screen == setPlayerOne || screen == setPlayerTwo) && (fleet.getDestroyerStatus() == selected || user2fleet.getDestroyerStatus() == selected)) {
        fleet.setDestroyerStatus(unselected);
        user2fleet.setDestroyerStatus(unselected);
        dragging=false;
        if (screen == shipPosition) {
            for (vector<Tangle> row : pvc.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getDestroyer().getVert()){
                        if (c.isOverlapping({x,y-30})) {
                            point p = c.getBoardCell();

                            if(pvc.getUserBoard().checkClear(p.x,p.y,3,2)){
                                pvc.placeShip(Destroyer, p.x, p.y,2);
                                Ship n= fleet.getDestroyer();
                                n.destroyerShipTang.setDimensions(0,0);
                                fleet.setDestroyer(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+30,y})) {
                            point p = c.getBoardCell();
                            if(pvc.getUserBoard().checkClear(p.x,p.y,3,0)){
                                pvc.placeShip(Destroyer, p.x, p.y,0);
                                Ship n= fleet.getDestroyer();
                                n.destroyerShipTang.setDimensions(0,0);
                                fleet.setDestroyer(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerOne){
            for (vector<Tangle> row : pvp.getUserBoard().cells) {
                for (Tangle c : row) {
                    if(fleet.getDestroyer().getVert()){
                        if (c.isOverlapping({x,y-30})) {
                            point p = c.getBoardCell();

                            if(pvp.getUserBoard().checkClear(p.x,p.y,3,2)){
                                pvp.placeShip(Destroyer, p.x, p.y,2);
                                Ship n= fleet.getDestroyer();
                                n.destroyerShipTang.setDimensions(0,0);
                                fleet.setDestroyer(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+30,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUserBoard().checkClear(p.x,p.y,3,0)){
                                pvp.placeShip(Destroyer, p.x, p.y,0);
                                Ship n= fleet.getDestroyer();
                                n.destroyerShipTang.setDimensions(0,0);
                                fleet.setDestroyer(n);
                                numOfShipsPlaced++;
                            }

                        }
                    }
                }
            }
        } else if (screen == setPlayerTwo){
            for (vector<Tangle> row : pvp.getUser2Board().cells) {
                for (Tangle c : row) {
                    if(user2fleet.getDestroyer().getVert()){
                        if (c.isOverlapping({x,y-30})) {
                            point p = c.getBoardCell();

                            if(pvp.getUser2Board().checkClear(p.x,p.y,3,2)){
                                pvp.placePlayer2(Destroyer, p.x, p.y,2);
                                Ship n= user2fleet.getDestroyer();
                                n.destroyerShipTang.setDimensions(0,0);
                                user2fleet.setDestroyer(n);
                                numOfShipsPlaced2++;
                            }

                        }
                    }else{
                        if (c.isOverlapping({x+30,y})) {
                            point p = c.getBoardCell();
                            if(pvp.getUser2Board().checkClear(p.x,p.y,3,0)){
                                pvp.placePlayer2(Destroyer, p.x, p.y,0);
                                Ship n= user2fleet.getDestroyer();
                                n.destroyerShipTang.setDimensions(0,0);
                                user2fleet.setDestroyer(n);
                                numOfShipsPlaced2++;
                            }
                        }
                    }
                }
            }
        }
    }


    glutPostRedisplay();

}

void cursor(int x, int y) {


    if (fleet.getCarrierStatus() == selected && (screen == shipPosition || screen == setPlayerOne)) {
        fleet.dragCarrier(x, y);
    }
    if (user2fleet.getCarrierStatus() == selected && screen == setPlayerTwo) {
        user2fleet.dragCarrier(x, y);
    }

    if (fleet.getBattleStatus() == selected && (screen == shipPosition || screen == setPlayerOne)) {
        fleet.dragBattle(x, y);
    }
    if (user2fleet.getBattleStatus() == selected && screen == setPlayerTwo) {
        user2fleet.dragBattle(x, y);
    }

    if (fleet.getCruiserStatus() == selected && (screen == shipPosition || screen == setPlayerOne)) {
        fleet.dragCruiser(x, y);
    }
    if (user2fleet.getCruiserStatus() == selected && screen == setPlayerTwo) {
        user2fleet.dragCruiser(x, y);
    }

    if (fleet.getSubStatus() == selected && (screen == shipPosition || screen == setPlayerOne)) {
        fleet.dragSub(x, y);
    }
    if (user2fleet.getSubStatus() == selected && screen == setPlayerTwo) {
        user2fleet.dragSub(x, y);
    }

    if (fleet.getDestroyerStatus() == selected && (screen == shipPosition || screen == setPlayerOne)) {
        fleet.dragDestroyer(x, y);
    }
    if (user2fleet.getDestroyerStatus() == selected && screen == setPlayerTwo) {
        user2fleet.dragDestroyer(x, y);
    }


    //HOVER FUNCTIONS
    switch (screen) {
        case menu:

            if (x > 399 && x < 501 && y > 249 && y < 351) {
                startButton.setBorderColor(0, .5, .5);
                hovering = true;
            } else if (x > 9 && x < 51 && y > 9 && y < 51) {
                helpButton.setBorderColor(0, .5, .5);
                hovering = true;
            } else if (x > 59 && x < 101 && y > 9 && y < 51) {
                infoButton.setBorderColor(0, .5, .5);
                hovering = true;

            } else {
                hovering = false;
            }


            break;
        case help:
            if (x > 834 && x < 886 && y > 14 && y < 46 && screen == help) {
                exitButton.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }
            break;
        case info:
            if (x > 834 && x < 886 && y > 14 && y < 46 && screen == info) {
                helpButton.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }
            break;
        case mode:
            if (x > 299 && x < 601 && y > 124 && y < 176) {
                hhButton.setBorderColor(0, .5, .5);
                hovering = true;
            } else if (x > 299 && x < 601 && y > 424 && y < 476) {
                hcButton.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }
            break;
        case hitSelection:
            if (x > 760 && x < 840 && y > 280 && y < 320) {
                nukeSelect.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }


            break;
        case p1hs:
            if (x > 760 && x < 840 && y > 280 && y < 320) {
                nukeSelect.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }

            break;
        case p2hs:
            if (x > 760 && x < 840 && y > 280 && y < 320) {
                nukeSelect.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }

            break;
        case setPlayerOne:
            if (x > 410 && x < 490 && y > 330 && y < 370) {
                finishPlacing.setBorderColor(0, .5, .5);
                hovering = true;

            } else {
                hovering = false;
            }


            break;
        case setPlayerTwo:
            if (x > 410 && x < 490 && y > 330 && y < 370) {
                finishPlacing.setBorderColor(0, .5, .5);
                hovering = true;

            } else {
                hovering = false;
            }
            break;
        case shipPosition:

            if (x > 410 && x < 490 && y > 330 && y < 370) {
                finishPlacing.setBorderColor(0, .5, .5);
                hovering = true;

            } else {
                hovering = false;
            }
            break;

        case bye:
            if (x > 834 && x < 886 && y > 14 && y < 46) {
                exitButton3.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }

            break;
        case idleGame:
            if (x > 560 && x < 640 && y > 480 && y < 520) {
                nuke.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }
            break;
        case p1turn: {
            if (x > 560 && x < 640 && y > 480 && y < 520) {
                nuke.setBorderColor(0, .5, .5);
                hovering = true;
            } else if (x > 660 && x < 740 && y > 480 && y < 520) {
                nextTurn.setBorderColor(0, .5, .5);
                hovering = true;
            } else {
                hovering = false;
            }
            break;
        }
        case p2turn: {
            if (x > 560 && x < 640 && y > 480 && y < 520) {
                nuke.setBorderColor(0, .5, .5);
                hovering = true;
            } else if (x > 660 && x < 740 && y > 480 && y < 520) {
                nextTurn.setBorderColor(0, .5, .5);
                hovering = true;

            } else {
                hovering = false;
            }

        }

            glutPostRedisplay();

    }
}
void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}



/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {



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

