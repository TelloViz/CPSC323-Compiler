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
#pragma region End Of File verification
	if (IsEOF())
	{
		LA::LexicalUnit lexUnit;
		lexUnit.token = LA::eToken::NO_TOKEN;
		lexUnit.lexeme = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
		return lexUnit;
	}
#pragma endregion
	
#pragma region Local Variable Declarations
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

	bool isCommentUnresolved;
#pragma endregion
	
#pragma region Cycle to next non-blank character as long as not End-Of-File
	// Increment source index to next non-blank character
	while (!IsEOF() && IsBlank(currCh))
	{
		currCh = m_source.at(m_currentIndex);
		IncrementSourceIndex();
		++tokenStartIndex;
		if (IsEOF())
		{
			LA::LexicalUnit lexUnit;
			lexUnit.token = LA::eToken::NO_TOKEN;
			lexUnit.lexeme = TOKEN_TO_STRING_MAP.at(lexUnit.token);
			lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);
			return lexUnit;
		}
		
	}
#pragma endregion

#pragma region Cycle through source input one character at a time
	/* This while loop should grab each subsequent character
	 as long as it is not a Delimiter or EOF */
	while (!IsEOF() && !IsDelimiter(currCh))
	{
		currCh = m_source.at(m_currentIndex);
		currStateEnumAsIndex = static_cast<int>(m_currentState);
		inputEnumAsIndex = static_cast<int>(InputType(currCh));
		prevState = m_currentState;
		m_currentState = StateTable[currStateEnumAsIndex][inputEnumAsIndex];
		tokenEndIndex = m_currentIndex;
		IncrementSourceIndex();

	}
#pragma endregion

#pragma region Acceptance Verification
	LA::LexicalUnit lexUnit;
	if (IsAccepted())
	{
		while (currCh == ' ')
		{
			currCh = m_source.at(--m_currentIndex);
		}
		int strLength{ (++m_currentIndex) - tokenStartIndex };
		lexeme = std::string(m_source.substr(tokenStartIndex, strLength));
		token = STATE_TO_TOKEN_MAP.at(m_currentState);
		if (token == LA::eToken::IDENTIFIER && IsKeyword(lexeme))
		{
			token = eToken::KEYWORD;
		}

		tokenString = TOKEN_TO_STRING_MAP.at(token);

		lexUnit.token = token;
		lexUnit.lexeme = lexeme;
		lexUnit.tokenString = tokenString;
	}
	else
	{
		token = LA::eToken::UNKNOWN;
		tokenString = TOKEN_TO_STRING_MAP.at(token);
		int strLength{ m_currentIndex - tokenStartIndex };
		lexeme = std::string(m_source.substr(tokenStartIndex, strLength));
		lexUnit.token = token;
		lexUnit.tokenString = tokenString;
		lexUnit.lexeme = lexeme;
	};
	return lexUnit;

#pragma endregion
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
