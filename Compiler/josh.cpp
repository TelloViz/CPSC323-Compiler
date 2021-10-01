#include <string>
#include <iostream>
#include <iomanip>
#include "LexicalAnalyzer.h"


std::string SOURCE{
	"123.321"
};

LA::LexicalAnalyzer lex(SOURCE);


int main()
{
	std::cout << "    Token    |    Lexeme    \n" << std::setfill('-') << std::setw(29) << '\n';
	while (!lex.IsEOF())
	{
		LA::LexicalUnit lexUnit = lex.Lexer();
		std::cout << std::setw(12) << lexUnit.tokenString << "|" << std::setw(12) << lexUnit.lexeme << '\n';
	}
	
	return 0;
}