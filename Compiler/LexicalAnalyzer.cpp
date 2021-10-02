#include "LexicalAnalyzer.h"
#include <stack>

/// <summary>
/// Constructor for Lexical Analyzer. Requires string containing source on construction
/// </summary>
/// <param name="sourceRef"></param>
LA::LexicalAnalyzer::LexicalAnalyzer(std::string sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }, m_currentState{ eStates::START }
{

}

/// <summary>
/// Call Lexer(LexicalUnit&) to load reference param with next token
/// </summary>
/// <param name="lexUnit"></param>
/// <returns>True if token found or False if EOF</returns>
bool LA::LexicalAnalyzer::Lexer(LexicalUnit& lexUnit)
{

	char inputChar= ' ';
	

#pragma region Skip White Space and Position Source Index
	if (IsEOF(m_currentIndex))
	{
		return false;
	} // end if(IsEOF())
	else if (!IsEOF(m_currentIndex))
	{
		inputChar = m_source.at(m_currentIndex);
		while (!IsEOF(m_currentIndex) && IsBlank(inputChar))
		{
			++m_currentIndex;
			inputChar = m_source.at(m_currentIndex);
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
	std::stack<LA::eStates> stateStack;
	do
	{
		stateStack.push(m_currentState);
		m_currentState = nextState;
		m_currentIndex = nextIndex;
		inputChar = m_source.at(m_currentIndex);
		nextState = StateTable[static_cast<int>(m_currentState)][static_cast<int>(InputType(inputChar))];
		nextIndex = m_currentIndex + 1;

		endIndex = m_currentIndex;

	} while (!IsEOF(nextIndex) && !IsDelimiter(inputChar));

	// if we have a backup state on top then pop it to back up
	while (stateStack.top() == LA::eStates::BACKUP)
	{
		stateStack.pop();
	}

	// if by now the stop state on the stack is an accept, then this is our token
	if (IsAccepted(stateStack.top()))
	{
		int strLength{ endIndex - startIndex };
		lexUnit.lexeme = std::string(m_source.substr(startIndex, strLength));

		if (stateStack.top() == eStates::IDENTIFIER)
		{
			if (IsKeyword(lexUnit.lexeme))
			{
				lexUnit.token = eToken::KEYWORD;
			}
			else
			{
				lexUnit.token = eToken::IDENTIFIER;
			}
		}
		else
		{
			lexUnit.token = STATE_TO_TOKEN_MAP.at(m_currentState);
		}
		
		lexUnit.tokenString = TOKEN_TO_STRING_MAP.at(lexUnit.token);		
		m_currentIndex = endIndex+1;
	}
	

}

/// <summary>
/// Confirms whether or not the current source position is the EOF
/// </summary>
/// <returns>True if current position is EOF false otherwise</returns>
bool LA::LexicalAnalyzer::IsEOF() const
{
	return m_currentIndex >= static_cast<int>(m_source.length());
}

/// <summary>
/// Confirms whether or not the provided source position is the EOF
/// </summary>
/// <param name="sourceIndex"></param>
/// <returns>True if provided position is EOF or false otherwise</returns>
bool LA::LexicalAnalyzer::IsEOF(int sourceIndex) const
{
	return sourceIndex >= static_cast<int>(m_source.length());
}


/// <summary>
/// Used internally to check string against a list of Keywords
/// </summary>
/// <param name="kw"></param>
/// <returns>True if keyword and false otherwise</returns>
bool LA::LexicalAnalyzer::IsKeyword(const std::string kw) const
{
	bool isFound= std::find(std::begin(m_keywords), std::end(m_keywords), kw) != std::end(m_keywords);
	return isFound;
}

/// <summary>
/// Used internally to check string against a list of accept states
/// </summary>
/// <param name="st"></param>
/// <returns>true for accepted false otherwise</returns>
bool LA::LexicalAnalyzer::IsAccepted(eStates st) const 
{ 
	bool isFound = std::find(m_acceptStates.begin(), m_acceptStates.end(), st) != m_acceptStates.end();
	return isFound;
}

/// <summary>
/// used internally to check string against list of delimeters
/// </summary>
/// <param name="ch"></param>
/// <returns>True if delimiter false otherwise</returns>
bool LA::LexicalAnalyzer::IsDelimiter(char ch) const 
{
	bool isFound = std::find(m_delimiters.begin(), m_delimiters.end(), ch) != m_delimiters.end();
	return isFound;
}

/// <summary>
/// Used internally to confirm the type of input of param
/// </summary>
/// <param name="ch"></param>
/// <returns>The enumerated input type</returns>
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
