#include <string>
#include <iostream>
#include <iomanip>
#include "LexicalAnalyzer.h"


std::string SOURCE{
	"while (fahr <= upper) a = 23.00; /* this is sample */"
};

LA::LexicalAnalyzer lex(SOURCE);


int main()
{
	std::cout << "    Token    |    Lexeme    \n" << std::setfill('-') << std::setw(29) << '\n';
	while (!lex.IsEOF())
	{
		LA::LexicalUnit lexUnit = lex.Lexer();
		std::cout << std::setw(13) << lexUnit.tokenString << "|" << std::setw(14) << lexUnit.lexeme << '\n';
	}
	
	return 0;
}