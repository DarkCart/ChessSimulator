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

    parseMove(white, whitePieces);

    if (black.length() == 0) {
        std::cout << "End of game!" << std::endl;
    } else {
        parseMove(black, blackPieces);
    }

    board->drawBoard();
    std::cout << "Successful game moves: " << movesSuccessful << std::endl;
}

void MoveSimulator::parseMove(std::string&  move, std::vector<GamePiece*> pieces) {
    PieceTypes targetPieceType = getPieceType(move[0]);
    int moveLength = move.length();

    bool lock = false;

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

            if (piece->canMove(destinationFile, destinationRank) && !lock) {
                std::cout << "found piece for move at " << (char)piece->getFile() << piece->getRank() << std::endl;
                board->moveCharacterOnBoard(piece->getFile(), piece->getRank(), destinationFile, destinationRank);
                piece->setPosition(destinationFile, destinationRank);
                movesSuccessful++;
                lock = true;
            }

        }
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