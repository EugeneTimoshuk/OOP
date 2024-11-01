#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "ShipManager.h"

class GameBoard {
public:
    enum CellStatus { Unknown, Empty, ShipCell };  

    GameBoard(size_t width, size_t height);
    CellStatus getCellStatus(size_t x, size_t y) const;
    size_t getWidth() const;
    size_t getHeight() const;
    bool placeShip(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation);
    bool attack(size_t x, size_t y);

private:
    size_t width, height;
    std::vector<std::vector<CellStatus>> grid;  

    bool canPlaceShip(const Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) const;
};

#endif
