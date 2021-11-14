#pragma once
#include <vector>
#include "Board.h"
#include "GameMove.h"
#include "GamePiece.h"

class MoveSimulator {
    public:
        MoveSimulator(Board *board);
        void simulateMove(GameMove move);
        std::vector<GamePiece*> getWhitePieces();
        std::vector<GamePiece*> getBlackPieces();
    private:
        void setInitialPositions();
        void updateBoard();
        void parseMove(std::string& move, std::vector<GamePiece*> pieces);
        PieceTypes getPieceType(char a);
        std::vector<GamePiece*> whitePieces;
        std::vector<GamePiece*> blackPieces;
        Board *board;
};