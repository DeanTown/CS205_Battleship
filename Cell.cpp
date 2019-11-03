#include "Cell.h"
using namespace std;
// square constructor
Cell::Cell()
{
    selected = false;
    position.resize(2);
    status = empty;
    pts[0] = point(0.2,0.2);
    pts[1] = point(0.4,0.2);
    pts[2] = point(0.4,0.4);
    pts[3] = point(0.2,0.4);
};

/* Getters */
bool Cell::getSelected() {
    return selected;
}
vector<int> Cell::getPosition() {
    return position;
}
cellStatus Cell::getStatus() {
    return status;
}

double Cell::getLength() const {
    return length;
}

double Cell::getWidth() const {
    return width;
}

double Cell::getCenterX() const {
    return position[0];
}

double Cell::getCenterY() const {
    return position[1];
}

double Cell::getLeftX() const {
    return position[0] - (getWidth() / 2.0);
}

double Cell::getRightX() const {
    return position[0] + (getWidth() / 2.0);
}

double Cell::getTopY() const {
    return position[1] - (getLength() / 2.0);
}

double Cell::getBottomY() const {
    return position[1] + (getLength() / 2.0);
}

int Cell::getCellNumber() const {
    return cellNumber;
}

/* Setters */
void Cell::setSelected(bool sel) {
    this->selected = sel;
}
void Cell::setPosition(int row, int col) {
    position[0] = row;
    position[1] = col;
}
void Cell::setStatus(cellStatus stat) {
    this->status = stat;
}

void Cell::setLength(int len) {
    this->length = len;
}

void Cell::setWidth(int wid) {
    this->width = wid;
}


// draw function
void Cell::draw(Cell *c)
{
    // draw square fill
    int i;
    glColor3f(1.0, 0.0, 0.2);
    glBegin(GL_QUADS);
    for (i = 0; i < 4; ++i)
    {
        glVertex2f(c->pts[i].x, c->pts[i].y);
    }
    glEnd();
    // draw square points
    i = 0;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; ++i)
    {
        glVertex2f(c->pts[i].x, c->pts[i].y);
    }
    glEnd();
}

// mouse function
point Cell::mouse(int x, int y)
{
    int windowWidth = 400, windowHeight = 400;
    return point(float(x)/windowWidth, 1.0 - float(y)/windowHeight);
}

// drag function
Cell* Cell::drag(Cell *c, point *mouse)
{
    c->pts[0].x = mouse->x - 0.1;
    c->pts[0].y = mouse->y - 0.1;
    c->pts[1].x = mouse->x + 0.1;
    c->pts[1].y = mouse->y - 0.1;

    c->pts[3].x = mouse->x - 0.1;
    c->pts[3].y = mouse->y + 0.1;

    c->pts[2].x = mouse->x + 0.1;
    c->pts[2].y = mouse->y + 0.1;

    return c;
}
void Cell::drawShapeDefault() {
    // draws grid lines set to white
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX(),getTopY());
    glVertex2d(getRightX(),getTopY());
    glVertex2d(getRightX(),getBottomY());
    glVertex2d(getLeftX(),getBottomY());
    glEnd();

    // draws color of box (set to black)
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}

void Cell::drawShapeOc() {
    // keeps inside color same when clicked on
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX(),getTopY());
    glVertex2d(getRightX(),getTopY());
    glVertex2d(getRightX(),getBottomY());
    glVertex2d(getLeftX(),getBottomY());
    glEnd();

    // this is color when clicked on
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(getLeftX() + 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getTopY() + 1);
    glVertex2d(getRightX() - 1,getBottomY() - 1);
    glVertex2d(getLeftX() + 1,getBottomY() - 1);
    glEnd();
}



///* Constructors */
//Cell::Cell() {
//    selected = false;
//    position.resize(2);
//    status = empty;
//}
//
///* Getters */
//bool Cell::getSelected() {
//    return selected;
//}
//vector<int> Cell::getPosition() {
//    return position;
//}
//cellStatus Cell::getStatus() {
//    return status;
//}
//
//double Cell::getLength() const {
//    return length;
//}
//
//double Cell::getWidth() const {
//    return width;
//}
//
//double Cell::getCenterX() const {
//    return position[0];
//}
//
//double Cell::getCenterY() const {
//    return position[1];
//}
//
//double Cell::getLeftX() const {
//    return position[0] - (getWidth() / 2.0);
//}
//
//double Cell::getRightX() const {
//    return position[0] + (getWidth() / 2.0);
//}
//
//double Cell::getTopY() const {
//    return position[1] - (getLength() / 2.0);
//}
//
//double Cell::getBottomY() const {
//    return position[1] + (getLength() / 2.0);
//}
//
//int Cell::getCellNumber() const {
//    return cellNumber;
//}
//
///* Setters */
//void Cell::setSelected(bool sel) {
//    this->selected = sel;
//}
//void Cell::setPosition(int row, int col) {
//    position[0] = row;
//    position[1] = col;
//}
//void Cell::setStatus(cellStatus stat) {
//    this->status = stat;
//}
//
//void Cell::setLength(int len) {
//    this->length = len;
//}
//
//void Cell::setWidth(int wid) {
//    this->width = wid;
//}
//
//
//void Cell::drawShapeDefault() {
//    // draws grid lines set to white
//    glColor3f(1.0,1.0,1.0);
//    glBegin(GL_QUADS);
//    glVertex2d(getLeftX(),getTopY());
//    glVertex2d(getRightX(),getTopY());
//    glVertex2d(getRightX(),getBottomY());
//    glVertex2d(getLeftX(),getBottomY());
//    glEnd();
//
//    // draws color of box (set to black)
//    glColor3f(0.0,0.0,0.0);
//    glBegin(GL_QUADS);
//    glVertex2d(getLeftX() + 1,getTopY() + 1);
//    glVertex2d(getRightX() - 1,getTopY() + 1);
//    glVertex2d(getRightX() - 1,getBottomY() - 1);
//    glVertex2d(getLeftX() + 1,getBottomY() - 1);
//    glEnd();
//}
//
//void Cell::drawShapeOc() {
//    // keeps inside color same when clicked on
//    glColor3f(1.0,1.0,1.0);
//    glBegin(GL_QUADS);
//    glVertex2d(getLeftX(),getTopY());
//    glVertex2d(getRightX(),getTopY());
//    glVertex2d(getRightX(),getBottomY());
//    glVertex2d(getLeftX(),getBottomY());
//    glEnd();
//
//    // this is color when clicked on
//    glColor3f(1.0,0.0,0.0);
//    glBegin(GL_QUADS);
//    glVertex2d(getLeftX() + 1,getTopY() + 1);
//    glVertex2d(getRightX() - 1,getTopY() + 1);
//    glVertex2d(getRightX() - 1,getBottomY() - 1);
//    glVertex2d(getLeftX() + 1,getBottomY() - 1);
//    glEnd();
//}