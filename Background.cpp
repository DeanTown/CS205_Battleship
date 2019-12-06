//
// Created by Harry Makovsky on 12/4/19.
//

#include "Background.h"


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

}
// draw the background
void Background::draw() {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            background[i][j].draw();
        }
    }

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
}