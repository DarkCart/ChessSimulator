#include "MoveSimulator.h"

int movesSuccessful = 0;

MoveSimulator::MoveSimulator(Board *board) {
    this -> board = board;
    setInitialPositions();

    updateBoard();
    board->drawBoard();
    std::cout << "Initial position" << std::endl;
}

void MoveSimulator::simulateMove(GameMove move) {
    std::string white = move.getWhiteMove();
    std::string black = move.getBlackMove();

    parseMove(white, true);

    if (black.length() == 0) {
        std::cout << "End of game!" << std::endl;
    } else {
        parseMove(black, false);
    }

    //board->drawBoard();
    //std::cout << "Successful game moves: " << movesSuccessful << std::endl;
}

void MoveSimulator::parseMove(std::string&  move, bool color) {
    if (move == "O-O") {
        // king-side castling, handle this later
    } else if (move == "O-O-O") {
        // queen-side castling
    } else {
        // Otherwise, we can fall back on our standard dissection of the move
        PieceTypes targetPieceType = getPieceType(move[0]); // Identify the target type - in other words, look at the first char and determine what piece we're moving
        GamePiece* pieceToMove = nullptr; // Placeholder for the piece that will be moved

        //std::cout << targetPieceType << std::endl;

        char targetFile;
        int targetRank;
        bool capturing = false;

        if (move[move.length() - 1] != '+') { // Identify where we're going to, this is usually the last two characters of the move, unless there's a check.
            targetRank = move[move.length() - 1] - '0';
            targetFile = move[move.length() - 2];
        } else {
            targetRank = move[move.length() - 2] - '0';
            targetFile = move[move.length() - 3];
        }

        if (move.find('x') != std::string::npos) { // Find out if we're capturing or not, as this changes the behavior of the pawn
            capturing = true;
        }

        //std::cout << targetFile << targetRank << std::endl;

        for (GamePiece *piece: ((color) ? whitePieces: blackPieces)) { // Loop through the pieces dependent on which color is moving
            if (piece->getPieceType() == PAWN && capturing) {
                int fileDifference = std::abs(((targetFile - 'a') - (piece->getFile() - 'a')));
                int rankDifference = std::abs(targetRank - piece->getRank());
                //std::cout << "Pawn at " << piece->getFile() << piece->getRank() << " is " << fileDifference << " " << rankDifference << std::endl;
                if (fileDifference <= 1 && rankDifference <= 2) { // Special case for pawns that are capturing, as they can move files while normal pawns can't
                    pieceToMove = piece;
                    break;
                }
            } else if (piece->getPieceType() == targetPieceType && piece->canMove(targetFile, targetRank)) { // If we're not a capturing pawn, we can just rely on the canMove methods
                pieceToMove = piece;
                break;
            }
        }

        if (pieceToMove == nullptr) {
            std::cout << "COULD NOT FIND PIECE TO MOVE" << std::endl;
            std::exit(-1);
        }

        std::cout << "Possible " << (color ? "white" : "black") << " move: " << pieceToMove->getFile() << pieceToMove->getRank() << " -> " << targetFile << targetRank << std::endl;
        
        
        if (capturing) {
            std::cout << "Size before capture " << whitePieces.size() << " " << blackPieces.size() << std::endl;
            if (color) {
                blackPieces.erase(std::remove(blackPieces.begin(), blackPieces.end(), getPieceByFileAndRank(targetFile, targetRank)), blackPieces.end());
            } else {
                whitePieces.erase(std::remove(whitePieces.begin(), whitePieces.end(), getPieceByFileAndRank(targetFile, targetRank)), whitePieces.end());
            }
            std::cout << "Size after capture " << whitePieces.size() << " " << blackPieces.size() << std::endl;
        }
        
        pieceToMove->setPosition(targetFile, targetRank);
    }
    /*
    PieceTypes targetPieceType = getPieceType(move[0]);
    int moveLength = move.length();

    bool lock = false;
    int oldSize, newSize;

    for (GamePiece *piece : pieces) {
        if (piece->getPieceType() == targetPieceType) {
            int destinationFileIndex, destinationRankIndex;

            //std::cout << "0: " << move[0] << " 1: " << move[1] << " 2: " << move[2] << " 3: " << move[3] << std::endl;
            switch (moveLength) {
                case 2:
                    destinationFileIndex = 0;
                    destinationRankIndex = 1;
                    break;
                case 3:
                    destinationFileIndex = 1;
                    destinationRankIndex = 2;
                    break;
                case 4:
                    destinationFileIndex = 2;
                    destinationRankIndex = 3;
                    break;
            }

            char destinationFile = move[destinationFileIndex];
            int destinationRank = move[destinationRankIndex];

            destinationRank -= 48;

            //std::cout << destinationFile << destinationRank << std::endl;

            if (piece->canMove(destinationFile, destinationRank)) {
                //std::cout << "found piece for move at " << (char)piece->getFile() << piece->getRank() << std::endl;
                if (move[1] == 'x') {
                    oldSize = whitePieces.size() + blackPieces.size();
                    //std::cout << getPieceAtFileAndRank(destinationFile, destinationRank, blackPieces)->getPieceType() << std::endl;

                    GamePiece *temp = getPieceAtFileAndRank(destinationFile, destinationRank, whitePieces);
                    GamePiece *temp2 = getPieceAtFileAndRank(destinationFile, destinationRank, blackPieces);

                    if (temp != nullptr) {
                        whitePieces.erase(std::remove(whitePieces.begin(), whitePieces.end(), temp), whitePieces.end());
                    } else if (temp2 != nullptr) {
                        blackPieces.erase(std::remove(blackPieces.begin(), blackPieces.end(), temp), blackPieces.end());
                    }
                    
                    newSize = whitePieces.size() + blackPieces.size();

                    if (oldSize == newSize) {
                        std::cout << "Error, piece at " << (char) destinationFile << destinationRank << " should have been removed but was not!" << std::endl;
                    } else {
                        std::cout << "Piece at " << (char) destinationFile << destinationRank << " successfully removed" << std::endl;
                    }
                }
                board->moveCharacterOnBoard(piece->getFile(), piece->getRank(), destinationFile, destinationRank);
                piece->setPosition(destinationFile, destinationRank);
                movesSuccessful++;
            }

        }
    }
    */
}

