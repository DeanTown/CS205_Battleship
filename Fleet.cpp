#include "Fleet.h"
fleetStat Fleet::getFleetStat() const {
    return fs;
}
fleetStat Fleet::getAdditionStat() const {
    return fsA;
}

void Fleet::setFleetStat(fleetStat fs) {
    this->fs = fs;
}

void Fleet::setAdditionStat(fleetStat fs) {
    fsA = fs;
}
