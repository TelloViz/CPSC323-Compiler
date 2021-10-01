#include "LexicalAnalyzer.h"


LA::LexicalAnalyzer::LexicalAnalyzer(std::string sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }, m_currentState{ eStates::START }
{
}

// Call Lexer to recieve next token
LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
{
	if (IsEOF())
	{
		LA::LexicalUnit lexUnit;
		lexUnit.token = LA::eToken::NO_TOKEN;
		lexUnit.lexeme = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		return lexUnit;
	}

	

	// Cache current source char and check its input category (letter, digit, .)
	
	std::string tokenString{}, lexeme{};
	LA::eToken token{};
	m_currentState = LA::eStates::START;
	LA::eStates prevState{ m_currentState };

	char currCh(m_source.at(m_currentIndex));
	int tokenStartIndex{ m_currentIndex };
	int tokenEndIndex{ m_currentIndex };

	int currStateEnumAsIndex{};
	int inputEnumAsIndex{};

	// Increment source index to next non-blank character
	while (!IsEOF() && IsBlank(currCh))
	{
		IncrementSourceIndex();
		currCh = m_source.at(m_currentIndex);
	}

	/* This while loop should grab each subsequent character
	 as long as it is not a Delimiter or EOF */
	while (!IsEOF() && !IsDelimiter(currCh)) 
	{
		currStateEnumAsIndex = static_cast<int>(m_currentState);
		inputEnumAsIndex = static_cast<int>(InputType(currCh));
		prevState = m_currentState;
		m_currentState = StateTable[currStateEnumAsIndex][inputEnumAsIndex];
		tokenEndIndex = m_currentIndex;
		  
		currCh = m_source.at(m_currentIndex);
	}

	if (IsAccepted())
	{
		token = STATE_TO_TOKEN_MAP.at(m_currentState);
		tokenString = TOKEN_TO_STRING_MAP.at(token);
		int strLength{ m_currentIndex - tokenStartIndex };
		lexeme = std::string(m_source.substr(tokenStartIndex, strLength));
		return LA::LexicalUnit{ token, tokenString, lexeme };
	}
	else
	{
		token = LA::eToken::UNKNOWN;
		tokenString = TOKEN_TO_STRING_MAP.at(token);
		int strLength{ m_currentIndex - tokenStartIndex };
		lexeme = std::string(m_source.substr(tokenStartIndex, strLength));
		return LA::LexicalUnit{ token, tokenString, lexeme };
		 
	}
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
		inputType = LA::eInputType::PERIOD_INPUT;
	}

	return inputType;
}