PieceTypes MoveSimulator::getPieceType(char a) {
    switch (a) {
        case 'K':
            return KING;
        case 'Q':
            return QUEEN;
        case 'B':
            return BISHOP;
        case 'R':
            return ROOK;
        case 'N':
            return KNIGHT;
        default:
            return PAWN;
    }
}

void MoveSimulator::setInitialPositions() {
    for (int i = 'a'; i <= 'h'; i++) {
        whitePieces.push_back(new Pawn(i, 2));
        blackPieces.push_back(new Pawn(i, 7));
    }

    whitePieces.push_back(new Rook('a', 1));
    whitePieces.push_back(new Rook('h', 1));
    blackPieces.push_back(new Rook('a', 8));
    blackPieces.push_back(new Rook('h', 8));

    whitePieces.push_back(new Knight('b', 1));
    whitePieces.push_back(new Knight('g', 1));
    blackPieces.push_back(new Knight('b', 8));
    blackPieces.push_back(new Knight('g', 8));

    whitePieces.push_back(new Bishop('c', 1));
    whitePieces.push_back(new Bishop('f', 1));
    blackPieces.push_back(new Bishop('c', 8));
    blackPieces.push_back(new Bishop('f', 8));

    whitePieces.push_back(new Queen('d', 1));
    whitePieces.push_back(new King('e', 1));
    blackPieces.push_back(new Queen('d', 8));
    blackPieces.push_back(new King('e', 8));
}

void MoveSimulator::updateBoard() {
    for (GamePiece *piece: whitePieces) {
        char characterToBePlaced = ' ';
        if (piece->getPieceType() == PAWN) {
            characterToBePlaced = 'p';
        } else if (piece->getPieceType() == ROOK) {
            characterToBePlaced = 'R';
        } else if (piece->getPieceType() == KNIGHT) {
            characterToBePlaced = 'N';
        } else if (piece->getPieceType() == BISHOP) {
            characterToBePlaced = 'B';
        } else if (piece->getPieceType() == KING) {
            characterToBePlaced = 'K';
        } else if (piece->getPieceType() == QUEEN) {
            characterToBePlaced = 'Q';
        }
        board->setCharacterOnBoard(piece->getFile(), piece->getRank(), characterToBePlaced, board->WHITE);
    }

    for (GamePiece *piece : blackPieces) {
        char characterToBePlaced = ' ';
        if (piece->getPieceType() == PAWN) {
            characterToBePlaced = 'p';
        } else if (piece->getPieceType() == ROOK) {
            characterToBePlaced = 'R';
        } else if (piece->getPieceType() == KNIGHT) {
            characterToBePlaced = 'N';
        } else if (piece->getPieceType() == BISHOP) {
            characterToBePlaced = 'B';
        } else if (piece->getPieceType() == KING) {
            characterToBePlaced = 'K';
        } else if (piece->getPieceType() == QUEEN) {
            characterToBePlaced = 'Q';
        }
        board->setCharacterOnBoard(piece->getFile(), piece->getRank(), characterToBePlaced, board->BLACK);
    }
}

std::vector<GamePiece*> MoveSimulator::getWhitePieces() {
    return whitePieces;
 }
 
std::vector<GamePiece*> MoveSimulator::getBlackPieces() {
    return blackPieces;
 }

GamePiece* MoveSimulator::getPieceByFileAndRank(char file, int rank) {
    for (GamePiece *piece: whitePieces) {
        if (piece->getFile() == file && piece->getRank() == rank) {
            return piece;
        }
    }

    for (GamePiece *piece: blackPieces) {
        if (piece->getFile() == file && piece->getRank() == rank) {
            return piece;
        }
    }

    return nullptr;
}