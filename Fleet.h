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

    status carrier2Status;
    status battle2Status;
    status cruiser2Status;
    status sub2Status;
    status destroyer2Status;

    Ship carrier2;
    Ship battleship2;
    Ship destroyer2;
    Ship sub2;
    Ship cruiser2;

public:


    // GETTERS
    Ship getCarrier();
    Ship getBattle();
    Ship getDestroyer();
    Ship getSub();
    Ship getCruiser();

    Ship getCarrier2();
    Ship getBattle2();
    Ship getDestroyer2();
    Ship getSub2();
    Ship getCruiser2();
    // SETTERS
    void setCarrier(Ship sh);
    void setCruiser(Ship sh);
    void setSub(Ship sh);
    void setBattle(Ship sh);
    void setDestroyer(Ship sh);

    void setCarrier2(Ship sh);
    void setCruiser2(Ship sh);
    void setSub2(Ship sh);
    void setBattle2(Ship sh);
    void setDestroyer2(Ship sh);


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

    void setCarrier2Status(status carrierStatus);
    status getCarrier2Status();

    void setBattle2Status(status battleStatus);
    status getBattle2Status();

    void setDestroyer2Status(status destroyerStatus);
    status getDestroyer2Status();

    void setSub2Status(status subStatus);
    status getSub2Status();

    void setCruiser2Status(status cruiserStatus);
    status getCruiser2Status();

    Fleet();
    // updates ship with correct number of hits
    void updateShip(int ship);
    void updateShip2(int ship);
    // methods to check if fleet is sunk (win condition)
    bool sunk();
    bool sunk2();
    // methods to handle dragging for the GUI
    void dragCarrier(int x, int y);
    void dragBattle(int x, int y);
    void dragDestroyer(int x, int y);
    void dragSub(int x, int y);
    void dragCruiser(int x, int y);

    void dragCarrier2(int x, int y);
    void dragBattle2(int x, int y);
    void dragDestroyer2(int x, int y);
    void dragSub2(int x, int y);
    void dragCruiser2(int x, int y);
};


#endif //CS205_FINAL_PROJECT_FLEET_H
