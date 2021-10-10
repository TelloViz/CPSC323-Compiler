#pragma once
#include <string>

struct LexicalUnit
{
	enum EnumeratedToken{INTEGER, UNKNOWN};
	EnumeratedToken eToken{ UNKNOWN };
	std::string sToken;
	std::string sLexeme;
};

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(std::string sourceString);
	bool Lexer(LexicalUnit& lexUnit);
private:
};

