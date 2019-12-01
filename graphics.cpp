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
#include "BPlayerOne.h"



using namespace std;
GLdouble width, height;
GLint wd, cellNumber,ocNumber;
GLint boardL,boardR,boardT,boardB;
Cell cells;
BPlayerOne userBoard;
UCarrier* uc = new UCarrier;
UBattleship* ub = new UBattleship;
UDestroyer* ud = new UDestroyer;
USub* us = new USub;
UCruiser* ur = new UCruiser;
bool mouseInput = false;
bool doneOnHover = false;
vector<int> occupiedCells;
vector<int> occupiedCellsTemp;
vector<int> userBCarrier, userBBattleship, userBDestroyer, userBSub, userBCruiser;

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
    userBoard.drawBoard();
    boardL = userBoard.getLeftX();
    boardR = userBoard.getRightX();
    boardT = userBoard.getTopY();
    boardB = userBoard.getBottomY();
    uc->draw();
    ub->draw();
    ud->draw();
    us->draw();
    ur->draw();

    if (uc->getFleetStat() == placedHo || ub->getFleetStat() == placedHo || ud->getFleetStat() == placedHo || us->getFleetStat() == placedHo
        || ur->getFleetStat() == placedHo || uc->getFleetStat() == placedVe || ub->getFleetStat() == placedVe || ud->getFleetStat() == placedVe
        || us->getFleetStat() == placedVe || ur->getFleetStat() == placedVe) {
        cells.drawButton("change dirction");
        cells.drawDone("done");
    }

    if (uc->getThirdStat() == out) {
        uc->outBoard("carrier is out of board");
    }
    if (uc->getForthStat() == working) {
        uc->focus("working on placing carrier");
    }
    if (uc->getFifthStat() == overlapping) {
        uc->overlap("carrier get overlapped");
    }
    if (ub->getThirdStat() == out) {
        ub->outBoard("battleship is out of board");
    }
    if (ub->getForthStat() == working) {
        ub->focus("working on placing battleship");
    }
    if (ub->getFifthStat() == overlapping) {
        ub->overlap("battleship get overlapped");
    }
    if (ud->getThirdStat() == out) {
        ud->outBoard("destroyer is out of board");
    }
    if (ud->getForthStat() == working) {
        ud->focus("working on placing destroyer");
    }
    if (ud->getFifthStat() == overlapping) {
        ud->overlap("destroyer get overlapped");
    }
    if (us->getThirdStat() == out) {
        us->outBoard("sub is out of board");
    }
    if (us->getForthStat() == working) {
        us->focus("working on placing sub");
    }
    if (us->getFifthStat() == overlapping) {
        us->overlap("sub get overlapped");
    }
    if (ur->getThirdStat() == out) {
        ur->outBoard("cruiser is out of board");
    }
    if (ur->getForthStat() == working) {
        ur->focus("working on placing cruiser");
    }
    if (ur->getFifthStat() == overlapping) {
        ur->overlap("cruiser get overlapped");
    }

    if (doneOnHover) {
        cells.hoverDone("once click, ship can't be moving again");
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
    if (uc->getFleetStat() == selected) {
        uc->drag(uc,x,y);
        glutPostRedisplay();
    }
    if (ub->getFleetStat() == selected) {
        ub->drag(ub,x,y);
        glutPostRedisplay();
    }
    if (ud->getFleetStat() == selected) {
        ud->drag(ud,x,y);
        glutPostRedisplay();
    }
    if (us->getFleetStat() == selected) {
        us->drag(us,x,y);
        glutPostRedisplay();
    }
    if (ur->getFleetStat() == selected) {
        ur->drag(ur,x,y);
        glutPostRedisplay();
    }

    doneOnHover = cells.inDone(x, y) && (uc->getFleetStat() == placedHo || uc->getFleetStat() == placedVe
                                         || ub->getFleetStat() == placedHo || ub->getFleetStat() == placedVe || ud->getFleetStat() == placedHo
                                         || ud->getFleetStat() == placedVe || us->getFleetStat() == placedHo || us->getFleetStat() == placedVe
                                         || ur->getFleetStat() == placedVe || ur->getFleetStat() == placedHo);
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
            if (state == GLUT_DOWN && x >= userBoard.getLeftX() && x <= userBoard.getRightX() && y >= userBoard.getTopY() &&
                y <= userBoard.getBottomY()) {
                cellNumber = userBoard.cellNum(x,y);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user carrier
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && uc->getFleetStat() == moveable ) {
                if (x >= uc->getLeftX() && x <= uc->getRightX() && y >= uc->getTopY() && y <= uc->getBottomY()) {
                    uc->setFleetStat(selected);
                    uc->setThirdStat(noWord);
                    uc->setForthStat(working);
                    uc->setFifthStat(noWord);
                    if (ub->getFleetStat() != ready)
                        ub->setFleetStat(No);
                    if (ud->getFleetStat() != ready)
                        ud->setFleetStat(No);
                    if (us->getFleetStat() != ready)
                        us->setFleetStat(No);
                    if (ur->getFleetStat() != ready)
                        ur->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && uc->getFleetStat() == selected) {
                occupiedCellsTemp.clear();
                if (uc->inBoard(boardL,boardR,boardT,boardB)) {
                    uc->setCenterX(userBoard.getCellX(cellNumber - 1));
                    uc->setCenterY(userBoard.getCellY(cellNumber - 1));
                    if (uc->getWidth() == 30 && uc->getHeight() == 149) {
                        uc->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(uc->getCenterX(),uc->getCenterY());
                        for (int i = ocNumber - 20; i <= ocNumber + 20; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            uc->setCenterX(100);
                            uc->setCenterY(500);
                            uc->setFleetStat(moveable);
                            uc->setFifthStat(overlapping);
                        }
                    }
                    else {
                        uc->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(uc->getCenterX(),uc->getCenterY());
                        for (int i = ocNumber - 2; i <= ocNumber + 2; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            uc->setCenterX(100);
                            uc->setCenterY(500);
                            uc->setFleetStat(moveable);
                            uc->setFifthStat(overlapping);
                        }
                    }
                    uc->setAdditionStat(placed);
                } else {
                    uc->setCenterX(100);
                    uc->setCenterY(500);
                    uc->setFleetStat(moveable);
                    uc->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && uc->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                uc->setWidth(149);
                uc->setHeight(30);
                uc->setFleetStat(placedVe);
                uc->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(uc->getCenterX(),uc->getCenterY());
                for (int i = ocNumber - 2; i <= ocNumber + 2; i += 1) {
                    occupiedCellsTemp.push_back(i);
                }
                if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    uc->setCenterX(100);
                    uc->setCenterY(500);
                    uc->setFleetStat(moveable);
                    uc->setFifthStat(overlapping);
                } else if (!uc->inBoard(boardL,boardR,boardT,boardB)) {
                    uc->setWidth(30);
                    uc->setHeight(149);
                    uc->setCenterX(100);
                    uc->setCenterY(500);
                    uc->setFleetStat(moveable);
                    uc->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && uc->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                uc->setWidth(30);
                uc->setHeight(149);
                uc->setFleetStat(placedHo);
                uc->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(uc->getCenterX(),uc->getCenterY());
                for (int i = ocNumber - 20; i <= ocNumber + 20; i += 10) {
                    occupiedCellsTemp.push_back(i);
                }
                if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    uc->setCenterX(100);
                    uc->setCenterY(500);
                    uc->setFleetStat(moveable);
                    uc->setFifthStat(overlapping);
                } else if (!uc->inBoard(boardL,boardR,boardT,boardB)) {
                    uc->setWidth(30);
                    uc->setHeight(149);
                    uc->setCenterX(100);
                    uc->setCenterY(500);
                    uc->setFleetStat(moveable);
                    uc->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (uc->getFleetStat() == placedHo
            || uc->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    occupiedCells.push_back(num);
                }
                uc->setFleetStat(ready);
                uc->setAdditionStat(addNull);
                uc->setForthStat(noWord);
                doneOnHover = false;
                if (ub->getFleetStat() == No)
                    ub->setFleetStat(moveable);
                if (ud->getFleetStat() == No)
                    ud->setFleetStat(moveable);
                if (us->getFleetStat() == No)
                    us->setFleetStat(moveable);
                if (ur->getFleetStat() == No)
                    ur->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && uc->getAdditionStat() == placed) {
                uc->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user battleship
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && ub->getFleetStat() == moveable ) {
                if (x >= ub->getLeftX() && x <= ub->getRightX() && y >= ub->getTopY() && y <= ub->getBottomY()) {
                    ub->setFleetStat(selected);
                    ub->setThirdStat(noWord);
                    ub->setForthStat(working);
                    ub->setFifthStat(noWord);
                    if (uc->getFleetStat() != ready)
                        uc->setFleetStat(No);
                    if (ud->getFleetStat() != ready)
                        ud->setFleetStat(No);
                    if (us->getFleetStat() != ready)
                        us->setFleetStat(No);
                    if (ur->getFleetStat() != ready)
                        ur->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && ub->getFleetStat() == selected) {
                occupiedCellsTemp.clear();
                if (ub->inBoard(boardL,boardR,boardT,boardB)) {
                    if (ub->getWidth() == 30 && ub->getHeight() == 119) {
                        ub->setCenterX(userBoard.getCellX(cellNumber - 1));
                        ub->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                        ub->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(ub->getCenterX(),ub->getCenterY());
                        for (int i = ocNumber - 20; i <= ocNumber + 10; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            ub->setCenterX(160);
                            ub->setCenterY(500);
                            ub->setFleetStat(moveable);
                            ub->setFifthStat(overlapping);
                        }
                    }
                    else {
                        ub->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                        ub->setCenterY(userBoard.getCellY(cellNumber));
                        ub->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(ub->getCenterX(),ub->getCenterY());
                        for (int i = ocNumber - 2; i <= ocNumber + 1; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            ub->setCenterX(160);
                            ub->setCenterY(500);
                            ub->setFleetStat(moveable);
                            ub->setFifthStat(overlapping);
                        }
                    }
                    ub->setAdditionStat(placed);
                    ub->setThirdStat(noWord);
                } else {
                    ub->setCenterX(160);
                    ub->setCenterY(500);
                    ub->setFleetStat(moveable);
                    ub->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && ub->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                ub->setWidth(119);
                ub->setHeight(30);
                ub->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                ub->setCenterY(userBoard.getCellY(cellNumber));
                ub->setFleetStat(placedVe);
                ub->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(ub->getCenterX(),ub->getCenterY());
                for (int i = ocNumber - 2; i <= ocNumber + 1; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    ub->setCenterX(160);
                    ub->setCenterY(500);
                    ub->setFleetStat(moveable);
                    ub->setFifthStat(overlapping);
                } else if (!ub->inBoard(boardL,boardR,boardT,boardB)) {
                    ub->setWidth(30);
                    ub->setHeight(119);
                    ub->setCenterX(160);
                    ub->setCenterY(500);
                    ub->setFleetStat(moveable);
                    ub->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && ub->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                ub->setWidth(30);
                ub->setHeight(119);
                ub->setCenterX(userBoard.getCellX(cellNumber - 1));
                ub->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                ub->setFleetStat(placedHo);
                ub->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(ub->getCenterX(),ub->getCenterY());
                for (int i = ocNumber - 20; i <= ocNumber + 10; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    ub->setCenterX(160);
                    ub->setCenterY(500);
                    ub->setFleetStat(moveable);
                    ub->setFifthStat(overlapping);
                } else if (!ub->inBoard(boardL,boardR,boardT,boardB)) {
                    ub->setWidth(30);
                    ub->setHeight(119);
                    ub->setCenterX(160);
                    ub->setCenterY(500);
                    ub->setFleetStat(moveable);
                    ub->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (ub->getFleetStat() == placedHo
            || ub->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    occupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                ub->setFleetStat(ready);
                ub->setAdditionStat(addNull);
                ub->setForthStat(noWord);
                doneOnHover = false;
                if (uc->getFleetStat() == No)
                    uc->setFleetStat(moveable);
                if (ud->getFleetStat() == No)
                    ud->setFleetStat(moveable);
                if (us->getFleetStat() == No)
                    us->setFleetStat(moveable);
                if (ur->getFleetStat() == No)
                    ur->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && ub->getAdditionStat() == placed) {
                ub->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user destroyer
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && ud->getFleetStat() == moveable ) {
                if (x >= ud->getLeftX() && x <= ud->getRightX() && y >= ud->getTopY() && y <= ud->getBottomY()) {
                    ud->setFleetStat(selected);
                    ud->setThirdStat(noWord);
                    ud->setForthStat(working);
                    ud->setFifthStat(noWord);
                    if (uc->getFleetStat() != ready)
                        uc->setFleetStat(No);
                    if (ub->getFleetStat() != ready)
                        ub->setFleetStat(No);
                    if (us->getFleetStat() != ready)
                        us->setFleetStat(No);
                    if (ur->getFleetStat() != ready)
                        ur->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && ud->getFleetStat() == selected) {
                if (ud->inBoard(boardL,boardR,boardT,boardB)) {
                    occupiedCellsTemp.clear();
                    ud->setCenterX(userBoard.getCellX(cellNumber - 1));
                    ud->setCenterY(userBoard.getCellY(cellNumber - 1));
                    if (ud->getWidth() == 30 && ud->getHeight() == 89) {
                        ud->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(ud->getCenterX(),ud->getCenterY());
                        for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            ud->setCenterX(220);
                            ud->setCenterY(500);
                            ud->setFleetStat(moveable);
                            ud->setFifthStat(overlapping);
                        }
                    }
                    else {
                        ud->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(ud->getCenterX(),ud->getCenterY());
                        for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            ud->setCenterX(220);
                            ud->setCenterY(500);
                            ud->setFleetStat(moveable);
                            ud->setFifthStat(overlapping);
                        }
                    }
                    ud->setAdditionStat(placed);
                    ud->setThirdStat(noWord);
                } else {
                    ud->setCenterX(220);
                    ud->setCenterY(500);
                    ud->setFleetStat(moveable);
                    ud->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && ud->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                ud->setWidth(89);
                ud->setHeight(30);
                ud->setFleetStat(placedVe);
                ud->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(ud->getCenterX(),ud->getCenterY());
                for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    ud->setCenterX(220);
                    ud->setCenterY(500);
                    ud->setFleetStat(moveable);
                    ud->setFifthStat(overlapping);
                } else if (!ud->inBoard(boardL,boardR,boardT,boardB)) {
                    ud->setWidth(30);
                    ud->setHeight(89);
                    ud->setCenterX(220);
                    ud->setCenterY(500);
                    ud->setFleetStat(moveable);
                    ud->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && ud->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                ud->setWidth(30);
                ud->setHeight(89);
                ud->setFleetStat(placedHo);
                ud->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(ud->getCenterX(),ud->getCenterY());
                for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    ud->setCenterX(220);
                    ud->setCenterY(500);
                    ud->setFleetStat(moveable);
                    ud->setFifthStat(overlapping);
                } else if (!ud->inBoard(boardL,boardR,boardT,boardB)) {
                    ud->setWidth(30);
                    ud->setHeight(89);
                    ud->setCenterX(220);
                    ud->setCenterY(500);
                    ud->setFleetStat(moveable);
                    ud->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (ud->getFleetStat() == placedHo
            || ud->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    occupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                ud->setFleetStat(ready);
                ud->setAdditionStat(addNull);
                ud->setForthStat(noWord);
                doneOnHover = false;
                if (uc->getFleetStat() == No)
                    uc->setFleetStat(moveable);
                if (ub->getFleetStat() == No)
                    ub->setFleetStat(moveable);
                if (us->getFleetStat() == No)
                    us->setFleetStat(moveable);
                if (ur->getFleetStat() == No)
                    ur->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && ud->getAdditionStat() == placed) {
                ud->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user sub
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && us->getFleetStat() == moveable ) {
                if (x >= us->getLeftX() && x <= us->getRightX() && y >= us->getTopY() && y <= us->getBottomY()) {
                    us->setFleetStat(selected);
                    us->setThirdStat(noWord);
                    us->setForthStat(working);
                    us->setFifthStat(noWord);
                    if (uc->getFleetStat() != ready)
                        uc->setFleetStat(No);
                    if (ub->getFleetStat() != ready)
                        ub->setFleetStat(No);
                    if (ud->getFleetStat() != ready)
                        ud->setFleetStat(No);
                    if (ur->getFleetStat() != ready)
                        ur->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && us->getFleetStat() == selected) {
                if (us->inBoard(boardL,boardR,boardT,boardB)) {
                    occupiedCellsTemp.clear();
                    us->setCenterX(userBoard.getCellX(cellNumber - 1));
                    us->setCenterY(userBoard.getCellY(cellNumber - 1));
                    if (us->getWidth() == 30 && us->getHeight() == 89) {
                        us->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(us->getCenterX(),us->getCenterY());
                        for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            us->setCenterX(280);
                            us->setCenterY(500);
                            us->setFleetStat(moveable);
                            us->setFifthStat(overlapping);
                        }
                    }
                    else {
                        us->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(us->getCenterX(),us->getCenterY());
                        for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            us->setCenterX(280);
                            us->setCenterY(500);
                            us->setFleetStat(moveable);
                            us->setFifthStat(overlapping);
                        }
                    }
                    us->setAdditionStat(placed);
                    us->setThirdStat(noWord);
                } else {
                    us->setCenterX(280);
                    us->setCenterY(500);
                    us->setFleetStat(moveable);
                    us->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && us->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                us->setWidth(89);
                us->setHeight(30);
                us->setFleetStat(placedVe);
                us->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(us->getCenterX(),us->getCenterY());
                for (int i = ocNumber - 1; i <= ocNumber + 1; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    us->setCenterX(280);
                    us->setCenterY(500);
                    us->setFleetStat(moveable);
                    us->setFifthStat(overlapping);
                } else if (!us->inBoard(boardL,boardR,boardT,boardB)) {
                    us->setWidth(30);
                    us->setHeight(89);
                    us->setCenterX(280);
                    us->setCenterY(500);
                    us->setFleetStat(moveable);
                    us->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && us->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                us->setWidth(30);
                us->setHeight(89);
                us->setFleetStat(placedHo);
                us->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(us->getCenterX(),us->getCenterY());
                for (int i = ocNumber - 10; i <= ocNumber + 10; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    us->setCenterX(280);
                    us->setCenterY(500);
                    us->setFleetStat(moveable);
                    us->setFifthStat(overlapping);
                } else if (!us->inBoard(boardL,boardR,boardT,boardB)) {
                    us->setWidth(30);
                    us->setHeight(89);
                    us->setCenterX(280);
                    us->setCenterY(500);
                    us->setFleetStat(moveable);
                    us->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (us->getFleetStat() == placedHo
            || us->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    occupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                us->setFleetStat(ready);
                us->setAdditionStat(addNull);
                us->setForthStat(noWord);
                doneOnHover = false;
                if (uc->getFleetStat() == No)
                    uc->setFleetStat(moveable);
                if (ub->getFleetStat() == No)
                    ub->setFleetStat(moveable);
                if (ud->getFleetStat() == No)
                    ud->setFleetStat(moveable);
                if (ur->getFleetStat() == No)
                    ur->setFleetStat(moveable);
            } else if (state == GLUT_DOWN && us->getAdditionStat() == placed) {
                us->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

            // user cruiser
            // -------------------------------------------------------------------------------------------------------------
            if (state == GLUT_DOWN && ur->getFleetStat() == moveable ) {
                if (x >= ur->getLeftX() && x <= ur->getRightX() && y >= ur->getTopY() && y <= ur->getBottomY()) {
                    ur->setFleetStat(selected);
                    ur->setThirdStat(noWord);
                    ur->setForthStat(working);
                    ur->setFifthStat(noWord);
                    if (uc->getFleetStat() != ready)
                        uc->setFleetStat(No);
                    if (ub->getFleetStat() != ready)
                        ub->setFleetStat(No);
                    if (ud->getFleetStat() != ready)
                        ud->setFleetStat(No);
                    if (us->getFleetStat() != ready)
                        us->setFleetStat(No);
                    glutPostRedisplay();
                }
            } else if (state == GLUT_DOWN && ur->getFleetStat() == selected) {
                if (ur->inBoard(boardL,boardR,boardT,boardB)) {
                    occupiedCellsTemp.clear();
                    if (ur->getWidth() == 30 && ur->getHeight() == 59) {
                        ur->setCenterX(userBoard.getCellX(cellNumber - 1));
                        ur->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                        ur->setFleetStat(placedHo);
                        ocNumber = userBoard.cellNum(ur->getCenterX(),ur->getCenterY());
                        for (int i = ocNumber - 10; i <= ocNumber; i += 10) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            ur->setCenterX(340);
                            ur->setCenterY(500);
                            ur->setFleetStat(moveable);
                            ur->setFifthStat(overlapping);
                        }
                    }
                    else {
                        ur->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                        ur->setCenterY(userBoard.getCellY(cellNumber));
                        ur->setFleetStat(placedVe);
                        ocNumber = userBoard.cellNum(ur->getCenterX(),ur->getCenterY());
                        for (int i = ocNumber - 1; i <= ocNumber; i += 1) {
                            occupiedCellsTemp.push_back(i);
                        }
                        if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                            ur->setCenterX(340);
                            ur->setCenterY(500);
                            ur->setFleetStat(moveable);
                            ur->setFifthStat(overlapping);
                        }
                    }
                    ur->setAdditionStat(placed);
                    ur->setThirdStat(noWord);
                } else {
                    ur->setCenterX(340);
                    ur->setCenterY(500);
                    ur->setFleetStat(moveable);
                    ur->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && ur->getFleetStat() == placedHo) {
                occupiedCellsTemp.clear();
                ur->setWidth(59);
                ur->setHeight(30);
                ur->setCenterX(userBoard.getCellX(cellNumber) - cells.getWidth() / 2);
                ur->setCenterY(userBoard.getCellY(cellNumber));
                ur->setFleetStat(placedVe);
                ur->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(ur->getCenterX(),ur->getCenterY());
                for (int i = ocNumber - 1; i <= ocNumber; i += 1) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    ur->setCenterX(340);
                    ur->setCenterY(500);
                    ur->setFleetStat(moveable);
                    ur->setFifthStat(overlapping);
                } else if (!ur->inBoard(boardL,boardR,boardT,boardB)) {
                    ur->setWidth(30);
                    ur->setHeight(59);
                    ur->setCenterX(340);
                    ur->setCenterY(500);
                    ur->setFleetStat(moveable);
                    ur->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inButton(x,y) && ur->getFleetStat() == placedVe) {
                occupiedCellsTemp.clear();
                ur->setWidth(30);
                ur->setHeight(59);
                ur->setCenterX(userBoard.getCellX(cellNumber - 1));
                ur->setCenterY(userBoard.getCellY(cellNumber - 1) + cells.getWidth() / 2);
                ur->setFleetStat(placedHo);
                ur->setAdditionStat(placed);
                ocNumber = userBoard.cellNum(ur->getCenterX(),ur->getCenterY());
                for (int i = ocNumber - 10; i <= ocNumber; i += 10) {
                    occupiedCellsTemp.push_back(i);
                } if (checkCommon(occupiedCellsTemp,occupiedCells)) {
                    ur->setCenterX(340);
                    ur->setCenterY(500);
                    ur->setFleetStat(moveable);
                    ur->setFifthStat(overlapping);
                } else if (!ur->inBoard(boardL,boardR,boardT,boardB)) {
                    ur->setWidth(30);
                    ur->setHeight(59);
                    ur->setCenterX(340);
                    ur->setCenterY(500);
                    ur->setFleetStat(moveable);
                    ur->setThirdStat(out);
                }
            } else if (state == GLUT_DOWN && cells.inDone(x,y) && (ur->getFleetStat() == placedHo
            || ur->getFleetStat() == placedVe)) {
                for (int num : occupiedCellsTemp) {
                    occupiedCells.push_back(num);
                    occupiedCellsTemp.clear();
                }
                ur->setFleetStat(ready);
                ur->setAdditionStat(addNull);
                ur->setForthStat(noWord);
                doneOnHover = false;
                if (uc->getFleetStat() == No)
                    uc->setFleetStat(moveable);
                if (ub->getFleetStat() == No)
                    ub->setFleetStat(moveable);
                if (ud->getFleetStat() == No)
                    ud->setFleetStat(moveable);
                if (us->getFleetStat() == No)
                    us->setFleetStat(moveable);
                for (int num : occupiedCells) {
                    cout << num << ", ";
                }
            } else if (state == GLUT_DOWN && ur->getAdditionStat() == placed) {
                ur->setFleetStat(selected);
            }
            // -------------------------------------------------------------------------------------------------------------

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

