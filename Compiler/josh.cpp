#include <string>
#include <iostream>
#include "LexicalAnalyzer.h"


const std::string SOURCE{
	"while (fahr <= upper) a = 23.00; /* this is sample */"
};

LA::LexicalAnalyzer lex{ SOURCE };

int main()
{

	std::cout << LA::TOKEN_TO_STRING_MAP.at(LA::eToken::KEYWORD) << std::endl;
	return 0;
}