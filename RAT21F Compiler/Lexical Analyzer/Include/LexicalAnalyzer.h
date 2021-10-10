#pragma once
#include <string>
#include "../StateTable.h"

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

	StateTable::eInputType FindInputType(std::string::iterator testInput) const;
	
	std::string m_source;
	bool m_isEOF{ false };

	
	
	
	
	StateTable m_stateTable{ m_stateVec };
	int m_currentStateID{ m_stateVec[0].ID() };
	int m_prevStateID{ m_stateVec[0].ID() };
	int m_nextStateID{ m_stateVec[0].ID() };

	std::string::iterator m_currCharIter;
	std::string::iterator m_prevCharIter;
	
};

