#include <string>
#include <iostream>
#include <iomanip>
#include "LexicalAnalyzer.h"


std::string SOURCE{
	"  if  "
};

LA::LexicalAnalyzer lex(SOURCE);


int main()
{
	std::cout << "    Token    |    Lexeme    \n" << std::setfill('-') << std::setw(29) << '\n';
	LA::LexicalUnit lexUnit;
	while (lex.Lexer(lexUnit))
	{
		std::cout << std::setw(12) << lexUnit.tokenString << "|" << std::setw(12) << lexUnit.lexeme << '\n';
	}
	
	return 0;
}