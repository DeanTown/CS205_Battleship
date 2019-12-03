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
Tangle exitButton;
Tangle infoButton;
Tangle iMenu;

Fleet fleet;

enum gameState{menu,mode,hhGame,shipPosition,hitSelection,bye,help,info};

gameState screen;
bool dragging;


void init() {
    dragging=false;

    screen= menu;
    width = 900;
    height = 600;
    fleet.setCarrierStatus(unselected);
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
//    fleet.getCarrier().setCenterY(470);
//    fleet.getCarrier().setCenterY(140);
    fleet.getCarrier().drawShip_car();
//    battle.drawShip(140,470);
//    cruiser.drawShip(200,470);
//    sub.drawShip(260,470);
//    destroyer.drawShip(320,470);
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
        case hitSelection:
            hs.draw(width, height);
            // get cell clicked
            // update hitSelection board
            hs.update(g.getComputerBoard());
            break;
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
//
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 121 && x < 221 && y > 249 && y < 351 && screen == mode ){
//        screen = hhGame;
//    }
//
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 281 && x < 381 && y > 249 && y < 351 && screen == mode ){
        screen = shipPosition;
    }


    if (button == GLUT_LEFT_BUTTON && dragging==false &&state == GLUT_DOWN && fleet.getCarrier().carrierShip.isOverlapping({x,y})
        && screen == shipPosition && fleet.getCarrierStatus() == unselected){
        cout << "DRAGGABLE" << endl;
        fleet.setCarrierStatus(selected);
        wait((int*)1);
        dragging=true;
    } else if(button == GLUT_LEFT_BUTTON && dragging==true && state == GLUT_DOWN && fleet.getCarrier().carrierShip.isOverlapping({x,y})
        && screen == shipPosition && fleet.getCarrierStatus() == selected) {
        cout << "UNSELECTED" << endl;
        fleet.setCarrierStatus(unselected);
        dragging=false;
        point p = g.getUserBoard().cells[5][5].getBoardCell();
        g.placeShip(Carrier,p.x,p.y,0);
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
//    cout << x << endl;
//    cout << y << endl;
    if (fleet.getCarrierStatus() == selected) {
        fleet.drag(x, y);
        glutPostRedisplay();
    }


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

