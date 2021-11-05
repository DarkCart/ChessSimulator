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
	while (std::regex_search(rawMoves, m, gamePattern)) {
		std::cout << m.str(0) << std::endl;
		rawMoves = m.suffix().str();
	}
}
