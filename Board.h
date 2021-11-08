#include <iostream>

class Board {
    public:
        Board();
        void drawBoard();
        void setCharacterOnBoard(char file, int rank, char newChar, int color);
        void moveCharacterOnBoard(char oldFile, int oldRank, char newFile, int newRank);
    private:
        char board[8][8];
        int colors[8][8];
};