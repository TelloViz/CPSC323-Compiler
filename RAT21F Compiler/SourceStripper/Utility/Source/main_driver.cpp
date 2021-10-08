#include <sstream>
#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> SplitStringByLine(const std::string& str);

int main()
{

	std::string source{
		"This is some source that\n" \
		"Bleeds over multiple\n" \
		"Lines\n" \
		"\n" \
		"Did the stripper...\n" \
		"\n" \
		"\n" \
		"\n" \
		"...do its job."
	};
	std::vector<std::string> sourceLines =  SplitStringByLine(source);


	for (auto iter : sourceLines)
	{
		std::cout << iter << std::endl;
		
	}

	return 0;
}



std::vector<std::string> SplitStringByLine(const std::string& str)
{
	std::stringstream inSS(str);
	std::vector<std::string> returnVec{};

	std::string line;
	while (std::getline(inSS, line))
	{
		if (line.size()) returnVec.push_back(line);
	}
	return returnVec;
}