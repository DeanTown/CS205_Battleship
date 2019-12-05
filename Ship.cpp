//
// Created by Oliver Reckord Groten on 10/22/19.
//

#include "Ship.h"
using namespace std;

/* Constructor */

Ship::Ship(){

}
Ship::Ship(int size) {
    this->size = size;
    hits=0;
    isVertical=true;

    // set carriers dimensions and starting center position
    // do for each ship
    carrierShipTang = Tangle(30*5,30);
    carrierShipTang.setCenter(100, 500);
    carrierShipP2 = Tangle(30*5,30);
    carrierShipP2.setCenter(600,500);

    battleShipTang = Tangle(30*4,30);
    battleShipTang.setCenter(145, 500);
    battleShipP2 = Tangle(30*4,30);
    battleShipP2.setCenter(645,500);

    cruiserShipTang = Tangle(30*2,30);
    cruiserShipTang.setCenter(190, 500);
    cruiserShipP2 = Tangle(30*2,30);
    cruiserShipP2.setCenter(690,500);

    subShipTang = Tangle(30*3,30);
    subShipTang.setCenter(235, 500);
    subShipP2 = Tangle(30*3,30);
    subShipP2.setCenter(735,500);

    destroyerShipTang = Tangle(30*3,30);
    destroyerShipTang.setCenter(280, 500);
    destroyerShipP2 = Tangle(30*3,30);
    destroyerShipP2.setCenter(780,500);
}
bool Ship::getVert(){
    return isVertical;
}
void Ship::setVert(bool vert){
    isVertical=vert;
}
void Ship::rotate(){
    if(isVertical){
        isVertical=false;
    }else{
        isVertical=true;
    }
}



/* Getters */
int Ship::getSize() {
    return size;
}
bool Ship::getDestroyed() {
    return size==hits;
}

int Ship::getCenterX_car() const {
    return shipCenter.x;
}
int Ship::getCenterY_car() const {
    return shipCenter.y;
}

/* Setters */
void Ship::setSize(int s) {
    size = s;
}
void Ship::setDestroyed(bool d) {
    destroyed = d;
}

// setters
void Ship::setCenterCarrier(int x,int y) {
    carrierShipTang.setCenter(x,y);
}

void Ship::setCenterDestroyer(int x,int y) {
    destroyerShipTang.setCenter(x,y);
}

void Ship::setCenterCruiser(int x,int y) {
    cruiserShipTang.setCenter(x,y);
}

void Ship::setCenterSub(int x,int y) {
    subShipTang.setCenter(x,y);
}

void Ship::setCenterBattle(int x,int y) {
    battleShipTang.setCenter(x,y);
}

void Ship::setCenterCarrier2(int x,int y) {
    carrierShipP2.setCenter(x,y);
}

void Ship::setCenterDestroyer2(int x,int y) {
    destroyerShipP2.setCenter(x,y);
}

void Ship::setCenterCruiser2(int x,int y) {
    cruiserShipP2.setCenter(x,y);
}

void Ship::setCenterSub2(int x,int y) {
    subShipP2.setCenter(x,y);
}

void Ship::setCenterBattle2(int x,int y) {
    battleShipP2.setCenter(x,y);
}

void Ship::setCenterY(int y) {
    shipCenter.y = y;
}

void Ship::addHit() {
    hits++;
}

void Ship::drawShip_car(){

//    carrierShip.setDimensions(30*l,30);
//    int xC = 100;
//    int yC = 470;
//    carrierShip.setCenter(xC, yC);
    carrierShipTang.setFillColor(0.4, 0.4, 0.4);
    carrierShipTang.draw();
}

void Ship::drawShip_battle(){

//    carrierShip.setDimensions(30*l,30);
//    int xC = 100;
//    int yC = 470;
//    carrierShip.setCenter(xC, yC);
    battleShipTang.setFillColor(0.4, 0.4, 0.4);
    battleShipTang.draw();
}

void Ship::drawShip_destroyer(){
    destroyerShipTang.setFillColor(0.4, 0.4, 0.4);
    destroyerShipTang.draw();
}
void Ship::drawShip_cruiser(){
    cruiserShipTang.setFillColor(0.4, 0.4, 0.4);
    cruiserShipTang.draw();
}
void Ship::drawShip_sub(){
    subShipTang.setFillColor(0.4, 0.4, 0.4);
    subShipTang.draw();
}

void Ship::drawShip_car2(){
    carrierShipP2.setFillColor(100,0,0);
    carrierShipP2.draw();
}

void Ship::drawShip_battle2(){
    battleShipP2.setFillColor(100,0,0);
    battleShipP2.draw();
}

void Ship::drawShip_destroyer2(){
    destroyerShipP2.setFillColor(100,0,0);
    destroyerShipP2.draw();
}
void Ship::drawShip_cruiser2(){
    cruiserShipP2.setFillColor(100,0,0);
    cruiserShipP2.draw();
}
void Ship::drawShip_sub2(){
    subShipP2.setFillColor(100,0,0);
    subShipP2.draw();
}