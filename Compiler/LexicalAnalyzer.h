#pragma once
#include <string>
#include <unordered_map>

namespace LA // Lexical Analysis 
{

	enum eToken{ACCEPT=0, IDENTIFIER, INTEGER, REAL, KEYWORD, SEPARATOR, BLANK, UNKNOWN};

	const std::unordered_map<eToken, std::string> TOKEN_TO_STRING_MAP{
		{eToken::ACCEPT, "accept"},
		{eToken::IDENTIFIER, "identifier"},
		{eToken::INTEGER, "integer"},
		{eToken::REAL, "real"},
		{eToken::KEYWORD, "keyword"},
		{eToken::SEPARATOR, "separator"},
		{eToken::BLANK, "blank"},
		{eToken::UNKNOWN, "unknown"}
	};

	struct LexicalUnit
	{
		eToken token;
		std::string tokenString;
		std::string lexeme;
	};

	class LexicalAnalyzer
	{
	public:
		explicit LexicalAnalyzer(const std::string& sourceRef);

		LexicalUnit Lexer();

	private:

	};

}