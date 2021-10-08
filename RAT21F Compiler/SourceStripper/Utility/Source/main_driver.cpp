#include <iostream>
#include <string>
#include <vector>
#include "../Include/SourceStripper.hpp"


int main()
{

	std::string source{"This is some source that\nBleeds over multiple\nLines\n\nDid the stripper...\n\n\n\n...do its job."};
	std::vector<std::string> sourceLines =  Utility::SplitStringByLine(source);


	for (auto iter : sourceLines)
	{
		std::cout << iter << std::endl;
		
	}

	return 0;
}