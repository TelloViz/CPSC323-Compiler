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

	

}

