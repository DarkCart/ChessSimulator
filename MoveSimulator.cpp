#include "MoveSimulator.h"

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
    parseMove(black, blackPieces);
    //board->drawBoard();
}

void MoveSimulator::parseMove(std::string&  move, std::vector<GamePiece*> pieces) {
    PieceTypes targetPieceType = getPieceType(move[0]);
    for (GamePiece *piece : pieces) {
        if (piece->getPieceType() == targetPieceType) {
            char destinationFile = move[1];
            int destinationRank = move[2];
            //std::cout << "0: " << move[0] << " 1: " << move[1] << " 2: " << move[2] << " 3: " << move[3] << std::endl;
            
            if (targetPieceType == PAWN) {
                destinationFile = move[0];
                destinationRank = move[1];
            }
            if (move[1] == 'x') {
                destinationFile = move[2];
                destinationRank = move[3];
            }

            destinationRank -= 48;

            //std::cout << destinationFile << destinationRank << std::endl;

            if (piece->canMove(destinationFile, destinationRank)) {
                std::cout << "found piece for move at " << (char)piece->getFile() << piece->getRank() << std::endl;
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