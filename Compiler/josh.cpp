#include <string>
#include <iostream>
#include <iomanip>
#include "LexicalAnalyzer.h"


std::string SOURCE{
	"while if IF WHILE get put Josh josh 345 3.456 3.4.4."
};

LA::LexicalAnalyzer lex(SOURCE);
LA::LexicalUnit lexUnit;
int main()
{
	std::cout << "    Token    |    Lexeme    \n" << std::setfill('-') << std::setw(29) << '\n';
	while (lex.Lexer(lexUnit))
	{
		std::cout << std::setw(12) << lexUnit.tokenString << "|" << std::setw(12) << lexUnit.lexeme << '\n';
	}

	return 0;
}