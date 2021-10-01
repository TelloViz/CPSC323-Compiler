#include "LexicalAnalyzer.h"


LA::LexicalAnalyzer::LexicalAnalyzer(std::string sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }, m_currentState{ eStates::START }
{
}

// Call Lexer to recieve next token
/* **********************Lexer()*********************
// ** 


*/
LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
{
	LexicalUnit lexUnit;
	if (!IsEOF())
	{
		LA::eInputType inType = InputType(m_source.at(m_currentIndex));
		LA::eStates nextState = StateTable[static_cast<int>(m_currentState)][static_cast<int>(inType)];
	}
	else
	{
		lexUnit.token = LA::eToken::NO_TOKEN;
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		lexUnit.lexeme = "EOF";
		return lexUnit;
	}

	return lexUnit;
}

bool LA::LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{

	while (!IsEOF() && IsBlank(m_source.at(m_currentIndex)))
	{
		++m_currentIndex;
		if (IsEOF()) return false;
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
bool LA::LexicalAnalyzer::IsDelimiter(std::string ch) const 
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
