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
Cell cell;
Ship ships;
bool mouseInput = false;


void init() {
    width = 500;
    height = 600;
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
    board.drawBoard();
    ships.createCarrier();
    ships.createBattleship();
//    ships.createShip(100,450,4,1);
//    ships.createShip(170,450,5,2);
//    ships.createShip(240,450,3,3);
//    ships.createShip(310,450,3,4);
//    ships.createShip(380,450,2,5);
    if (mouseInput) {
        board.updateBoard();
//        cout << ships.getCenterX() << "," << ships.getCenterY() << endl;
//        mouseInput = false;
    }

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
    switch (button) {
        default:
            break;
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {

                if (x >= board.getLeftX() && x <= board.getRightX() && y >= board.getTopY() && y <= board.getBottomY()) {
                    cout << board.cellNum(x,y) << endl;
                    cellNumber = board.cellNum(x,y);
                    mouseInput = board.updateStat(cellNumber - 1 );
                } else {
                    cout << x << "," << y << endl;
                }
            }
            break;
        case GLUT_RIGHT_BUTTON:
            break;
    }
}
//void onMouse(int button, int state, int x, int y) {
//    if(state != GLUT_DOWN)
//        return;
//
//    width = glutGet(GLUT_WINDOW_WIDTH);
//    height = glutGet(GLUT_WINDOW_HEIGHT);
//
//    GLbyte color[4];
//    GLfloat depth;
//    GLuint index;
//
//    glReadPixels(x, height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
//    glReadPixels(x, height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
//    glReadPixels(x, height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
//
//    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
//           x, y, color[0], color[1], color[2], color[3], depth, index);
//}
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

