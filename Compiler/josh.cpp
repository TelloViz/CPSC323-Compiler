#include <string>
#include <iostream>
#include "LexicalAnalyzer.h"


const std::string SOURCE{
	"while (fahr <= upper) a = 23.00; /* this is sample */"
};

LA::LexicalAnalyzer lex{ SOURCE };


int main()
{

	auto tok = lex.Lexer();
	return 0;
}