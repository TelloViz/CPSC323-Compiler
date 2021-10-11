#include "../Include/LexicalAnalyzer.h"
#include <iostream>

LexicalAnalyzer::LexicalAnalyzer(std::string sourceString) : m_source{sourceString}
{
	m_currCharIter = m_source.begin();
	m_prevCharIter = m_source.end();
	if (m_currCharIter == m_source.end()) m_isEOF = true;
}

bool LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{
	static bool isFirstCallToLexer{ true };
	bool isEndofToken{ false };
	std::string::iterator startOfToken{ m_currCharIter };
		
	if (m_isEOF) // If you've called Lexer() in EOF state
	{
		if (isFirstCallToLexer) // And its the first time you've called lexer
		{
			std::cout << "Lexer called for first time but already EOF..." << std::endl;
		}
		else // Any other call beside first
		{
			std::cout << "Looks like your last call to lexer was the EOF..." << std::endl;
		}
	}	

	while (!isEndofToken && !m_isEOF)
	{
		if (!isFirstCallToLexer)
		{
			m_currCharIter = m_nextCharIter;
		}

		//Find out character input type
		eInputType inputType = FindInputType(m_currCharIter);

		// Push_back current char into temp building string
		lexUnit.sLexeme.push_back(*m_currCharIter);

		// Query table for next state based on input type and current state	
		m_nextStateID = GetNextState(m_currentStateID, inputType);

		m_prevCharIter = m_currCharIter;
		if (++m_currCharIter == m_source.end())
		{
			m_isEOF = true;
		}

		m_prevStateID = m_currentStateID; // Next iteration our current state will be the previous state
		m_currentStateID = m_nextStateID; // next iteration our next state will be our new current state

		if (isEndofToken && acceptStates[m_currentStateID])
		{
			lexUnit.sToken = std::string(startOfToken, m_currCharIter);
		}
			
		}



	return m_isEOF;
	
}

LexicalAnalyzer::eInputType LexicalAnalyzer::FindInputType(std::string::iterator testInput) const
{
	char testChar = *testInput;
	eInputType inType{ LexicalAnalyzer::eInputType::UNKNOWN };

	if (testChar >= 48 && testChar <= 57)
		inType = LexicalAnalyzer::eInputType::DIGIT;
	else if ((testChar >= 97 && testChar <= 122) || (testChar >= 65 && testChar <= 90))
		inType = LexicalAnalyzer::eInputType::LETTER;
	else if (isspace(testChar)) inType = LexicalAnalyzer::eInputType::BLANK;

	return inType;
}

int LexicalAnalyzer::GetNextState(int currentState, eInputType inputType)
{
	return m_stateTable[currentState][inputType];
}
