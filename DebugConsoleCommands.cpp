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

    if (commandParts.at(0) == "can") { // can pawn move e2 e4
        std::string from = commandParts.at(3);
        char fromFile = from[0];
        int fromRank = from[1] - '0';

        std::string to = commandParts.at(4);
        char toFile = to[0];
        int toRank = to[1] - '0';

        GamePiece *temp;
        switch (getPieceTypeByName(commandParts.at(1))) {
            case QUEEN:
                temp = new Queen(fromFile, fromRank);
                break;
            case KING:
                temp = new King(fromFile, fromRank);
                break;
            case BISHOP:
                temp = new Bishop(fromFile, fromRank);
                break;
            case ROOK:
                temp = new Rook(fromFile, fromRank);
                break;
            case KNIGHT:
                temp = new Knight(fromFile, fromRank);
                break;
            case PAWN:
                temp = new Pawn(fromFile, fromRank);
                break;
        }

        std::cout << commandParts.at(1) << ((temp->canMove(toFile, toRank) == true) ? " can " : " CANNOT ") << "move from " << from << " to " << to << std::endl;
        delete temp;
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