#include "graphics.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <zconf.h>
#include "algorithm"
#include "cstdlib"
#include "ctime"
#include "Cell.h"
#include "UCarrier.h"
#include "UBattleship.h"
#include "UDestroyer.h"
#include "USub.h"
#include "UCruiser.h"
#include "Board.h"

enum screen {Start,playerOneSet,game,finished};

using namespace std;
GLdouble width, height;
GLint wd, cellNumber,ocNumber;
GLint uboardL,uboardR,uboardT,uboardB,
        gUserBoardL,gUserBoardR,gUserBoardT,gUserBoardB;
GLint hitCellX, hitCellY, notHitX, notHitY;
screen curr = Start;
Cell cells;
Board userBoard;
Board gameUserBoard;
UCarrier* p1c = new UCarrier;
UBattleship* p1b = new UBattleship;
UDestroyer* p1d = new UDestroyer;
USub* p1s = new USub;
UCruiser* p1r = new UCruiser;
bool mouseInput = false;
bool doneOnHover = false;
bool gameOver = false;

vector<int> uOccupiedCells;
vector<int> occupiedCellsTemp;
vector<int> gHitCells;
vector<int> gNotHit;

bool checkCommon(vector<int> &v1, vector<int> &v2) {
    bool tf = false;
    int v1S = v1.size();
    int v2S = v2.size();
    for (int i = 0; i < v1S; ++i) {
        for (int j = 0; j < v2S; ++j) {
            if (v1[i] == v2[j])
                tf = true;
        }
    }
    return tf;
}

bool checkEquality(vector<int> &v1, vector<int> &v2) {
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    return v1 == v2;
}

