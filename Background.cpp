//
// Created by Harry Makovsky on 12/4/19.
//

#include "Background.h"
#include "string"
#include "graphics.h"

using namespace std;


Background::Background() {

    for (int i=0;i<height;i++){
        vector<Tangle> temp;
        background.push_back(temp);
    }

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            Tangle water;

            if( j %3==0){

                if(i %4==1) {
                    water = Tangle(size, size, darkBlue, darkBlue, {i *size, j * size});
                }else {
                    water= Tangle(size,size,lightBlue,lightBlue,{i*size,j*size});
                }
                background[i].push_back(water);

            }else if(j%3==1){

                if(i %2==0) {
                    water = Tangle(size, size, darkBlue, darkBlue, {i *size, j * size});
                }else {
                    water= Tangle(size,size,lightBlue,lightBlue,{i*size,j*size});
                }
                background[i].push_back(water);
            }else if(j%3==2) {
                if(i %4==3) {
                    water = Tangle(size, size, darkBlue, darkBlue, {i *size, j * size});
                }else {
                    water= Tangle(size,size,lightBlue,lightBlue,{i*size,j*size});
                }
                background[i].push_back(water);
            }
        }


        }

    body.setCenter(150,75);
    body2.setCenter(100,350);
    body3.setCenter(50,550);

    body4.setCenter(450,250);
    body5.setCenter(400,400);

    gun1.setCenter(150,75);
    gun2.setCenter(160,75);

}


void Background::drawShips(){

    gun1= Tangle(13,13,{0,0,0},{0,0,0},gun1.getCenter());
    gun2= Tangle(5,15,{0,0,0},{0,0,0},gun2.getCenter());


    body= Tangle(20,80,{0,0,0},{1,1,1},body.getCenter());

    body.draw();
    gun1.draw();
    gun2.draw();

    body2= Tangle(20,60,{0,0,0},{.3,.3,.8},body2.getCenter());

    body2.draw();

    body3= Tangle(20,40,{0,0,0},{1,1,1},body3.getCenter());

    body3.draw();

    body4= Tangle(20,60,{0,0,0},{1,1,1},body4.getCenter());

    body4.draw();

    body5= Tangle(20,100,{0,0,0},{1,1,1},body5.getCenter());


    body5.draw();
    string planes = "=}> =}>";
    glColor3f(0, 0, 0);
    glRasterPos2i(body5.getCenter().x,body5.getCenter().y);
    for (char r : planes) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, r);
    }



}
void Background::scrollShips(int velocity){
    point temp=body.getCenter();
    if(temp.x>900){
        body.setCenter(temp.x-900,temp.y);

    }else{
        body.setCenter(temp.x+velocity,temp.y);

    }

    point temp2=body2.getCenter();
    if(temp2.x>900){
        body2.setCenter(temp2.x-900,temp2.y);

    }else{
        body2.setCenter(temp2.x+velocity,temp2.y);

    }

    point temp3=body3.getCenter();
    if(temp3.x>900){
        body3.setCenter(temp3.x-900,temp3.y);

    }else{
        body3.setCenter(temp3.x+(2*velocity),temp3.y);

    }

    point temp4=body4.getCenter();
    if(temp4.x>900){
        body4.setCenter(temp4.x-900,temp4.y);

    }else{
        body4.setCenter(temp4.x+velocity,temp4.y);

    }

    point temp5=body5.getCenter();
    if(temp5.x>900){
        body5.setCenter(temp5.x-900,temp5.y);

    }else{
        body5.setCenter(temp5.x+velocity,temp5.y);

    }

    point temp6=gun1.getCenter();
    if(temp6.x>900){
        gun1.setCenter(temp6.x-900,temp6.y);

    }else{
        gun1.setCenter(temp6.x+velocity,temp6.y);

    }

    point temp7=gun2.getCenter();
    if(temp7.x>900){
        gun2.setCenter(temp7.x-900,temp7.y);

    }else{
        gun2.setCenter(temp7.x+velocity,temp7.y);

    }




}
// draw the background
void Background::draw() {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            background[i][j].draw();
        }
    }

    drawShips();

}
// function to handle scrolling on the background
void Background::scroll(int velocity) {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            point temp=background[i][j].getCenter();
            if(temp.x>900){
                background[i][j].setCenter(temp.x-900,temp.y);

            }else{
                background[i][j].setCenter(temp.x+velocity,temp.y);
            }


        }
    }
    scrollShips(velocity);

}