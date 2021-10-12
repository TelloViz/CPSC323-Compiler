#pragma once
#include <string>
#include "../StateTable.h"
#include <vector>

//#define DEBUG

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

	enum eInputType{BLANK=0, LETTER=1, DIGIT=2, UNDERSCORE=3, PERIOD=4, UNKNOWN=6, END_OF_FILE=-1};
	eInputType FindInputType(std::string::iterator testInput) const;
	int GetNextState(int currentState, eInputType inputType);
	
	std::string m_source;
	bool m_isEOF{ false };

	int m_stateTable[5][5]
	{
		0,	1,	2,	 0,  0,
		1,	1,	1,	 1,  0,
		2,   0,	2,    0,  3,
		3,   0,   4,    0,  0,
		4,   0,	4,	 0,  0
	};
	
	std::vector<bool> acceptStates = { false, true, true, false, true };
	
	int m_currentStateID{ 0 };
	int m_prevStateID{ -1 };
	int m_nextStateID{ -1 };

	std::string::iterator m_currCharIter;
	std::string::iterator m_prevCharIter;
	std::string::iterator m_nextCharIter;
	
};

