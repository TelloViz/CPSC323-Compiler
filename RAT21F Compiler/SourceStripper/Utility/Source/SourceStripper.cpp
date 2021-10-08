#include "..\Include\SourceStripper.hpp"
#include <sstream>

std::vector<std::string> Utility::SplitStringByLine(const std::string& str)
{
	std::stringstream inSS(str);
	std::vector<std::string> returnVec{};

	std::string line;
	while (std::getline(inSS, line))
	{
		if(line.size()) returnVec.push_back(line);
	}
	return returnVec;
}
