#pragma once
#include <iostream>

class Board {
    public:
        const int WHITE = 97;
        const int BLACK = 30;
        const int TRANSPARENT = 0;
        Board();
        void drawBoard();
        void setCharacterOnBoard(char file, int rank, char newChar, int color);
        void moveCharacterOnBoard(char oldFile, int oldRank, char newFile, int newRank);
    private:
        char board[8][8];
        int colors[8][8];
        int convertRankToIndex(int rank);
};