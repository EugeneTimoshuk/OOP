#include "ShipManager.h"
#include "GameBoard.h"
#include "BoardRenderer.h"

int main() {
    std::vector<size_t> shipSizes = {3, 2, 4};  
    ShipManager manager(shipSizes);
    GameBoard board(10, 10);

    Ship& ship1 = manager.getShip(2);
    if (!board.placeShip(ship1, 5, 5, Ship::Vertical)) {
        std::cout << "Не удалось разместить корабль!" << std::endl;
    }
    Ship& ship2 = manager.getShip(1);
    if (!board.placeShip(ship2, 0, 0, Ship::Horizontal)) {
            std::cout << "Не удалось разместить корабль!" << std::endl;
        }
	
   	bool hit = board.attack(5, 7);
    if (hit) {
        std::cout << "Попал" << std::endl;
    } else {
        std::cout << "Мимо" << std::endl;
    }
	
    BoardRenderer renderer(board);
    std::cout << "Игровое поле: " << std::endl;
    renderer.render();

    return 0;
}
