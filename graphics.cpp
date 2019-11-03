#include "graphics.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <zconf.h>
#include "algorithm"
#include "cstdlib"
#include "ctime"
#include "Cell.h"
#include "Board.h"
//#include "Player.h"
#include "Ship.h"
//#include "Game.h"


using namespace std;
GLdouble width, height;
int wd, cellNumber;
Board board;
Cell* c = new Cell;
Board* b = new Board;
bool mouseInput = false;

// display at start
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    c->draw(c);
    glFlush();

}

// drag function
void drag (int x, int y)
{
    // int x and y of mouse converts to screen coordinates
    // returns the point as mousePt
    point mousePt = c->mouse(x,y);
    //create pointer to window point coordinates
    point* mouse = &mousePt;

    // if the mouse is within the square
    if (mouse->x > c->pts[0].x && mouse->y > c->pts[0].y)
    {
        if (mouse->x < c->pts[2].x && mouse->y < c->pts[2].y)
        {
            // then drag by chaning square coordinates relative to mouse
            c->drag(c,mouse);
            glutPostRedisplay();
        }
    }
}


void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

//void init() {
//    width = 500;
//    height = 500;
//}
//
///* Initialize OpenGL Graphics */
//void initGL() {
//    // Set "clearing" or background color
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black and opaque
//}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */

//void display(){
//    glViewport(0, 0, width, height);
//    // do an orthographic parallel projection with the coordinate
//    // system set to first quadrant, limited by screen/window size
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
//    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    board.drawBoard();
//    if (mouseInput) {
//        board.updateBoard();
////        mouseInput = false;
//    }
//
//    glFlush();  // Render now
//}
//
//// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
//void kbd(unsigned char key, int x, int y)
//{
//    //escape key exits window
//    if (key == 27) {
//
//        glutDestroyWindow(wd);
//        exit(0);
//    }
//
//    glutPostRedisplay();
//}
//
//void kbdS(int key, int x, int y) {
//    switch(key) {
//        case GLUT_KEY_DOWN:
//
//            break;
//
//        case GLUT_KEY_LEFT:
//
//            break;
//
//        case GLUT_KEY_RIGHT:
//
//            break;
//
//        case GLUT_KEY_UP:
//
//            break;
//    }
//
//    glutPostRedisplay();
//}
//
//void cursor(int x, int y) {
//
//    glutPostRedisplay();
//}
//
//// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
//// state will be GLUT_UP or GLUT_DOWN
//void mouse(int button, int state, int x, int y) {
//    switch (button) {
//        default:
//            break;
//        case GLUT_LEFT_BUTTON:
//            if (state == GLUT_DOWN) {
//                if (x >= board.getLeftX() && x <= board.getRightX() && y >= board.getTopY() && y <= board.getBottomY()) {
//                    cout << board.cellNum(x,y) << endl;
//                    if (board.cellNum(x,y) != 0) {
//                        cellNumber = board.cellNum(x,y);
//                        mouseInput = board.updateStat(cellNumber - 1 );
//                    }
//                }
//            }
//            break;
//        case GLUT_RIGHT_BUTTON:
//            break;
//    }
//
//}
//

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

int main(int iArgc, char** cppArgv) {

    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Move Box");


    glutMotionFunc(drag);

    Initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

/* Main function: GLUT runs as a console application starting at main()  */
//int main(int argc, char** argv) {
//
//    init();
//
//    // Initialize GLUT
//    glutInit(&argc, argv);
//
//    glutInitDisplayMode(GLUT_RGBA);
//
//    glutInitWindowSize((int)width, (int)height);
//
//    // Position the window's initial top-left corner
//    /* create the window and store the handle to it */
//    glutInitWindowPosition(-200,-100);
//
//    wd = glutCreateWindow("BATTLESHIP" /* title */ );
//
//    // Register callback handler for window re-paint event
//    glutDisplayFunc(display);
//
//    // Our own OpenGL initialization
//    initGL();
//
//    // register keyboard press event processing function
//    // works for numbers, letters, spacebar, etc.
//
//    glutKeyboardFunc(kbd);
//
//    // register special event: function keys, arrows, etc.
//    glutSpecialFunc(kbdS);
//
//    // handles mouse movement
//    glutPassiveMotionFunc(cursor);
//
//    // handles mouse click
//    glutMouseFunc(mouse);
//
////    glutMouseFunc(onMouseClick);
//
//    // handles timer
//    glutTimerFunc(0, timer, 0);
//
//    // Enter the event-processing loop
//    glutMainLoop();
//
//    return 0;
//}
