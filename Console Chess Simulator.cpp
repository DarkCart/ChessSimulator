#include <iostream>
#include "PGNParser.h"
#include "Board.h"
#include "GamePiece.h"
#include "MoveSimulator.h"
#include "DebugConsoleCommands.h"

int main(int argc, char **argv)
{
    std::string line;

    if (argc != 2) {
        std::cout << "Improper number of arguments. Specify the .PGN file to be simulated." << std::endl;
        std::exit(-1);
    }

    PGNParser p;
    p.readFile(argv[1]);
    std::vector<GameMove> moves = p.getMoves();

    Board b;
    
    MoveSimulator moveSim(&b);
/*
    while (true) {
        std::getline(std::cin, line);
        b.moveCharacterOnBoard(line[0], line[1]-'0', line[3], line[4]-'0');
        b.drawBoard();
    }
*/

    for (GameMove move : moves) {
        moveSim.simulateMove(move);
        std::getline(std::cin, line);
        DebugConsoleCommands::parseDebugCommand(line, moveSim.getWhitePieces(), moveSim.getBlackPieces());
    }

}

