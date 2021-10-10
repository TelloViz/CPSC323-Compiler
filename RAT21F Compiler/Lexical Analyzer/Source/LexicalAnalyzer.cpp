#include "../Include/LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::string sourceString) : m_source{sourceString}
{
	m_currCharIter = m_source.begin();
	m_prevCharIter = m_source.end();
	if (m_currCharIter == m_prevCharIter) m_isEOF = true;
}

bool LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{
	std::string resultString;
	bool isEndofToken{ false };

	 
	
	do
	{
		// 1) Check End of File flag
		if (m_isEOF) return false;

		// 2) Push_back current char into temp building string
		resultString.push_back(*m_currCharIter);

		// 3) Find out character input type
		eInputType inputType = FindInputType(m_currCharIter);

		// 4) Query table for next state based on input type and current state	
		m_nextStateID = GetNextState(m_currentStateID, inputType);


		m_prevCharIter = m_currCharIter;
		if (++m_currCharIter == m_source.end())
		{
			m_isEOF = true;
		}

		m_prevStateID = m_currentStateID; // Next iteration our current state will be the previous state
		m_currentStateID = m_nextStateID; // next iteration our next state will be our new current state

	} while (!isEndofToken && !m_isEOF);

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

	return inType;
}

int LexicalAnalyzer::GetNextState(int currentState, eInputType inputType)
{
	return m_stateTable[currentState][inputType];
}
