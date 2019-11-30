#include "Fleet.h"
#include "graphics.h"

fleetStat Fleet::getFleetStat() const {
    return fs;
}
fleetStat Fleet::getAdditionStat() const {
    return fsTwo;
}
fleetStat Fleet::getThirdStat() const {
    return fsThree;
}
fleetStat Fleet::getForthStat() const {
    return fsFour;
}

void Fleet::setFleetStat(fleetStat fs) {
    this->fs = fs;
}

void Fleet::setAdditionStat(fleetStat fs) {
    fsTwo = fs;
}
void Fleet::setThirdStat(fleetStat fs) {
    fsThree = fs;
}
void Fleet::setForthStat(fleetStat fs) {
    fsFour = fs;
}

void Fleet::outBoard(std::string label) {
    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(420,240);
    for (char &le : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,le);
    }
}
void Fleet::focus(std::string label) {
    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(260,60);
    for (char &le : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,le);
    }
}
