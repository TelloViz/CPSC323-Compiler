#include "LexicalAnalyzer.h"


LA::LexicalAnalyzer::LexicalAnalyzer(std::string sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }, m_currentState{ eStates::START }
{
}

// Call Lexer to recieve next token
/* **********************Lexer()*********************
// ** 


*/
//LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
//{
//	LexicalUnit lexUnit;
//	if (!IsEOF())
//	{
//		LA::eInputType inType = InputType(m_source.at(m_currentIndex));
//		LA::eStates nextState = StateTable[static_cast<int>(m_currentState)][static_cast<int>(inType)];
//	}
//	else
//	{
//		lexUnit.token = LA::eToken::NO_TOKEN;
//		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
//		lexUnit.lexeme = "EOF";
//		return lexUnit;
//	}
//
//	return lexUnit;
//}

bool LA::LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{

	char inputChar= ' ';
	

#pragma region Skip White Space and Position Source Index
	if (IsEOF(m_currentIndex))
	{
		return false;
	} // end if(IsEOF())
	else if (!IsEOF())
	{
		inputChar = m_source.at(m_currentIndex);
		while (!IsEOF(m_currentIndex) && IsBlank(inputChar))
		{
			++m_currentIndex;
		}

		// If we've skipped all white space
		// and have reached end of file
		if (IsEOF(m_currentIndex))
		{
			return false;
		}
	} // end else if (!IsEOF())
#pragma endregion


	// By this point m_currentIndex should be 
	// the index of a valid non blank and non-EOF character
	int nextIndex = m_currentIndex;
	int startIndex = m_currentIndex;
	int endIndex = m_currentIndex;
	m_currentState = eStates::START;
	eStates nextState = m_currentState;
	do
	{
		m_currentState = nextState;
		m_currentIndex = nextIndex;
		nextState = StateTable[static_cast<int>(m_currentState)][static_cast<int>(InputType(inputChar))];
		nextIndex = m_currentIndex + 1;
		endIndex = m_currentIndex;

	} while (!IsEOF(nextIndex) && !IsDelimiter(inputChar));

	if (IsAccepted())
	{
		lexUnit.token = STATE_TO_TOKEN_MAP.at(m_currentState);
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		int strLength{ endIndex - startIndex };
		lexUnit.lexeme = std::string(m_source.substr(startIndex, strLength));
		m_currentIndex = endIndex;
	}
	

}

bool LA::LexicalAnalyzer::IsKeyword(const std::string kw) const
{
	bool isFound= std::find(std::begin(m_keywords), std::end(m_keywords), kw) != std::end(m_keywords);
	return isFound;
}

bool LA::LexicalAnalyzer::IsAccepted() const 
{ 
	bool isFound = std::find(m_acceptStates.begin(), m_acceptStates.end(), m_currentState) != m_acceptStates.end();
	return isFound;
}
bool LA::LexicalAnalyzer::IsDelimiter(char ch) const 
{
	bool isFound = std::find(m_delimiters.begin(), m_delimiters.end(), ch) != m_delimiters.end();
	return isFound;
}
LA::eInputType LA::LexicalAnalyzer::InputType(char ch) const
{
	LA::eInputType inputType{ LA::eInputType::UNKNOWN_INPUT };
	if (isalpha(ch))
	{
		inputType = LA::eInputType::LETTER_INPUT;
	}
	else if (isdigit(ch))
	{
		inputType = LA::eInputType::DIGIT_INPUT;
	}
	else if (isspace(ch))
	{
		inputType = LA::eInputType::BLANK_INPUT;
	}
	else if (ch == char('.'))
	{
		inputType = LA::eInputType::PERIOD_INPUT;
	}

	return inputType;
}
