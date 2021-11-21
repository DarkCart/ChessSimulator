#include "MoveSimulator.h"

int movesSuccessful = 0;

MoveSimulator::MoveSimulator(Board *board, std::map<std::string, std::string> metaData) {
    this -> board = board;
    setInitialPositions();

    std::cout << "White pieces: " << metaData.at("White") << std::endl;
    std::cout << "Black pieces: " << metaData.at("Black") << std::endl;
    
    board->drawBoard();
    std::cout << "Initial position" << std::endl;
    std::cin.ignore();
}

void MoveSimulator::simulateMove(GameMove move) {
    std::cout << "\033[2J";
    
    std::string white = move.getWhiteMove();
    std::string black = move.getBlackMove();

    parseMove(white, true);

    if (black.length() != 0) { // Depending on whose turn the game ends on, the final black move may not exist. Detect this and alert the user that we're at the end of the game.  
        parseMove(black, false);
    }

    board->drawBoard();
}

void MoveSimulator::parseMove(std::string&  move, bool color) {
    // Castling is basically a hard-coded move in Chess, the king and rooks can only be in one position for it to happen, so we can hardcode the board/piece movement
    if (move == "O-O") {
        GamePiece* castlingKing = getPieceByFileAndRank('e', color ? 1 : 8);
        GamePiece* castlingRook = getPieceByFileAndRank('h', color ? 1 : 8);

        std::cout << ((color) ? "White" : "Black") << " king castling king-side, ";
        if (color) {
            std::cout << "h1 -> f1, e1 -> g1";
        } else {
            std::cout << "h8 -> f8, e8 -> g8";
        }
        std::cout << std::endl;

        castlingRook->setPosition('f', castlingRook->getRank()); 
        castlingKing->setPosition('g', castlingKing->getRank());  
        board->moveCharacterOnBoard('h', color ? 1 : 8, 'f', color ? 1 : 8);
        board->moveCharacterOnBoard('e', color ? 1 : 8, 'g', color ? 1 : 8);
    } else if (move == "O-O-O") {
        GamePiece* castlingKing = getPieceByFileAndRank('e', color ? 1 : 8);
        GamePiece* castlingRook = getPieceByFileAndRank('a', color ? 1 : 8);

        std::cout << ((color) ? "White" : "Black") << " king castling queen-side, ";
        if (color) {
            std::cout << "a1 -> d1, e1 -> c1";
        } else {
            std::cout << "a8 -> d8, e8 -> c8";
        }
        std::cout << std::endl;

        castlingRook->setPosition('d', castlingRook->getRank()); 
        castlingKing->setPosition('c', castlingKing->getRank());
        board->moveCharacterOnBoard('a', color ? 1 : 8, 'd', color ? 1 : 8);
        board->moveCharacterOnBoard('e', color ? 1 : 8, 'c', color ? 1 : 8);  
    } else {
        // Otherwise, we can fall back on our standard dissection of the move
        PieceTypes targetPieceType = getPieceType(move[0]); // Identify the target type - in other words, look at the first char and determine what piece we're moving
        GamePiece* pieceToMove = nullptr; // Placeholder for the piece that will be moved

        char targetFile;
        int targetRank;
        bool capturing = false, specificFile = false;

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

        if (move.length() == 4 && (move[1] >= 'a' && move[1] <= 'h') && move[move.length() - 1] != '+') { // Find out if the move specifies a certain file that the piece has to come from
            specificFile = true;
            std::cout << "Specific file" << std::endl;
        }

        for (GamePiece *piece: ((color) ? whitePieces: blackPieces)) { // Loop through the pieces dependent on which color is moving
            if (piece->getPieceType() == PAWN && capturing && piece->getFile() == move[0]) { // Special case for capturing pawn, make sure we're in the right file, then calculate if it's a legal move
                int fileDifference = std::abs(((targetFile - 'a') - (piece->getFile() - 'a')));
                int rankDifference = std::abs(targetRank - piece->getRank());
                //std::cout << "Pawn at " << piece->getFile() << piece->getRank() << " is " << fileDifference << " " << rankDifference << std::endl;
                if (fileDifference <= 1 && rankDifference <= 2) { // Special case for pawns that are capturing, as they can move files while normal pawns can't
                    pieceToMove = piece;
                    //std::cout << "[pawn capturing] Could move from " << piece->getFile() << piece->getRank() << " to " << targetFile << targetRank << std::endl;
                    break; // If we find a pawn that can capture legally in the correct file, we're done. Break out of the loop.
                }
            } else if (piece->getPieceType() == targetPieceType && piece->canMove(targetFile, targetRank)) { // If we're not a capturing pawn, we can just rely on the canMove methods
                if (specificFile && piece->getFile() == move[1] || !specificFile) { // Well, almost. If the piece has to come from a specific file according to the move, ensure that is so. Otherwise, all's fair.
                    pieceToMove = piece;
                    //std::cout << "Could move from " << piece->getFile() << piece->getRank() << " to " << targetFile << targetRank << std::endl;
                }
            }

        }

        if (pieceToMove == nullptr) {
            std::cout << "COULD NOT FIND PIECE TO MOVE" << std::endl;
            std::exit(-1); // Safeguard, prevents SEGFAULT from an undefined pointer. Basically, if we've gotten through all the pieces without finding anything that can move, we're in trouble.
        }


        std::cout << (color ? "White" : "Black") << ": " << pieceToMove->getFile() << pieceToMove->getRank() << " -> " << targetFile << targetRank << std::endl;
        
        
        if (capturing) { // If we're capturing, remove the target piece. If it's a white move, remove the corresponding black piece, and vice-versa.
            //std::cout << "Size before capture " << whitePieces.size() << " " << blackPieces.size() << std::endl;
            if (color) {
                blackPieces.erase(std::remove(blackPieces.begin(), blackPieces.end(), getPieceByFileAndRank(targetFile, targetRank)), blackPieces.end());
            } else {
                whitePieces.erase(std::remove(whitePieces.begin(), whitePieces.end(), getPieceByFileAndRank(targetFile, targetRank)), whitePieces.end());
            }
            //std::cout << "Size after capture " << whitePieces.size() << " " << blackPieces.size() << std::endl;
        }

        // Update our positions on the board and in the piece vectors
        board->moveCharacterOnBoard(pieceToMove->getFile(), pieceToMove->getRank(), targetFile, targetRank);
        pieceToMove->setPosition(targetFile, targetRank);
    }
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

    setInitialBoardPositions();
}

void MoveSimulator::setInitialBoardPositions() {
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