void init() {
    width = 700;
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

    switch (curr) {
        default:
            break;
        case Start:
            cells.drawWelcom("Battleship");
            cells.drawPVC("fight a computer");
            cells.drawPVP("fight a friend");
            break;
        case playerOneSet:
            userBoard.drawBoard();
            uboardL = userBoard.getLeftX();
            uboardR = userBoard.getRightX();
            uboardT = userBoard.getTopY();
            uboardB = userBoard.getBottomY();
            p1c->draw();
            p1b->draw();
            p1d->draw();
            p1s->draw();
            p1r->draw();
            break;
        case game:
            gameUserBoard.drawBoard();
            gUserBoardL = gameUserBoard.getLeftX();
            gUserBoardR = gameUserBoard.getRightX();
            gUserBoardT = gameUserBoard.getTopY();
            gUserBoardB = gameUserBoard.getBottomY();
            p1c->draw();
            p1b->draw();
            p1d->draw();
            p1s->draw();
            p1r->draw();
            for (int num : gHitCells) {
                hitCellX = gameUserBoard.getCellX(num - 1);
                hitCellY = gameUserBoard.getCellY(num - 1);
                cells.drawHit(hitCellX,hitCellY);
            }
            for (int num : gNotHit) {
                notHitX = gameUserBoard.getCellX(num - 1);
                notHitY = gameUserBoard.getCellY(num - 1);
                cells.drawNotHit(notHitX,notHitY);
            }
            break;
        case finished:
            cells.drawWelcom("end of Game");
            break;
    }

    if (p1c->getFleetStat() == placedHo || p1b->getFleetStat() == placedHo || p1d->getFleetStat() == placedHo || p1s->getFleetStat() == placedHo
        || p1r->getFleetStat() == placedHo || p1c->getFleetStat() == placedVe || p1b->getFleetStat() == placedVe || p1d->getFleetStat() == placedVe
        || p1s->getFleetStat() == placedVe || p1r->getFleetStat() == placedVe) {
        cells.drawButton("change dirction");
        cells.drawDone("done");
    }

    if (p1c->getThirdStat() == out) {
        p1c->outBoard("carrier is out of board");
    }
    if (p1c->getForthStat() == working) {
        p1c->focus("working on placing carrier");
    }
    if (p1c->getFifthStat() == overlapping) {
        p1c->overlap("carrier get overlapped");
    }
    if (p1b->getThirdStat() == out) {
        p1b->outBoard("battleship is out of board");
    }
    if (p1b->getForthStat() == working) {
        p1b->focus("working on placing battleship");
    }
    if (p1b->getFifthStat() == overlapping) {
        p1b->overlap("battleship get overlapped");
    }
    if (p1d->getThirdStat() == out) {
        p1d->outBoard("destroyer is out of board");
    }
    if (p1d->getForthStat() == working) {
        p1d->focus("working on placing destroyer");
    }
    if (p1d->getFifthStat() == overlapping) {
        p1d->overlap("destroyer get overlapped");
    }
    if (p1s->getThirdStat() == out) {
        p1s->outBoard("sub is out of board");
    }
    if (p1s->getForthStat() == working) {
        p1s->focus("working on placing sub");
    }
    if (p1s->getFifthStat() == overlapping) {
        p1s->overlap("sub get overlapped");
    }
    if (p1r->getThirdStat() == out) {
        p1r->outBoard("cruiser is out of board");
    }
    if (p1r->getForthStat() == working) {
        p1r->focus("working on placing cruiser");
    }
    if (p1r->getFifthStat() == overlapping) {
        p1r->overlap("cruiser get overlapped");
    }

    if (doneOnHover) {
        cells.hoverDone("once click, ship can't be moving again");
    }

    if (p1c->getFleetStat() == ready && p1b->getFleetStat() == ready && p1d->getFleetStat() == ready
        && p1s->getFleetStat() == ready && p1r->getFleetStat() == ready) {
        curr = game;
    }

    if (gameOver) {
        curr = finished;
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
    // when fleet state is selected, it can be moved
    if (p1c->getFleetStat() == selected && curr == playerOneSet) {
        p1c->drag(p1c,x,y);
        glutPostRedisplay();
    }
    if (p1b->getFleetStat() == selected && curr == playerOneSet) {
        p1b->drag(p1b,x,y);
        glutPostRedisplay();
    }
    if (p1d->getFleetStat() == selected && curr == playerOneSet) {
        p1d->drag(p1d,x,y);
        glutPostRedisplay();
    }
    if (p1s->getFleetStat() == selected && curr == playerOneSet) {
        p1s->drag(p1s,x,y);
        glutPostRedisplay();
    }
    if (p1r->getFleetStat() == selected && curr == playerOneSet) {
        p1r->drag(p1r,x,y);
        glutPostRedisplay();
    }

    doneOnHover = cells.inDone(x, y) && (p1c->getFleetStat() == placedHo || p1c->getFleetStat() == placedVe
                                         || p1b->getFleetStat() == placedHo || p1b->getFleetStat() == placedVe || p1d->getFleetStat() == placedHo
                                         || p1d->getFleetStat() == placedVe || p1s->getFleetStat() == placedHo || p1s->getFleetStat() == placedVe
                                         || p1r->getFleetStat() == placedVe || p1r->getFleetStat() == placedHo);
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    switch (button) {
        default:
            break;
        case GLUT_LEFT_BUTTON:
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && cells.inPVC(x,y) && curr == Start) {
                curr = playerOneSet;
            }
            // -------------------------------------------------------------------------------------------------------------

            // player one set ships-----------------------------------------------------------------------------------------
            // check if the mouse clicked on board--------------------------------------------------------------------------
            if (state == GLUT_DOWN && x >= userBoard.getLeftX() && x <= userBoard.getRightX() && y >= userBoard.getTopY() &&
                y <= userBoard.getBottomY() ) {
                cellNumber = userBoard.cellNum(x,y);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user carrier
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && p1c->getFleetStat() == moveable && curr == playerOneSet) {
                if (x >= p1c->getLeftX() && x <= p1c->getRightX() && y >= p1c->getTopY() && y <= p1c->getBottomY()) {
                    p1c->setFleetStat(selected);
                    p1c->setThirdStat(noWord);
                    p1c->setForthStat(working);
                    p1c->setFifthStat(noWord);
                    if (p1b->getFleetStat() != ready)
                        p1b->setFleetStat(No);
                    if (p1d->getFleetStat() != ready)
                        p1d->setFleetStat(No);
                    if (p1s->getFleetStat() != ready)
                        p1s->setFleetStat(No);
                    if (p1r->getFleetStat() != ready)
                        p1r->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && p1c->getFleetStat() == selected ) {
                occupiedCellsTemp.clear();
                if (p1c->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1c->setCenterX(userBoard.getCellX(cellNumber - 1));
                    p1c->setCenterY(userBoard.getCellY(cellNumber - 1));
                    if (p1c->getWidth() == 30 && p1c->getHeight() == 149) {
                        p1c->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(p1c->getCenterX(),p1c->getCenterY());
                        for (int i = ocNumber - 20; i <= ocNumber + 20; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1c->setCenterX(100);
                            p1c->setCenterY(500);
                            p1c->setFleetStat(moveable);
                            p1c->setFifthStat(overlapping);
                        }
                    }
                    else {
                        p1c->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(p1c->getCenterX(),p1c->getCenterY());
                        for (int i = ocNumber - 2; i <= ocNumber + 2; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1c->setCenterX(100);
                            p1c->setCenterY(500);
                            p1c->setFleetStat(moveable);
                            p1c->setFifthStat(overlapping);
                        }
                    }
                    p1c->setAdditionStat(placed);
                } else {
                    p1c->setCenterX(100);
                    p1c->setCenterY(500);
                    p1c->setFleetStat(moveable);
                    p1c->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1c->getFleetStat() == placedHo ) {
                occupiedCellsTemp.clear();
                p1c->setWidth(149);
                p1c->setHeight(30);
                p1c->setFleetStat(placedVe);
                p1c->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1c->getCenterX(),p1c->getCenterY());
                for (int i = ocNumber - 2; i <= ocNumber + 2; i += 1) {
                    occupiedCellsTemp.push_back(i);
                }
                if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1c->setCenterX(100);
                    p1c->setCenterY(500);
                    p1c->setFleetStat(moveable);
                    p1c->setFifthStat(overlapping);
                } else if (!p1c->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1c->setWidth(30);
                    p1c->setHeight(149);
                    p1c->setCenterX(100);
                    p1c->setCenterY(500);
                    p1c->setFleetStat(moveable);
                    p1c->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1c->getFleetStat() == placedVe ) {
                occupiedCellsTemp.clear();
                p1c->setWidth(30);
                p1c->setHeight(149);
                p1c->setFleetStat(placedHo);
                p1c->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1c->getCenterX(),p1c->getCenterY());
                for (int i = ocNumber - 20; i <= ocNumber + 20; i += 10) {
                    occupiedCellsTemp.push_back(i);
                }
                if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1c->setCenterX(100);
                    p1c->setCenterY(500);
                    p1c->setFleetStat(moveable);
                    p1c->setFifthStat(overlapping);
                } else if (!p1c->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1c->setWidth(30);
                    p1c->setHeight(149);
                    p1c->setCenterX(100);
                    p1c->setCenterY(500);
                    p1c->setFleetStat(moveable);
                    p1c->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (p1c->getFleetStat() == placedHo
                                                                   || p1c->getFleetStat() == placedVe) ) {
                for (int num : occupiedCellsTemp) {
                    uOccupiedCells.push_back(num);
                }
                p1c->setFleetStat(ready);
                p1c->setAdditionStat(addNull);
                p1c->setForthStat(noWord);
                doneOnHover = false;
                if (p1b->getFleetStat() == No)
                    p1b->setFleetStat(moveable);
                if (p1d->getFleetStat() == No)
                    p1d->setFleetStat(moveable);
                if (p1s->getFleetStat() == No)
                    p1s->setFleetStat(moveable);
                if (p1r->getFleetStat() == No)
                    p1r->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && p1c->getAdditionStat() == placed ) {
                p1c->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user battleship
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && p1b->getFleetStat() == moveable && curr == playerOneSet) {
                if (x >= p1b->getLeftX() && x <= p1b->getRightX() && y >= p1b->getTopY() && y <= p1b->getBottomY()) {
                    p1b->setFleetStat(selected);
                    p1b->setThirdStat(noWord);
                    p1b->setForthStat(working);
                    p1b->setFifthStat(noWord);
                    if (p1c->getFleetStat() != ready)
                        p1c->setFleetStat(No);
                    if (p1d->getFleetStat() != ready)
                        p1d->setFleetStat(No);
                    if (p1s->getFleetStat() != ready)
                        p1s->setFleetStat(No);
                    if (p1r->getFleetStat() != ready)
                        p1r->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && p1b->getFleetStat() == selected) {
                occupiedCellsTemp.clear();
                if (p1b->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    if (p1b->getWidth() == 30 && p1b->getHeight() == 119) {
                        p1b->setCenterX(userBoard.getCellX(cellNumber - 1));
                        p1b->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                        p1b->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(p1b->getCenterX(),p1b->getCenterY());
                        for (int i = ocNumber - 20; i <= ocNumber + 10; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1b->setCenterX(160);
                            p1b->setCenterY(500);
                            p1b->setFleetStat(moveable);
                            p1b->setFifthStat(overlapping);
                        }
                    }
                    else {
                        p1b->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                        p1b->setCenterY(userBoard.getCellY(cellNumber));
                        p1b->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(p1b->getCenterX(),p1b->getCenterY());
                        for (int i = ocNumber - 2; i <= ocNumber + 1; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1b->setCenterX(160);
                            p1b->setCenterY(500);
                            p1b->setFleetStat(moveable);
                            p1b->setFifthStat(overlapping);
                        }
                    }
                    p1b->setAdditionStat(placed);
                    p1b->setThirdStat(noWord);
                } else {
                    p1b->setCenterX(160);
                    p1b->setCenterY(500);
                    p1b->setFleetStat(moveable);
                    p1b->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1b->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                p1b->setWidth(119);
                p1b->setHeight(30);
                p1b->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                p1b->setCenterY(userBoard.getCellY(cellNumber));
                p1b->setFleetStat(placedVe);
                p1b->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1b->getCenterX(),p1b->getCenterY());
                for (int i = ocNumber - 2; i <= ocNumber + 1; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1b->setCenterX(160);
                    p1b->setCenterY(500);
                    p1b->setFleetStat(moveable);
                    p1b->setFifthStat(overlapping);
                } else if (!p1b->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1b->setWidth(30);
                    p1b->setHeight(119);
                    p1b->setCenterX(160);
                    p1b->setCenterY(500);
                    p1b->setFleetStat(moveable);
                    p1b->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1b->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                p1b->setWidth(30);
                p1b->setHeight(119);
                p1b->setCenterX(userBoard.getCellX(cellNumber - 1));
                p1b->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                p1b->setFleetStat(placedHo);
                p1b->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1b->getCenterX(),p1b->getCenterY());
                for (int i = ocNumber - 20; i <= ocNumber + 10; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1b->setCenterX(160);
                    p1b->setCenterY(500);
                    p1b->setFleetStat(moveable);
                    p1b->setFifthStat(overlapping);
                } else if (!p1b->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1b->setWidth(30);
                    p1b->setHeight(119);
                    p1b->setCenterX(160);
                    p1b->setCenterY(500);
                    p1b->setFleetStat(moveable);
                    p1b->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (p1b->getFleetStat() == placedHo
                                                                   || p1b->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    uOccupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                p1b->setFleetStat(ready);
                p1b->setAdditionStat(addNull);
                p1b->setForthStat(noWord);
                doneOnHover = false;
                if (p1c->getFleetStat() == No)
                    p1c->setFleetStat(moveable);
                if (p1d->getFleetStat() == No)
                    p1d->setFleetStat(moveable);
                if (p1s->getFleetStat() == No)
                    p1s->setFleetStat(moveable);
                if (p1r->getFleetStat() == No)
                    p1r->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && p1b->getAdditionStat() == placed) {
                p1b->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user destroyer
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && p1d->getFleetStat() == moveable && curr == playerOneSet) {
                if (x >= p1d->getLeftX() && x <= p1d->getRightX() && y >= p1d->getTopY() && y <= p1d->getBottomY()) {
                    p1d->setFleetStat(selected);
                    p1d->setThirdStat(noWord);
                    p1d->setForthStat(working);
                    p1d->setFifthStat(noWord);
                    if (p1c->getFleetStat() != ready)
                        p1c->setFleetStat(No);
                    if (p1b->getFleetStat() != ready)
                        p1b->setFleetStat(No);
                    if (p1s->getFleetStat() != ready)
                        p1s->setFleetStat(No);
                    if (p1r->getFleetStat() != ready)
                        p1r->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && p1d->getFleetStat() == selected) {
                if (p1d->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    occupiedCellsTemp.clear();
                    p1d->setCenterX(userBoard.getCellX(cellNumber - 1));
                    p1d->setCenterY(userBoard.getCellY(cellNumber - 1));
                    if (p1d->getWidth() == 30 && p1d->getHeight() == 89) {
                        p1d->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(p1d->getCenterX(),p1d->getCenterY());
                        for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1d->setCenterX(220);
                            p1d->setCenterY(500);
                            p1d->setFleetStat(moveable);
                            p1d->setFifthStat(overlapping);
                        }
                    }
                    else {
                        p1d->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(p1d->getCenterX(),p1d->getCenterY());
                        for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1d->setCenterX(220);
                            p1d->setCenterY(500);
                            p1d->setFleetStat(moveable);
                            p1d->setFifthStat(overlapping);
                        }
                    }
                    p1d->setAdditionStat(placed);
                    p1d->setThirdStat(noWord);
                } else {
                    p1d->setCenterX(220);
                    p1d->setCenterY(500);
                    p1d->setFleetStat(moveable);
                    p1d->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1d->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                p1d->setWidth(89);
                p1d->setHeight(30);
                p1d->setFleetStat(placedVe);
                p1d->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1d->getCenterX(),p1d->getCenterY());
                for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1d->setCenterX(220);
                    p1d->setCenterY(500);
                    p1d->setFleetStat(moveable);
                    p1d->setFifthStat(overlapping);
                } else if (!p1d->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1d->setWidth(30);
                    p1d->setHeight(89);
                    p1d->setCenterX(220);
                    p1d->setCenterY(500);
                    p1d->setFleetStat(moveable);
                    p1d->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1d->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                p1d->setWidth(30);
                p1d->setHeight(89);
                p1d->setFleetStat(placedHo);
                p1d->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1d->getCenterX(),p1d->getCenterY());
                for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1d->setCenterX(220);
                    p1d->setCenterY(500);
                    p1d->setFleetStat(moveable);
                    p1d->setFifthStat(overlapping);
                } else if (!p1d->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1d->setWidth(30);
                    p1d->setHeight(89);
                    p1d->setCenterX(220);
                    p1d->setCenterY(500);
                    p1d->setFleetStat(moveable);
                    p1d->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (p1d->getFleetStat() == placedHo
                                                                   || p1d->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    uOccupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                p1d->setFleetStat(ready);
                p1d->setAdditionStat(addNull);
                p1d->setForthStat(noWord);
                doneOnHover = false;
                if (p1c->getFleetStat() == No)
                    p1c->setFleetStat(moveable);
                if (p1b->getFleetStat() == No)
                    p1b->setFleetStat(moveable);
                if (p1s->getFleetStat() == No)
                    p1s->setFleetStat(moveable);
                if (p1r->getFleetStat() == No)
                    p1r->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && p1d->getAdditionStat() == placed) {
                p1d->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user sub
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && p1s->getFleetStat() == moveable && curr == playerOneSet) {
                if (x >= p1s->getLeftX() && x <= p1s->getRightX() && y >= p1s->getTopY() && y <= p1s->getBottomY()) {
                    p1s->setFleetStat(selected);
                    p1s->setThirdStat(noWord);
                    p1s->setForthStat(working);
                    p1s->setFifthStat(noWord);
                    if (p1c->getFleetStat() != ready)
                        p1c->setFleetStat(No);
                    if (p1b->getFleetStat() != ready)
                        p1b->setFleetStat(No);
                    if (p1d->getFleetStat() != ready)
                        p1d->setFleetStat(No);
                    if (p1r->getFleetStat() != ready)
                        p1r->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && p1s->getFleetStat() == selected) {
                if (p1s->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    occupiedCellsTemp.clear();
                    p1s->setCenterX(userBoard.getCellX(cellNumber - 1));
                    p1s->setCenterY(userBoard.getCellY(cellNumber - 1));
                    if (p1s->getWidth() == 30 && p1s->getHeight() == 89) {
                        p1s->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(p1s->getCenterX(),p1s->getCenterY());
                        for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1s->setCenterX(280);
                            p1s->setCenterY(500);
                            p1s->setFleetStat(moveable);
                            p1s->setFifthStat(overlapping);
                        }
                    }
                    else {
                        p1s->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(p1s->getCenterX(),p1s->getCenterY());
                        for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1s->setCenterX(280);
                            p1s->setCenterY(500);
                            p1s->setFleetStat(moveable);
                            p1s->setFifthStat(overlapping);
                        }
                    }
                    p1s->setAdditionStat(placed);
                    p1s->setThirdStat(noWord);
                } else {
                    p1s->setCenterX(280);
                    p1s->setCenterY(500);
                    p1s->setFleetStat(moveable);
                    p1s->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1s->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                p1s->setWidth(89);
                p1s->setHeight(30);
                p1s->setFleetStat(placedVe);
                p1s->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1s->getCenterX(),p1s->getCenterY());
                for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1s->setCenterX(280);
                    p1s->setCenterY(500);
                    p1s->setFleetStat(moveable);
                    p1s->setFifthStat(overlapping);
                } else if (!p1s->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1s->setWidth(30);
                    p1s->setHeight(89);
                    p1s->setCenterX(280);
                    p1s->setCenterY(500);
                    p1s->setFleetStat(moveable);
                    p1s->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1s->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                p1s->setWidth(30);
                p1s->setHeight(89);
                p1s->setFleetStat(placedHo);
                p1s->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1s->getCenterX(),p1s->getCenterY());
                for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1s->setCenterX(280);
                    p1s->setCenterY(500);
                    p1s->setFleetStat(moveable);
                    p1s->setFifthStat(overlapping);
                } else if (!p1s->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1s->setWidth(30);
                    p1s->setHeight(89);
                    p1s->setCenterX(280);
                    p1s->setCenterY(500);
                    p1s->setFleetStat(moveable);
                    p1s->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (p1s->getFleetStat() == placedHo
                                                                   || p1s->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    uOccupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                p1s->setFleetStat(ready);
                p1s->setAdditionStat(addNull);
                p1s->setForthStat(noWord);
                doneOnHover = false;
                if (p1c->getFleetStat() == No)
                    p1c->setFleetStat(moveable);
                if (p1b->getFleetStat() == No)
                    p1b->setFleetStat(moveable);
                if (p1d->getFleetStat() == No)
                    p1d->setFleetStat(moveable);
                if (p1r->getFleetStat() == No)
                    p1r->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && p1s->getAdditionStat() == placed) {
                p1s->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user cruiser
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && p1r->getFleetStat() == moveable && curr == playerOneSet) {
                if (x >= p1r->getLeftX() && x <= p1r->getRightX() && y >= p1r->getTopY() && y <= p1r->getBottomY()) {
                    p1r->setFleetStat(selected);
                    p1r->setThirdStat(noWord);
                    p1r->setForthStat(working);
                    p1r->setFifthStat(noWord);
                    if (p1c->getFleetStat() != ready)
                        p1c->setFleetStat(No);
                    if (p1b->getFleetStat() != ready)
                        p1b->setFleetStat(No);
                    if (p1d->getFleetStat() != ready)
                        p1d->setFleetStat(No);
                    if (p1s->getFleetStat() != ready)
                        p1s->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && p1r->getFleetStat() == selected) {
                if (p1r->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    occupiedCellsTemp.clear();
                    if (p1r->getWidth() == 30 && p1r->getHeight() == 59) {
                        p1r->setCenterX(userBoard.getCellX(cellNumber - 1));
                        p1r->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                        p1r->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(p1r->getCenterX(),p1r->getCenterY());
                        for (int i = ocNumber - 10; i <= ocNumber; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1r->setCenterX(340);
                            p1r->setCenterY(500);
                            p1r->setFleetStat(moveable);
                            p1r->setFifthStat(overlapping);
                        }
                    }
                    else {
                        p1r->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                        p1r->setCenterY(userBoard.getCellY(cellNumber));
                        p1r->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(p1r->getCenterX(),p1r->getCenterY());
                        for (int i = ocNumber - 1; i <= ocNumber; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                            p1r->setCenterX(340);
                            p1r->setCenterY(500);
                            p1r->setFleetStat(moveable);
                            p1r->setFifthStat(overlapping);
                        }
                    }
                    p1r->setAdditionStat(placed);
                    p1r->setThirdStat(noWord);
                } else {
                    p1r->setCenterX(340);
                    p1r->setCenterY(500);
                    p1r->setFleetStat(moveable);
                    p1r->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1r->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                p1r->setWidth(59);
                p1r->setHeight(30);
                p1r->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                p1r->setCenterY(userBoard.getCellY(cellNumber));
                p1r->setFleetStat(placedVe);
                p1r->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1r->getCenterX(),p1r->getCenterY());
                for (int i = ocNumber - 1; i <= ocNumber; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1r->setCenterX(340);
                    p1r->setCenterY(500);
                    p1r->setFleetStat(moveable);
                    p1r->setFifthStat(overlapping);
                } else if (!p1r->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1r->setWidth(30);
                    p1r->setHeight(59);
                    p1r->setCenterX(340);
                    p1r->setCenterY(500);
                    p1r->setFleetStat(moveable);
                    p1r->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && p1r->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                p1r->setWidth(30);
                p1r->setHeight(59);
                p1r->setCenterX(userBoard.getCellX(cellNumber - 1));
                p1r->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                p1r->setFleetStat(placedHo);
                p1r->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(p1r->getCenterX(),p1r->getCenterY());
                for (int i = ocNumber - 10; i <= ocNumber; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,uOccupiedCells)) {
                    p1r->setCenterX(340);
                    p1r->setCenterY(500);
                    p1r->setFleetStat(moveable);
                    p1r->setFifthStat(overlapping);
                } else if (!p1r->inBoard(uboardL,uboardR,uboardT,uboardB)) {
                    p1r->setWidth(30);
                    p1r->setHeight(59);
                    p1r->setCenterX(340);
                    p1r->setCenterY(500);
                    p1r->setFleetStat(moveable);
                    p1r->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (p1r->getFleetStat() == placedHo
                                                                   || p1r->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    uOccupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                p1r->setFleetStat(ready);
                p1r->setAdditionStat(addNull);
                p1r->setForthStat(noWord);
                doneOnHover = false;
                if (p1c->getFleetStat() == No)
                    p1c->setFleetStat(moveable);
                if (p1b->getFleetStat() == No)
                    p1b->setFleetStat(moveable);
                if (p1d->getFleetStat() == No)
                    p1d->setFleetStat(moveable);
                if (p1s->getFleetStat() == No)
                    p1s->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && p1r->getAdditionStat() == placed) {
                p1r->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            if (state == GLUT_DOWN && x >= gameUserBoard.getLeftX() && x <= gameUserBoard.getRightX() && y >= gameUserBoard.getTopY() &&
                y <= gameUserBoard.getBottomY() && curr == game) {
                cellNumber = gameUserBoard.cellNum(x,y);
                if (find(uOccupiedCells.begin(),uOccupiedCells.end(),cellNumber) != uOccupiedCells.end()){
                    gHitCells.push_back(cellNumber);
                    gameOver = checkEquality(gHitCells,uOccupiedCells);
                } else {
                    gNotHit.push_back(cellNumber);
                }
            }

            if (state == GLUT_DOWN && curr == finished) {
                break;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            break;
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
    glutInitWindowPosition(400,100);

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

