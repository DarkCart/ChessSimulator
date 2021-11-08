#pragma once

#include <cmath>

class GamePiece {
    public:
        GamePiece(char file, int rank) {
            this -> file = file;
            this -> rank = rank;
        }
        bool canMove(char newFile, int newRank);
    protected:
        char file;
        int rank;
};

class Pawn : GamePiece {
    public:
        Pawn(char file, int rank) : GamePiece(file, rank) { }
        bool canMove(char newFile, int newRank) {
            if (file == newFile && newRank - rank < 3) {
                return true;
            }
            return false;
        }
};

class Knight : GamePiece {
    public:
        Knight(char file, int rank) : GamePiece(file, rank) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs(newFile - file);
            int rankDifference = std::abs((newRank - 97) - (rank - 97));

            if ((rankDifference >= 1 && rankDifference <= 2) && (fileDifference >= 1 && fileDifference <= 2)) {
                return true;
            }
            return false;
        }
};

class Bishop : GamePiece {
    public:
        Bishop(char file, int rank) : GamePiece(file, rank) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs(newFile - file);
            int rankDifference = std::abs((newRank - 97) - (rank - 97));
            if (fileDifference == rankDifference) {
                return true;
            }
            return false;
        }
};

class Rook : GamePiece {
    public:
        Rook(char file, int rank) : GamePiece(file, rank) { }
        bool canMove(char newFile, int newRank) {
            if (newFile == file || newRank == rank) {
                return true;
            }
            return false;
        }
};

class King : GamePiece {
    public:
        King(char file, int rank) : GamePiece(file, rank) { }
        bool canMove(char newFile, int newRank) {
            int fileDifference = std::abs(newFile - file);
            int rankDifference = std::abs((newRank - 97) - (rank - 97));

            if (fileDifference <= 1 && rankDifference <= 1) {
                return true;
            }
            return false;
        }
};

class Queen : GamePiece {
    public:
        Queen(char file, int rank) : GamePiece(file, rank) { }
        bool canMove(char newFile, int newRank) {
            Bishop temp_bishop(file, rank);
            Rook temp_rook(file, rank);
            King temp_king(file, rank);

            return temp_bishop.canMove(newFile, newRank) || temp_rook.canMove(newFile, newRank) || temp_king.canMove(newFile, newRank);
        }
};
