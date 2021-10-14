#include "../Include/LexicalAnalyzer.h"
#include <iostream>
#include <stack>

LexicalAnalyzer::LexicalAnalyzer(std::string sourceString) : m_source{sourceString}
{
	m_currCharIter = m_source.begin();
	m_nextCharIter = m_source.begin() + 1;
	m_prevCharIter = m_source.end();
	if (m_currCharIter == m_source.end()) m_isEOF = true;
}

bool LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{

	if (m_isEOF) return true;

	static bool isFirstLexerLoop{ true };
	bool isEndofToken{ false };
	std::string::iterator startOfToken{ m_currCharIter };
	eInputType inputType{eInputType::UNKNOWN};

	std::stack<char> inputValueHistoryStack;
	std::stack<eInputType> inputHistoryStack;
	std::stack<int> stateHistoryStack;
	
	m_currentStateID = 0;
	m_nextStateID = 0;
	m_prevStateID = 0;

	

	while (!isEndofToken && !m_isEOF)
	{

		if (m_currCharIter == m_source.end())
		{
			m_isEOF = true;
			break;
		}
		if (!isFirstLexerLoop && !m_isEOF)
		{
			m_prevCharIter = m_currCharIter;
			m_currCharIter = m_nextCharIter;

			if (m_currCharIter == m_source.end())
			{
				m_isEOF = true;
				break;
			}
			else	m_nextCharIter = m_currCharIter + 1; 

			m_prevStateID = m_currentStateID;
			m_currentStateID = m_nextStateID;								
		}

		if (m_isEOF) break;


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

		isFirstLexerLoop = false;
	} // END ::  while (!isEndofToken && !m_isEOF)

	if (isEndofToken && acceptStates[m_currentStateID])
	{

		while (!inputValueHistoryStack.empty())
		{
			lexUnit.sLexeme.push_back( inputValueHistoryStack.top() );
			inputValueHistoryStack.pop();
		}
		std::reverse(lexUnit.sLexeme.begin(), lexUnit.sLexeme.end());

		//if (m_nextCharIter == m_source.end()) m_isEOF = true;
	}

	
	return m_isEOF;
	
}

LexicalAnalyzer::eInputType LexicalAnalyzer::FindInputType(std::string::iterator testInput) const
{
	eInputType inType{ LexicalAnalyzer::eInputType::UNKNOWN };
	char testChar;

	if (testInput == m_source.end())
	{
		inType = eInputType::END_OF_FILE;

	}
	else
	{
		testChar = *testInput;

		// Digit
		if (testChar >= 48 && testChar <= 57)
			inType = LexicalAnalyzer::eInputType::DIGIT;
		// Letter
		else if ((testChar >= 97 && testChar <= 122) || (testChar >= 65 && testChar <= 90))
			inType = LexicalAnalyzer::eInputType::LETTER;
		// Blank Space
		else if (isspace(testChar)) inType = LexicalAnalyzer::eInputType::BLANK;
		else inType = LexicalAnalyzer::eInputType::UNKNOWN;
	}

	return inType;
}

int LexicalAnalyzer::GetNextState(int currentState, eInputType inputType)
{
	return m_stateTable[currentState][inputType];
}
