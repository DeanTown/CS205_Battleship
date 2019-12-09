//
// Created by Harry Makovsky on 12/4/19.
//

#ifndef CS205_FINAL_PROJECT_BACKGROUND_H
#define CS205_FINAL_PROJECT_BACKGROUND_H

#include "Shapes.h"
#include <vector>
using namespace std;

// Class to draw the background splash image on the starting screen.

class Background {
private:
    vector<vector<Tangle>> background;
    Tangle body,body2,body3,body4,body5;

    Tangle gun1,gun2;




    color lightBlue={0,0,.5};
    color darkBlue={0,0,1};
    int height=200;
    int width=200;
    int size=5;


public:

    Background();
    void draw();
    void scroll(int velocity);
    void drawShips();
    void scrollShips(int velocity);



};


#endif //CS205_FINAL_PROJECT_BACKGROUND_H
