#include "Board.h"

#define TRANSPARENT 0
#define WHITE 97
#define BLACK 30

void Board::initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[j][i] = ' ';
            colors[j][i] = 0;
        }
    }

    updateBoard('a', 1, 'p', WHITE);
    updateBoard('a', 2, 'K', BLACK);
    updateBoard('c', 1, 'Q', TRANSPARENT);
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

void Board::updateBoard(char file, int rank, char newChar, int color) {
    board[file - 97][rank - 1] = newChar;
    colors[file - 97][rank - 1] = color;
}