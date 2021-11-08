#include "GameMove.h"

GameMove::GameMove(std::string whiteMove, std::string blackMove) {
	this -> whiteMove = whiteMove;
	this -> blackMove = blackMove;
}

std::string GameMove::getWhiteMove() {
	return whiteMove;
}

std::string GameMove::getBlackMove() {
	return blackMove;
}
