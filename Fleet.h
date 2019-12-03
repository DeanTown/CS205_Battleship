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
public:
    Ship carrier = Ship(5);
    Ship battleship = Ship(4);
    Ship destroyer = Ship(3);
    Ship sub = Ship(3);
    Ship cruiser = Ship(2);

    Ship getCarrier();

    void setCarrierStatus(status carrierStatus);
    status getCarrierStatus();

    Fleet();
    void updateShip(int ship);
    bool sunk();
    void drag(int x, int y);
};


#endif //CS205_FINAL_PROJECT_FLEET_H
