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

	// 1) Check End of File flag
	if (m_isEOF) return false; 

	// 2) Find out character input type
	StateTable::eInputType inputType = FindInputType(m_currCharIter);
	
	// 3) Update iterators and Query table for next state based on input type and current state
	
	int nextStateID = m_stateTable.GetNextState(m_currentStateID, inputType);	
	
	

	// 4) Push_back current char into temp building string
	resultString.push_back(*m_currCharIter);
	


	m_prevCharIter = m_currCharIter;
	if (++m_currCharIter == m_source.end())
	{
		m_isEOF = true;
	}
	
	m_prevStateID = m_currentStateID; // Next iteration our current state will be the previous state
	m_currentStateID = m_nextStateID; // next iteration our next state will be our new current state
}

StateTable::eInputType LexicalAnalyzer::FindInputType(std::string::iterator testInput) const
{
	char testChar = *testInput;
	StateTable::eInputType inType{ StateTable::eInputType::UNKNOWN };

	if (testChar >= 48 && testChar <= 57) 
		inType = StateTable::eInputType::DIGIT;
	else if ((testChar >= 97 && testChar <= 122) || (testChar >= 65 && testChar <= 90)) 
		inType = StateTable::eInputType::LETTER;

	return inType;
}
