#include "LexicalAnalyzer.h"

LA::LexicalAnalyzer::LexicalAnalyzer(const std::string& sourceRef)
	: m_source{ sourceRef }, m_currentIndex{ 0 }
{
}

LA::LexicalUnit LA::LexicalAnalyzer::Lexer()
{
	while( !IsEOF())
	{
		if (IsBlank())
		{
			++m_currentIndex;
		}
	}

	// m_currentIndex should be either pointing at the first non-blank index or the end of file at this point.


}
