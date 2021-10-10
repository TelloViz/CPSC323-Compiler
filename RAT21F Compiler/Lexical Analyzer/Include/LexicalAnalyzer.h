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

	std::vector<State> m_stateVec
	{ 
		State(0, false), 
		State(1, true), 
		State(2, true), 
		State(3, false), 
		State(4, true) 
	};
	
	
	
	StateTable m_stateTable{ m_stateVec };
	int m_currentStateID{ m_stateVec[0].ID() };
	int m_prevStateID{ m_stateVec[0].ID() };
	int m_nextStateID{ m_stateVec[0].ID() };

	std::string::iterator m_currCharIter;
	std::string::iterator m_prevCharIter;
	
};

