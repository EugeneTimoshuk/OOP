#include "GameBoard.h"

GameBoard::GameBoard(size_t width, size_t height)
    : width(width), height(height), grid(height, std::vector<CellStatus>(width, Unknown)) {}

GameBoard::CellStatus GameBoard::getCellStatus(size_t x, size_t y) const {
    if (x >= width || y >= height) {
        throw std::out_of_range("Неверные координаты");
    }
    return grid[y][x];
}

size_t GameBoard::getWidth() const {
    return width;
}

size_t GameBoard::getHeight() const {
    return height;
}

bool GameBoard::placeShip(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) {
    if (!canPlaceShip(ship, startX, startY, orientation)) {
        return false;  
    }
    size_t length = ship.getLength();
    for (size_t i = 0; i < length; ++i) {
        if (orientation == Ship::Horizontal) {
            grid[startY][startX + i] = ShipCell;
        } else {
            grid[startY + i][startX] = ShipCell;
        }
    }
    return true;
}

bool GameBoard::attack(size_t x, size_t y) {
    if (grid[y][x] == ShipCell) {
        grid[y][x] = Empty;  
        return true;
    }
    grid[y][x] = Empty;  
    return false;
}

bool GameBoard::canPlaceShip(const Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) const {
    size_t length = ship.getLength();
    if (orientation == Ship::Horizontal) {
        if (startX + length > width) return false;
        for (size_t i = 0; i < length; ++i) {
            if (grid[startY][startX + i] != Unknown) return false;
        }
    } else {
        if (startY + length > height) return false;
        for (size_t i = 0; i < length; ++i) {
            if (grid[startY + i][startX] != Unknown) return false;
        }
    }
    return true;
}
