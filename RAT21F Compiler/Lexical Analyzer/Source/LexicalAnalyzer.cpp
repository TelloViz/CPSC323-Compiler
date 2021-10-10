#include "../Include/LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::string sourceString)
{
}

bool LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{
	static int sInt{ 0 };
	sInt++;
	lexUnit.sLexeme = "Test Lexeme " + std::to_string(sInt);
	if (sInt == 1) return true;
	else return false;
}
