#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

class PGNParser
{
public:
	void readFile(const std::string& filename);
	std::vector<std::string> getMoves();
private:
	void parseFile();
	void parseMetaDataLine(const std::string& line);
	void parseGameContents(std::string& rawMoves);
	std::vector<std::string> moves;
	std::string rawFile;
	std::string rawMoves;
	std::vector<std::string> rawFileLines;
	std::map<std::string, std::string> metaData;
};

