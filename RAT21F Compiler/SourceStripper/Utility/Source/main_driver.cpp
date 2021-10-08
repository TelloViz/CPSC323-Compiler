#include <iostream>
#include <string>
#include <vector>
#include "../Include/SourceStripper.hpp"


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
	std::vector<std::string> sourceLines =  Utility::SplitStringByLine(source);


	for (auto iter : sourceLines)
	{
		std::cout << iter << std::endl;
		
	}

	return 0;
}