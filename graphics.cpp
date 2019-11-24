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
#include <sstream>


using namespace std;
GLdouble width, height;
int wd;
Board board;


enum gameState{menu,game,hitSelection,bye,help};

gameState screen;


void init() {
    screen= menu;
    width = 500;
    height = 500;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */

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
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_QUADS);
            glVertex2d(0.0,0.0);
            glVertex2d(100.0,0.0);
            glVertex2d(100.0,100.0);
            glVertex2d(0.0,100.0);
            glEnd();
            glColor3f(0.0,1.0,0.0);
            glBegin(GL_QUADS);
            glVertex2d(10.0,10.0);
            glVertex2d(90.0,10.0);
            glVertex2d(90.0,90.0);
            glVertex2d(10.0,90.0);
            glEnd();
            break;
        case game:
            break;
        case hitSelection:
            break;
        case bye:
            break;
        case help:
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

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

//    while(state == GLUT_DOWN){
//        drag(getShip(x,y),x,y);
//        glutPostRedisplay();
//    }



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
    glutInitWindowPosition(-200,-100);

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

