#pragma once
#include <vector>
#include <algorithm>
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
        void parseMove(std::string& move, bool color);
        PieceTypes getPieceType(char a);
        GamePiece* getPieceByFileAndRank(char file, int rank);
        std::vector<GamePiece*> whitePieces;
        std::vector<GamePiece*> blackPieces;
        Board *board;
};