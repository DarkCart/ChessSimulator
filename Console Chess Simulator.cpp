#include <iostream>
#include "PGNParser.h"
#include "Board.h"
#include "GamePiece.h"

int main(int argc, char **argv)
{   
    if (argc != 2) {
        std::cout << "Improper number of arguments. Specify the .PGN file to be simulated." << std::endl;
        std::exit(-1);
    }

    PGNParser p;
    p.readFile(argv[1]);

    Board b;
    //b.drawBoard();

    std::cout << std::boolalpha;

    Pawn pawn('e', 2);
    std::cout << pawn.canMove('e', 4) << std::endl;

    Knight knight('g', 1);
    std::cout << knight.canMove('f', 3) << std::endl;

    Bishop bishop('d', 4);
    std::cout << bishop.canMove('c', 5) << std::endl;

    Rook rook('d', 5);
    std::cout << rook.canMove('d', 6) << std::endl;

    King king('f', 5);
    std::cout << king.canMove('g', 4) << std::endl;

    Queen queen('d', 4);
    std::cout << queen.canMove('b', 5) << std::endl;
}

