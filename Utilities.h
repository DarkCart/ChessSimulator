#pragma once
#include <vector>
#include <string>
#include <sstream>

class Utilities
{
public:
	static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);
	static std::string replaceAll(std::string str, const std::string& from, const std::string& to);
	static std::istream& safeGetline(std::istream& is, std::string& t);
};

