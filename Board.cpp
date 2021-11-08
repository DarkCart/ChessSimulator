#include "Board.h"

#define TRANSPARENT 0
#define WHITE 97
#define BLACK 30

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[j][i] = ' ';
            colors[j][i] = 0;
        }
    }

    setCharacterOnBoard('a', 1, 'p', WHITE);
    setCharacterOnBoard('a', 2, 'K', BLACK);

    moveCharacterOnBoard('a', 1, 'b', 1);
}

void Board::drawBoard() {
    std::cout << " a b c d e f g h" << std::endl;
    std::cout << "┏━┳━┳━┳━┳━┳━┳━┳━┓" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "┃";
        for (int j = 0; j < 8; j++) {
            std::string ansi_string = "";
            bool darkSquare = false;

            if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
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
        std::cout << " " << (i + 1) << std::endl;
    }
    std::cout << "┗━┻━┻━┻━┻━┻━┻━┻━┛" << std::endl;
}

void Board::setCharacterOnBoard(char file, int rank, char newChar, int color) {
    board[file - 97][rank - 1] = newChar;
    colors[file - 97][rank - 1] = color;
}

void Board::moveCharacterOnBoard(char oldFile, int oldRank, char newFile, int newRank) {
    char tempChar = board[oldFile - 97][oldRank - 1];
    int tempColor = colors[oldFile - 97][oldRank - 1];

    board[oldFile - 97][oldRank - 1] = ' ';
    colors[oldFile - 97][oldRank - 1] = TRANSPARENT;

    board[newFile - 97][newRank - 1] = tempChar;
    colors[newFile - 97][newRank - 1] = tempColor;
}