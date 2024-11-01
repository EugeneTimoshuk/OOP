#include "ShipManager.h"

ShipManager::ShipManager(const std::vector<size_t>& shipSizes) {
    for (size_t size : shipSizes) {
        ships.push_back(Ship(size, Ship::Horizontal));  
    }
}

Ship& ShipManager::getShip(size_t index) {
    if (index >= ships.size()) {
        throw std::out_of_range("Неверный индекс корабля");
    }
    return ships[index];
}

bool ShipManager::allShipsDestroyed() const {
    for (const auto& ship : ships) {
        if (!ship.isDestroyed()) {
            return false;
        }
    }
    return true;
}
