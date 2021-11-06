#include "PGNParser.h"
#include "Utilities.h"

std::regex gamePattern("\\d+\\.?(\\s?(O-O|O-O-O)?\\s?\\w{1,3}[1-8]\\+?\\s)+(O-O|O-O-O)?");

void PGNParser::readFile(const std::string& filename) {
	std::cout << "Loading file " << filename << std::endl;
	std::ifstream filestream(filename);
	std::stringstream buffer;
	buffer << filestream.rdbuf();
	rawFile = buffer.str();
	rawFileLines = Utilities::splitString(rawFile, "\n");
	parseFile();
}

void PGNParser::parseFile() {
	// Isolate the metadata
	bool beginAppending = false;
	for (unsigned int i = 0; i < rawFileLines.size(); i++) {
		std::string line = rawFileLines[i];
		if (line[0] == '[' && line[line.size() - 1] == ']') {
			parseMetaDataLine(line);
		}

		if (line.length() == 0) {
			beginAppending = true;
		}

		if (beginAppending) {
			rawMoves += line + " ";
		}
	}
	parseGameContents(rawMoves);
}

void PGNParser::parseMetaDataLine(const std::string& line) {
	std::string bracketless = Utilities::splitString(Utilities::splitString(line, "[").at(1), "]").at(0);
	std::string tagName = Utilities::splitString(bracketless, " ").at(0);
	std::string tagValue = Utilities::splitString(bracketless, "\"").at(1);
	metaData.insert({ tagName, tagValue });
}

void PGNParser::parseGameContents(std::string& rawMoves) {
	std::smatch m;
	std::vector<std::string> temp;
	while (std::regex_search(rawMoves, m, gamePattern)) {
		std::string regex_match = m.str(0);
		std::size_t found = regex_match.find(" ");
		if (regex_match[found - 1] == '.') {
			regex_match.replace(found, 1, "");
		}
		//std::cout << regex_match << std::endl;
		temp.push_back(regex_match);
		rawMoves = m.suffix().str();
	}

	for (std::string s : temp) {
		std::string numberless = Utilities::splitString(s, ".").at(1);
		std::string whiteMove = Utilities::splitString(numberless, " ").at(0);
		std::string blackMove = Utilities::splitString(numberless, " ").at(1);
		std::cout << "\x1b[90;107m" << whiteMove << "\x1b[0m" << " " << "\x1b[97;100m" << blackMove << "\x1b[0m" << std::endl;
	}

	//std::cout << temp.at(0) << std::endl;
}
