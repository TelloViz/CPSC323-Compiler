#pragma once
#include <string>
#include <unordered_map>

namespace LA // Lexical Analysis 
{

	enum eToken
	// Valid Rat21F tokens
	{
		ACCEPT=0, 
		IDENTIFIER, 
		INTEGER, 
		REAL, 
		KEYWORD, 
		SEPARATOR, 
		BLANK, 
		UNKNOWN
	};

	const std::unordered_map<eToken, std::string> TOKEN_TO_STRING_MAP
	// Map used to convert eToken enumerated values into string values for output
	{
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
	// A data struct holding token and lexeme information for returning to parser
	{
		eToken token;
		std::string tokenString;
		std::string lexeme;
	};

	

	const int NUM_STATES{ 5 };
	const int NUM_INPUTS{ 4 };

	class LexicalAnalyzer
	// Main class of the lexer phase. This is the LexicalAnalyzer itself.
	{
	public:
		explicit LexicalAnalyzer(const std::string& sourceRef);

		LexicalUnit Lexer();

	private:
		
		//, L, D, \.
		int StateTable[NUM_STATES][NUM_INPUTS] = 
		{
			/*             Input                             */
			/*             L  D  .                           */
			/* State */ 
		};

	};

}