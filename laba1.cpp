#include <iostream>
#include <vector>
#include <stdexcept>

class Ship {
public:
    enum SegmentState { Whole, Damage, Destroyed };
    enum Orientation { Horizontal, Vertical };

    Ship(size_t length, Orientation orientation)
        : length(length), orientation(orientation), segments(length, Whole) {
        validate(length);
    }

    size_t getLength() const {
        return length;
    }

    Orientation getOrientation() const {
        return orientation;
    }

    SegmentState getSegmentState(size_t index) const {
        checkIndex(index);
        return segments[index];
    }

    void hitSegment(size_t index) {
        checkIndex(index);
        if (segments[index] == Whole) {
            segments[index] = Damage;
        } else if (segments[index] == Damage) {
            segments[iчndex] = Destroyed;
        }
    }

    bool isDestroyed() const {
        for (const auto& segment : segments) {
            if (segment != Destroyed) {
                return false;
            }
        }
        return true;
    }

private:
    size_t length;
    Orientation orientation;
    std::vector<SegmentState> segments;

    static void validate(size_t length) {
        if (length < 1 || length > 4) {
            throw std::invalid_argument("Длина должна быть от 1 до 4");
        }
    }

    void checkIndex(size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Неверный индекс сегмента");
        }
    }
};

class ShipManager{
public:
	ShipManager(const std::vector<size_t>& shipSizes) {
	        initializeShips(shipSizes);
	    }
	
	void initializeShips(const std::vector<size_t>& shipSizes) {
	        for (size_t size : shipSizes) {
	            ships.push_back(Ship(size, Ship::Horizontal));
	        }
	    }

	Ship& getShip(size_t index){
		if (index>= ships.size()){
			throw std::out_of_range("Неверный индекс коробля");
		}
		return ships[index];
	}

	bool allShipsDestroyed() const{
		for (const auto& ship : ships){
			if (!ship.isDestroyed()){
				return false;
			}
		}
		return true;
	}

private:
	std::vector<Ship> ships;
};

class GameBoard {
public:
    enum CellStatus { Unknown, Empty, ShipCell };  

    GameBoard(size_t width, size_t height)
        : width(width), height(height), grid(height, std::vector<CellStatus>(width, Unknown)) {}
   
    CellStatus getCellStatus(size_t x, size_t y) const {
        if (x >= width || y >= height) {
            throw std::out_of_range("Неверные координаты");
        }
        return grid[y][x];
    }

    size_t getWidth() const {
        return width;
    }

    size_t getHeight() const {
        return height;
    }

    bool placeShip(Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) {
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

    bool attack(size_t x, size_t y) {
        if (grid[y][x] == ShipCell) {
            grid[y][x] = Empty;  
            return true;
        }
        grid[y][x] = Empty;  
        return false;
    }

    GameBoard(const GameBoard& other)
        : width(other.width), height(other.height), grid(other.grid) {}

    GameBoard(GameBoard&& other) noexcept
        : width(other.width), height(other.height), grid(std::move(other.grid)) {
        other.width = 0;
        other.height = 0;
    }

    GameBoard& operator=(const GameBoard& other) {
        if (this == &other) {
            return *this;
        }
        width = other.width;
        height = other.height;
        grid = other.grid;
        return *this;
    }

    GameBoard& operator=(GameBoard&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        width = other.width;
        height = other.height;
        grid = std::move(other.grid);
        other.width = 0;
        other.height = 0;
        return *this;
    }

private:
    size_t width, height;
    std::vector<std::vector<CellStatus>> grid;  

    bool canPlaceShip(const Ship& ship, size_t startX, size_t startY, Ship::Orientation orientation) const {
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
};

class BoardRenderer {
public:
    BoardRenderer(const GameBoard& board) : board(board) {}

    void render() const {
        for (size_t y = 0; y < board.getHeight(); ++y) {
            for (size_t x = 0; x < board.getWidth(); ++x) {
                char symbol = getCellSymbol(board.getCellStatus(x, y));
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;
        }   
    }

private:
    const GameBoard& board;

    char getCellSymbol(GameBoard::CellStatus status) const {
        switch (status) {
            case GameBoard::Unknown: return '.';
            case GameBoard::Empty: return '~';
            case GameBoard::ShipCell: return 'S';
            default: return ' ';
        }
    }
};


int main() {
    std::vector<size_t> shipSizes = {3, 2, 4};  
    ShipManager manager(shipSizes);

    GameBoard board(10, 10);


    Ship& ship1 = manager.getShip(0);
    if (!board.placeShip(ship1, 5, 5, Ship::Vertical)) {
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
