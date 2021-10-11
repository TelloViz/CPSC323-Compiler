#include "../Include/LexicalAnalyzer.h"
#include <iostream>
#include <stack>

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
	eInputType inputType{eInputType::UNKNOWN};

	std::stack<char> inputValueHistoryStack;
	std::stack<eInputType> inputHistoryStack;
	std::stack<int> stateHistoryStack;
		
#ifdef DEBUG
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
#endif // DEBUG

	while (!isEndofToken && !m_isEOF)
	{
		if (!isFirstCallToLexer)
		{
			m_currCharIter = m_nextCharIter;
			m_nextCharIter = m_currCharIter + 1; 
			m_currentStateID = m_nextStateID;
			m_prevStateID = m_currentStateID;									
		}

		//Find out character input type and push it to history stack
		inputHistoryStack.push(inputType = FindInputType(m_currCharIter));
		inputValueHistoryStack.push(*m_currCharIter);

		// This is the transition function essentially.
		// We supply current state ID and the input type we discovered it to be
		m_nextStateID = GetNextState(m_currentStateID, inputType);				


		

		if (FindInputType(m_nextCharIter) == eInputType::BLANK ||
			FindInputType(m_nextCharIter) == eInputType::UNKNOWN)
		{
			isEndofToken = true;
		}

		if (	m_nextCharIter == m_source.end())
		{
			m_isEOF = true;
			isEndofToken = true;
		}
		else m_prevCharIter = m_currCharIter;

	} // END ::  while (!isEndofToken && !m_isEOF)

	if (isEndofToken && acceptStates[m_currentStateID])
	{
		lexUnit.sToken = std::string(startOfToken, m_currCharIter);
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
