#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include "Ship.h"

class ShipManager {
public:
    ShipManager(const std::vector<size_t>& shipSizes);

    Ship& getShip(size_t index);
    bool allShipsDestroyed() const;

private:
    std::vector<Ship> ships;
};

#endif
