#include "MoveSimulator.h"

MoveSimulator::MoveSimulator(Board *board) {
    this -> board = board;
    setInitialPositions();

    updateBoard();
    board->drawBoard();
}

void MoveSimulator::simulateMove(GameMove move) {

}

void MoveSimulator::setInitialPositions() {
    for (int i = 'a'; i <= 'h'; i++) {
        whitePieces.push_back(Pawn(i, 2));
        blackPieces.push_back(Pawn(i, 7));
    }

    whitePieces.push_back(Rook('a', 1));
    whitePieces.push_back(Rook('h', 1));
    blackPieces.push_back(Rook('a', 8));
    blackPieces.push_back(Rook('h', 8));

    whitePieces.push_back(Knight('b', 1));
    whitePieces.push_back(Knight('g', 1));
    blackPieces.push_back(Knight('b', 8));
    blackPieces.push_back(Knight('g', 8));

    whitePieces.push_back(Bishop('c', 1));
    whitePieces.push_back(Bishop('f', 1));
    blackPieces.push_back(Bishop('c', 8));
    blackPieces.push_back(Bishop('f', 8));

    whitePieces.push_back(Queen('d', 1));
    whitePieces.push_back(King('e', 1));
    blackPieces.push_back(Queen('d', 8));
    blackPieces.push_back(King('e', 8));
}

void MoveSimulator::updateBoard() {
    for (GamePiece piece : whitePieces) {
        char characterToBePlaced = ' ';
        if (piece.getPieceType() == PAWN) {
            characterToBePlaced = 'p';
        } else if (piece.getPieceType() == ROOK) {
            characterToBePlaced = 'R';
        } else if (piece.getPieceType() == KNIGHT) {
            characterToBePlaced = 'N';
        } else if (piece.getPieceType() == BISHOP) {
            characterToBePlaced = 'B';
        } else if (piece.getPieceType() == KING) {
            characterToBePlaced = 'K';
        } else if (piece.getPieceType() == QUEEN) {
            characterToBePlaced = 'Q';
        }
        board->setCharacterOnBoard(piece.getFile(), piece.getRank(), characterToBePlaced, board->WHITE);
    }

    for (GamePiece piece : blackPieces) {
        char characterToBePlaced = ' ';
        if (piece.getPieceType() == PAWN) {
            characterToBePlaced = 'p';
        } else if (piece.getPieceType() == ROOK) {
            characterToBePlaced = 'R';
        } else if (piece.getPieceType() == KNIGHT) {
            characterToBePlaced = 'N';
        } else if (piece.getPieceType() == BISHOP) {
            characterToBePlaced = 'B';
        } else if (piece.getPieceType() == KING) {
            characterToBePlaced = 'K';
        } else if (piece.getPieceType() == QUEEN) {
            characterToBePlaced = 'Q';
        }
        board->setCharacterOnBoard(piece.getFile(), piece.getRank(), characterToBePlaced, board->BLACK);
    }
}