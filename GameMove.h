#pragma once
#include <string>

class GameMove {
public:
	GameMove(std::string whiteMove, std::string blackMove);
	std::string getWhiteMove();
	std::string getBlackMove();
private:
	std::string whiteMove;
	std::string blackMove;
};
