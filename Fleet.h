#ifndef CS205_FINALPROJECT_FLEET_H
#define CS205_FINALPROJECT_FLEET_H

enum fleetStat{moveable,selected,placed,StoM,placedHo,placedVe,ready,No,addNull};
class Fleet {
private:
    fleetStat fs, fsA;
public:
    fleetStat getFleetStat() const;
    fleetStat getAdditionStat() const;
    void setFleetStat(fleetStat fs);
    void setAdditionStat(fleetStat fs);
};


#endif //CS205_FINALPROJECT_FLEET_H
