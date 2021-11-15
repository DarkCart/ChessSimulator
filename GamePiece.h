#pragma once

#include <cmath>

enum PieceTypes {
    PAWN, KNIGHT, BISHOP, ROOK, KING, QUEEN, NONE
};

class GamePiece {
    public:
        GamePiece(char file, int rank, PieceTypes type) {
            this -> file = file;
            this -> rank = rank;
            this -> type = type;
        }

        int getFile() {
            return file;
        }

        int getRank() {
            return rank;
        }

        virtual bool canMove(char newFile, int newRank) = 0;

        PieceTypes getPieceType() {
            return type;
        }

        void setPosition(char file, int rank) {
            this->file = file;
            this->rank = rank;
        }
    protected:
        char file;
        int rank;
        PieceTypes type;
};

class Pawn : public GamePiece {
    public:
        Pawn(char file, int rank) : GamePiece(file, rank, PAWN) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs((newFile - 97) - (file - 97));
            int rankDifference = std::abs(newRank - rank);

            if (fileDifference <= 1 && rankDifference < 3) {
                return true;
            }
            return false;
        }
};

class Knight : public GamePiece {
    public:
        Knight(char file, int rank) : GamePiece(file, rank, KNIGHT) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs((newFile - 97) - (file - 97));
            int rankDifference = std::abs(newRank - rank);

            if ((rankDifference >= 1 && rankDifference <= 2) && (fileDifference >= 1 && fileDifference <= 2)) {
                return true;
            }
            return false;
        }
};

class Bishop : public GamePiece {
    public:
        Bishop(char file, int rank) : GamePiece(file, rank, BISHOP) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs((newFile - 97) - (file - 97));
            int rankDifference = std::abs(newRank - rank);
            if (fileDifference == rankDifference) {
                return true;
            }
            return false;
        }
};

class Rook : public GamePiece {
    public:
        Rook(char file, int rank) : GamePiece(file, rank, ROOK) { }
        bool canMove(char newFile, int newRank) {
            if (newFile == file || newRank == rank) {
                return true;
            }
            return false;
        }
};

class King : public GamePiece {
    public:
        King(char file, int rank) : GamePiece(file, rank, KING) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs((newFile - 97) - (file - 97));
            int rankDifference = std::abs(newRank - rank);

            if (fileDifference <= 1 && rankDifference <= 1) {
                return true;
            }
            return false;
        }
};

class Queen : public GamePiece {
    public:
        Queen(char file, int rank) : GamePiece(file, rank, QUEEN) { }
        bool canMove(char newFile, int newRank) {
            Bishop temp_bishop(file, rank);
            Rook temp_rook(file, rank);
            King temp_king(file, rank);

            return temp_bishop.canMove(newFile, newRank) || temp_rook.canMove(newFile, newRank) || temp_king.canMove(newFile, newRank);
        }
};
