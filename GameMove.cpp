#include "GameMove.h"

GameMove::GameMove(std::string whiteMove, std::string blackMove) {
	this -> whiteMove = whiteMove;
	this -> blackMove = blackMove;
}

const std::string GameMove::getWhiteMove() {
	return whiteMove;
}

const std::string GameMove::getBlackMove() {
	return blackMove;
}
