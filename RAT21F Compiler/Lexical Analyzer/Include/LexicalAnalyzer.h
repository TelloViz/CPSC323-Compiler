#pragma once
#include <string>
#include "../StateTable.h"
#include <vector>

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

	enum eInputType{LETTER=0, DIGIT, UNDERSCORE, PERIOD, BLANK, UNKNOWN};
	eInputType FindInputType(std::string::iterator testInput) const;
	int GetNextState(int currentState, eInputType inputType);
	
	std::string m_source;
	bool m_isEOF{ false };

	int m_stateTable[5][5]
	{
		0,	1,	2,	-1, -1,
		1,	1,	1,	 1, -1,
		2,  -1,	2,   -1,  3,
		3,  -1,   4,   -1, -1,
		4,  -1,	4	-1, -1
	};
	
	std::vector<bool> acceptStates = { false, true, true, false, true };
	
	int m_currentStateID{ 0 };
	int m_prevStateID{ -1 };
	int m_nextStateID{ -1 };

	std::string::iterator m_currCharIter;
	std::string::iterator m_prevCharIter;
	std::string::iterator m_nextCharIter;
	
};

