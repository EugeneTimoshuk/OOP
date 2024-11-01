#ifndef BOARDRENDERER_H
#define BOARDRENDERER_H

#include <iostream>
#include "GameBoard.h"

class BoardRenderer {
public:
    BoardRenderer(const GameBoard& board);
    void render() const;

private:
    const GameBoard& board;
    char getCellSymbol(GameBoard::CellStatus status) const;
};

#endif
