#include <iostream>

class Board {
    public:
        void initBoard();
        void drawBoard();
        void updateBoard(char file, int rank, char newChar, int color);
    private:
        char board[8][8];
        int colors[8][8];
};