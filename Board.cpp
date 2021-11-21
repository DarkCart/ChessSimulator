#include "Board.h"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[j][i] = ' ';
            colors[j][i] = 0;
        }
    }
}

void Board::drawBoard() {
    std::cout << " a b c d e f g h" << std::endl;
    std::cout << "┏━┳━┳━┳━┳━┳━┳━┳━┓" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "┃";
        for (int j = 0; j < 8; j++) {
            std::string ansi_string = "";
            bool darkSquare = false;

            if ((i + j) % 2) {
                darkSquare = true;
            }

            ansi_string += (darkSquare) ? "\x1b[41" : "\x1b[101";
            
            if (colors[j][i] != 0) {
                ansi_string += ";" + std::to_string(colors[j][i]);
            } else {
                ansi_string += (darkSquare) ? ";31" : ";91";
            }
            
            ansi_string += "m";
            std::cout << ansi_string << board[j][i] << "\x1b[0m┃";
        }
        std::cout << " " << (9 - (i + 1)) << std::endl;
    }
    std::cout << "┗━┻━┻━┻━┻━┻━┻━┻━┛" << std::endl;
}

void Board::setCharacterOnBoard(char file, int rank, char newChar, int color) {
    board[file - 97][convertRankToIndex(rank)] = newChar;
    colors[file - 97][convertRankToIndex(rank)] = color;
}

void Board::moveCharacterOnBoard(char oldFile, int oldRank, char newFile, int newRank) {
    char tempChar = board[oldFile - 97][convertRankToIndex(oldRank)];
    int tempColor = colors[oldFile - 97][convertRankToIndex(oldRank)];

    board[oldFile - 97][convertRankToIndex(oldRank)] = ' ';
    colors[oldFile - 97][convertRankToIndex(oldRank)] = TRANSPARENT;

    board[newFile - 97][convertRankToIndex(newRank)] = tempChar;
    colors[newFile - 97][convertRankToIndex(newRank)] = tempColor;
}

int Board::convertRankToIndex(int rank) {
    if (rank > 4) {
        return rank - ((rank - 4) * 2);
    }
    if (rank < 4) {
        return rank + (4 - rank) * 2;
    }
    return rank;
}