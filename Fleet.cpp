//
// Created by Oliver Reckord Groten on 10/31/19.
//

#include <string>
#include "Fleet.h"

Fleet::Fleet() {}

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

bool Fleet::sunk() {
    return carrier.getDestroyed() &&
           battleship.getDestroyed() &&
           destroyer.getDestroyed() &&
           sub.getDestroyed() &&
           cruiser.getDestroyed();
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