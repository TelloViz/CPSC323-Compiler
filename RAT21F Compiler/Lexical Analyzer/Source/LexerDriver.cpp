#include <iostream>
#include "../Include/Utility/SourceStripper.hpp"

std::string SOURCE{ "This is my \n Source \n\nCode. Thre are a few lines\n in it" };
int main()
{
	auto newSource = Utility::SplitStringByLine(SOURCE);

	for (auto iter : newSource)
	{
		std::cout << iter << std::endl;
	}
	return 0;
}