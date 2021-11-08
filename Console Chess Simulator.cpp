#include <iostream>
#include "PGNParser.h"
#include "Board.h"

int main(int argc, char **argv)
{   
    if (argc != 2) {
        std::cout << "Improper number of arguments. Specify the .PGN file to be simulated." << std::endl;
        std::exit(-1);
    }

    PGNParser p;
    p.readFile(argv[1]);

    Board b;
    b.initBoard();
    b.drawBoard();
}

