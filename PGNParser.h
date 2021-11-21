#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>
#include "GameMove.h"

class PGNParser
{
public:
	void readFile(const std::string& filename);
	std::vector<GameMove> getMoves();
	std::map<std::string, std::string> getMetaData();
private:
	void parseFile();
	void parseMetaDataLine(const std::string& line);
	void parseGameContents(std::string& rawMoves);
	std::vector<GameMove> moves;
	std::string rawFile;
	std::string rawMoves;
	std::vector<std::string> rawFileLines;
	std::map<std::string, std::string> metaData;
};

