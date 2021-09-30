#pragma once
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
//#include <cstdlib>

namespace LA // Lexical Analysis 
{

	enum class eStates
	{
		START = 0,
		IDENTIFIER = 1,
		INTEGER = 2,
		INCOMPLETE_REAL = 3,
		REAL = 4,
		UNKNOWN = 5
	};

	

	enum class eToken
		// Valid Rat21F tokens
	{
		IDENTIFIER, 
		INTEGER,
		REAL,
		KEYWORD, 
		SEPARATOR, 
		BLANK, 
		UNKNOWN,
		NO_TOKEN
	};

	

	struct LexicalUnit
	// A data struct holding token and lexeme information for returning to parser
	{
		eToken token;
		std::string tokenString;
		std::string lexeme;
	};

	enum class eInputType
	{
		LETTER_INPUT=1, 
		DIGIT_INPUT=2, 
		PERIOD_INPUT=3, 
		BLANK_INPUT, 
		UNKNOWN_INPUT
	};

	const int NUM_STATES{ 6 };
	const int NUM_INPUTS{ 3 };

	class LexicalAnalyzer
		// Main class of the lexer phase. This is the LexicalAnalyzer itself.
	{
	public:
		explicit LexicalAnalyzer(std::string sourceRef);

		LexicalUnit Lexer();
		bool IsEOF() const { return m_currentIndex >= m_source.length(); }

	private:


		bool IsBlank(char ch) const { return isspace(m_source.at(m_currentIndex)); }
		bool IsDelimiter(char ch) const {return std::find(m_delimiters.begin(), m_delimiters.end(), ch) != m_delimiters.end();}
		bool IsAccepted() const { return STATE_TO_TOKEN_MAP.find(m_currentState) != STATE_TO_TOKEN_MAP.end(); }


		void IncrementSourceIndex() { ++m_currentIndex; }

		eInputType InputType(const char ch) const;

	private:

		int m_currentIndex;
		eStates m_currentState;
		std::string m_source;

		std::list<char> m_delimiters{ ';', ' ', '\t', '\n', '{', '}', '(', ')'};
		std::list <std::string> m_keywords
		{
			"true",	 "function",	"integer",	"false",	
			"boolean", "real",		"if",		"endif",
			"<=",	 "else",		"return",		"put",	
			"get",	 "while"		"+",			"}",
			"{",		 ", ",		"; ",		"-",
			"#",		 "*",		"/",			">",
			"<",		 "=>",		"!=",		"="
			
		};

		eStates StateTable[NUM_STATES][NUM_INPUTS+1] = 
		{
			/*                                                         Input                                           */

			/*               Start                              Letter		               Digit               Period(.)                           */
			/* State 0 */	  eStates::START,			eStates::IDENTIFIER,	   eStates::INTEGER,	 eStates::UNKNOWN,
			/* State 1 */	  eStates::IDENTIFIER,		eStates::IDENTIFIER,	   eStates::IDENTIFIER,   eStates::UNKNOWN,
			/* State 2 */	  eStates::INTEGER,			eStates::UNKNOWN,		   eStates::INTEGER,	 eStates::INCOMPLETE_REAL,
			/* State 3 */	  eStates::INCOMPLETE_REAL,   eStates::UNKNOWN,		   eStates::REAL,		 eStates::UNKNOWN,
			/* State 4 */	  eStates::REAL,			eStates::UNKNOWN,	        eStates::REAL,		 eStates::UNKNOWN,
			/* State 5 */	  eStates::UNKNOWN,			eStates::UNKNOWN,		   eStates::UNKNOWN,	 eStates::UNKNOWN
		};

		std::unordered_map<LA::eStates, LA::eToken> STATE_TO_TOKEN_MAP
		{
			{eStates::IDENTIFIER, eToken::IDENTIFIER},
			{eStates::INTEGER, eToken::INTEGER},
			{eStates::REAL, eToken::REAL},
			{eStates::UNKNOWN, eToken::UNKNOWN}
		};

		const std::unordered_map<eToken, std::string> TOKEN_TO_STRING_MAP
			// Map used to convert eToken enumerated values into string values for output
		{
			{eToken::IDENTIFIER, "identifier"},
			{eToken::INTEGER, "integer"},
			{eToken::REAL, "real"},
			{eToken::KEYWORD, "keyword"},
			{eToken::SEPARATOR, "separator"},
			{eToken::BLANK, "blank"},
			{eToken::UNKNOWN, "unknown"},
			{eToken::NO_TOKEN, "no_token"}
		};

	};

}