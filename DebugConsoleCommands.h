#include <string>
#include <vector>
#include <iostream>
#include "GamePiece.h"
#include "Utilities.h"

class DebugConsoleCommands {
    public:
        static void parseDebugCommand(std::string& line, std::vector<GamePiece*> whitePieces, std::vector<GamePiece*> blackPieces);
    private:
        static PieceTypes getPieceTypeByName(std::string& name);
};