//
// Created by Oliver Reckord Groten on 10/31/19.
//

#ifndef CS205_FINAL_PROJECT_FLEET_H
#define CS205_FINAL_PROJECT_FLEET_H

#include "Ship.h"
using namespace std;

enum status{selected, unselected};
class Fleet {
private:
//    Ship carrier = Ship(5);
//    Ship battleship = Ship(4);
//    Ship destroyer = Ship(3);
//    Ship sub = Ship(3);
//    Ship cruiser = Ship(2);
    status carrierStatus;
    status battleStatus;
    status cruiserStatus;
    status subStatus;
    status destroyerStatus;

    Ship carrier;
    Ship battleship;
    Ship destroyer;
    Ship sub;
    Ship cruiser;

public:



    Ship getCarrier();
    Ship getBattle();
    Ship getDestroyer();
    Ship getSub();
    Ship getCruiser();

    void setCarrier(Ship sh);
    void setCruiser(Ship sh);
    void setSub(Ship sh);
    void setBattle(Ship sh);
    void setDestroyer(Ship sh);


    void setCarrierStatus(status carrierStatus);
    status getCarrierStatus();

    void setBattleStatus(status battleStatus);
    status getBattleStatus();

    void setDestroyerStatus(status destroyerStatus);
    status getDestroyerStatus();

    void setSubStatus(status subStatus);
    status getSubStatus();

    void setCruiserStatus(status cruiserStatus);
    status getCruiserStatus();

    Fleet();

    void updateShip(int ship);
    bool sunk();
    void dragCarrier(int x, int y);
    void dragBattle(int x, int y);
    void dragDestroyer(int x, int y);
    void dragSub(int x, int y);
    void dragCruiser(int x, int y);
};


#endif //CS205_FINAL_PROJECT_FLEET_H
