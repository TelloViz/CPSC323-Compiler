#include "LexicalAnalyzer.h"

LA::LexicalAnalyzer::LexicalAnalyzer(const std::string& sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }
{
}

LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
{
	if( !IsEOF())
	{
		if (IsBlank())
		{

		}
	}
}
