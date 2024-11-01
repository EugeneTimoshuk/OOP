#include "BoardRenderer.h"

BoardRenderer::BoardRenderer(const GameBoard& board) : board(board) {}

void BoardRenderer::render() const {
    for (size_t y = 0; y < board.getHeight(); ++y) {
        for (size_t x = 0; x < board.getWidth(); ++x) {
            char symbol = getCellSymbol(board.getCellStatus(x, y));
            std::cout << symbol << ' ';
        }
        std::cout << std::endl;
    }
}

char BoardRenderer::getCellSymbol(GameBoard::CellStatus status) const {
    switch (status) {
        case GameBoard::Unknown: return '.';
        case GameBoard::Empty: return '~';
        case GameBoard::ShipCell: return 'S';
        default: return ' ';
    }
}
