#include "Board.h"

void Board::initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
                board[i][j] = 'X';
            } else {
                board[i][j] = '0';
            }
        }
    }
}

void Board::drawBoard() {
    std::cout << " a b c d e f g h" << std::endl;
    std::cout << "┏━┳━┳━┳━┳━┳━┳━┳━┓" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "┃";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 'X') {
                std::cout << "\x1b[100m";
            } else if (board[i][j] == '0') {
                std::cout << "\x1b[47m";
            }
            std::cout << " \x1b[0m┃";
        }
        std::cout << " " << (i + 1) << std::endl;
    }
    std::cout << "┗━┻━┻━┻━┻━┻━┻━┻━┛" << std::endl;
}