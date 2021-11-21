#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include "Board.h"
#include "GameMove.h"
#include "GamePiece.h"

class MoveSimulator {
    public:
        MoveSimulator(Board *board, std::map<std::string, std::string> metaData);
        void simulateMove(GameMove move);
        std::vector<GamePiece*> getWhitePieces();
        std::vector<GamePiece*> getBlackPieces();
    private:
        void setInitialPositions();
        void setInitialBoardPositions();
        void parseMove(std::string& move, bool color);
        PieceTypes getPieceType(char a);
        GamePiece* getPieceByFileAndRank(char file, int rank);
        std::vector<GamePiece*> whitePieces;
        std::vector<GamePiece*> blackPieces;
        Board *board;
};