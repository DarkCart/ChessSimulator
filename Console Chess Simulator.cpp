#include <iostream>
#include "PGNParser.h"
#include "Board.h"
#include "GamePiece.h"
#include "MoveSimulator.h"

int main(int argc, char **argv)
{   
    if (argc != 2) {
        std::cout << "Improper number of arguments. Specify the .PGN file to be simulated." << std::endl;
        std::exit(-1);
    }

    PGNParser p;
    p.readFile(argv[1]);
    std::vector<GameMove> moves = p.getMoves();

    Board b;
    
    MoveSimulator moveSim(&b);

    for (GameMove move : moves) {
        moveSim.simulateMove(move);
        std::cin.ignore();
    }
}

