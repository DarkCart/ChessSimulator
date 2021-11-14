#include "DebugConsoleCommands.h"

void DebugConsoleCommands::parseDebugCommand(std::string& line, std::vector<GamePiece*> whitePieces, std::vector<GamePiece*> blackPieces) {
    std::vector<std::string> commandParts = Utilities::splitString(line, " ");
    PieceTypes targetType;

    if (commandParts.at(0) == "position") {
        targetType = DebugConsoleCommands::getPieceTypeByName(commandParts[2]);

        if (commandParts[1] == "white") {
            for (GamePiece *piece: whitePieces) {
                if (piece->getPieceType() == targetType) {
                    std::cout << "[debug] " << commandParts[1] << " " << commandParts[2] << " at " << (char)piece->getFile() << piece->getRank() << std::endl;
                }
            }
        } else if (commandParts[1] == "black") {
            for (GamePiece *piece: blackPieces) {
                if (piece->getPieceType() == targetType) {
                    std::cout << "[debug] " << commandParts[1] << " " << commandParts[2] << " at " << (char)piece->getFile() << piece->getRank() << std::endl;
                }
            }
        }
 
    }
}

PieceTypes DebugConsoleCommands::getPieceTypeByName(std::string& name) {
    if (name == "queen") {
        return QUEEN;
    } else if (name == "king") {
        return KING;
    } else if (name == "bishop") {
        return BISHOP;
    } else if (name == "rook") {
        return ROOK;
    } else if (name == "knight") {
        return KNIGHT;
    } else if (name == "pawn") {
        return PAWN;
    }
    return NONE;
}