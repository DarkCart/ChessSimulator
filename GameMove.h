#pragma once
#include <string>

class GameMove {
public:
	GameMove(std::string whiteMove, std::string blackMove);
	const std::string getWhiteMove();
	const std::string getBlackMove();
private:
	std::string whiteMove;
	std::string blackMove;
};
