//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include <string>
#include "Fleet.h"


Fleet::Fleet(){
    carrier=Ship(5);
    carrier2=Ship(5);
    battleship=Ship(4);
    battleship2=Ship(4);
    destroyer=Ship(3);
    destroyer2=Ship(3);
    sub=Ship(3);
    sub2=Ship(3);
    cruiser=Ship(2);
    cruiser2=Ship(2);
}

void Fleet::setCarrier(Ship sh){
    carrier=sh;

}
void Fleet::setCruiser(Ship sh){
    cruiser=sh;
}
void Fleet::setSub(Ship sh){
    sub=sh;
}
void Fleet::setBattle(Ship sh){
    battleship=sh;
}
void Fleet::setDestroyer(Ship sh){
    destroyer=sh;
}

void Fleet::setCarrier2(Ship sh){
    carrier2=sh;

}
void Fleet::setCruiser2(Ship sh){
    cruiser2=sh;
}
void Fleet::setSub2(Ship sh){
    sub2=sh;
}
void Fleet::setBattle2(Ship sh){
    battleship2=sh;
}
void Fleet::setDestroyer2(Ship sh){
    destroyer2=sh;
}

void Fleet::setCarrierStatus(status carrierStatus){
    this->carrierStatus = carrierStatus;
}
status Fleet::getCarrierStatus(){
    return carrierStatus;
}

void Fleet::setBattleStatus(status battleStatus){
    this->battleStatus = battleStatus;
}
status Fleet::getBattleStatus(){
    return battleStatus;
}

void Fleet::setDestroyerStatus(status destroyerStatus){
    this->destroyerStatus = destroyerStatus;
}
status Fleet::getDestroyerStatus(){
    return destroyerStatus;
}

void Fleet::setSubStatus(status subStatus){
    this->subStatus = subStatus;
}
status Fleet::getSubStatus(){
    return subStatus;
}

void Fleet::setCruiserStatus(status cruiserStatus){
    this->cruiserStatus = cruiserStatus;
}
status Fleet::getCruiserStatus(){
    return cruiserStatus;
}

void Fleet::setCarrier2Status(status carrierStatus){
    carrier2Status = carrierStatus;
}
status Fleet::getCarrier2Status(){
    return carrier2Status;
}

void Fleet::setBattle2Status(status battleStatus){
    battle2Status = battleStatus;
}
status Fleet::getBattle2Status(){
    return battle2Status;
}

void Fleet::setDestroyer2Status(status destroyerStatus){
    destroyer2Status = destroyerStatus;
}
status Fleet::getDestroyer2Status(){
    return destroyer2Status;
}

void Fleet::setSub2Status(status subStatus){
    sub2Status = subStatus;
}
status Fleet::getSub2Status(){
    return sub2Status;
}

void Fleet::setCruiser2Status(status cruiserStatus){
    cruiser2Status = cruiserStatus;
}
status Fleet::getCruiser2Status(){
    return cruiser2Status;
}

void Fleet::updateShip(int ship) {
    switch(ship) {
        case 1:
            destroyer.addHit();
            break;
        case 2:
            sub.addHit();
            break;
        case 3:
            carrier.addHit();
            break;
        case 4:
            cruiser.addHit();
            break;
        case 5:
            battleship.addHit();
            break;
    }
}

void Fleet::updateShip2(int ship) {
    switch(ship) {
        case 1:
            destroyer2.addHit();
            break;
        case 2:
            sub2.addHit();
            break;
        case 3:
            carrier2.addHit();
            break;
        case 4:
            cruiser2.addHit();
            break;
        case 5:
            battleship2.addHit();
            break;
    }
}

bool Fleet::sunk() {
    return carrier.getDestroyed() &&
           battleship.getDestroyed() &&
           destroyer.getDestroyed() &&
           sub.getDestroyed() &&
           cruiser.getDestroyed();
}

bool Fleet::sunk2() {
    return carrier2.getDestroyed() &&
           battleship2.getDestroyed() &&
           destroyer2.getDestroyed() &&
           sub2.getDestroyed() &&
           cruiser2.getDestroyed();
}

Ship Fleet::getCarrier(){
    return carrier;
}
Ship Fleet::getBattle(){
    return battleship;
}

Ship Fleet::getCruiser(){
    return cruiser;
}

Ship Fleet::getDestroyer(){
    return destroyer;
}
Ship Fleet::getSub(){
    return sub;
}

Ship Fleet::getCarrier2(){
    return carrier2;
}
Ship Fleet::getBattle2(){
    return battleship2;
}

Ship Fleet::getCruiser2(){
    return cruiser2;
}

Ship Fleet::getDestroyer2(){
    return destroyer2;
}
Ship Fleet::getSub2(){
    return sub2;
}


void Fleet::dragCarrier(int x, int y) {
    carrier.setCenterCarrier(x,y);
//    carrier.setCenterY(y);
    carrier.drawShip_car();
}

void Fleet::dragBattle(int x, int y){
    battleship.setCenterBattle(x,y);
    battleship.drawShip_battle();
}

void Fleet::dragDestroyer(int x, int y){
   destroyer.setCenterDestroyer(x,y);
//    carrier.setCenterY(y);
    destroyer.drawShip_destroyer();
}

void Fleet::dragSub(int x, int y){
    sub.setCenterSub(x,y);
    sub.drawShip_sub();
}

void Fleet::dragCruiser(int x, int y){
    cruiser.setCenterCruiser(x,y);
    cruiser.drawShip_cruiser();
}

void Fleet::dragCarrier2(int x, int y) {
    carrier2.setCenterCarrier(x,y);
//    carrier.setCenterY(y);
    carrier2.drawShip_car();
}

void Fleet::dragBattle2(int x, int y){
    battleship2.setCenterBattle(x,y);
    battleship2.drawShip_battle();
}

void Fleet::dragDestroyer2(int x, int y){
    destroyer2.setCenterDestroyer(x,y);
//    carrier.setCenterY(y);
    destroyer2.drawShip_destroyer();
}

void Fleet::dragSub2(int x, int y){
    sub2.setCenterSub(x,y);
    sub2.drawShip_sub();
}

void Fleet::dragCruiser2(int x, int y){
    cruiser2.setCenterCruiser(x,y);
    cruiser2.drawShip_cruiser();
}