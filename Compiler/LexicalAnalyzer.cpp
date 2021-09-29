#include "LexicalAnalyzer.h"

LA::LexicalAnalyzer::LexicalAnalyzer(const std::string& sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }, m_currentState{eStates::START}
{
}

// Call Lexer to recieve next token
LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
{
	if (IsEOF())
	{
		LexicalUnit lexUnit;
		lexUnit.token = eToken::NO_TOKEN;
		lexUnit.lexeme = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		return lexUnit;
	}

	// Increment source index to next non-blank character
	while (!IsEOF() && IsBlank())
	{
		IncrementIndex();
	}
	
	// Cache current source char and check its input category (letter, digit, .)
	std::string currCh{ m_source[m_currentIndex] };
	eInputType inputType;
	if (isalpha(currCh.front()))
	{
		inputType = eInputType::LETTER_INPUT;
	}
	else if (isdigit(currCh.front()))
	{
		inputType = eInputType::DIGIT_INPUT;
	}
	else if (isspace(currCh.front()))
	{
		inputType = eInputType::PERIOD_INPUT;
	}

	eStates newState;
	newState = StateTable[static_cast<int>(m_currentState)][static_cast<int>(newState)];

	

}

