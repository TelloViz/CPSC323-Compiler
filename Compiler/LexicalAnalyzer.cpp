#include "LexicalAnalyzer.h"

LA::LexicalAnalyzer::LexicalAnalyzer(const std::string& sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }, m_currentState{eStates::START}
{
}

// Call Lexer to recieve next token
LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
{
	// Increment source index to next non-blank character
	while (!IsEOF() && IsBlank())
	{
		IncrementIndex();
	}

	if (IsEOF())
	{
		LexicalUnit lexUnit;
		lexUnit.token = eToken::NO_TOKEN;
		lexUnit.lexeme = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		return lexUnit;
	}

	// Cache current source char and check its input category (letter, digit, .)
	char currCh{ m_source[m_currentIndex] };
	eInputType inputType;
	if (isalpha(currCh))
	{
		inputType = eInputType::LETTER;
	}
	else if (isdigit(currCh))
	{
		inputType = eInputType::DIGIT;
	}
	else if (currCh == '.')
	{
		inputType = eInputType::PERIOD;
	}

	eStates newState;
	newState = StateTable[m_currentState][inputType];

	

}

