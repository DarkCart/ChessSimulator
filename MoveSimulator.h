#pragma once
#include <vector>
#include "Board.h"
#include "GameMove.h"
#include "GamePiece.h"

class MoveSimulator {
    public:
        MoveSimulator(Board *board);
        void simulateMove(GameMove move);
    private:
        void setInitialPositions();
        std::vector<GamePiece> whitePieces;
        std::vector<GamePiece> blackPieces;
        Board *board;
};