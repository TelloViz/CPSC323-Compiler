#pragma once
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>

namespace LA // Lexical Analysis 
{

	enum eStates
	{
		START = 0,
		IDENTIFIER = 1,
		INTEGER = 2,
		INCOMPLETE_REAL = 3,
		REAL = 4,
		UNKNOWN = 5
	};

	std::list<int> acceptanceStates
	{ 
		eStates::IDENTIFIER, 
		eStates::INTEGER, 
		eStates::REAL, 
		eStates::UNKNOWN };

	enum eToken
		// Valid Rat21F tokens
	{
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

	

	const int NUM_STATES{ 6 };
	const int NUM_INPUTS{ 3 };

	class LexicalAnalyzer
	// Main class of the lexer phase. This is the LexicalAnalyzer itself.
	{
	public:
		explicit LexicalAnalyzer(const std::string& sourceRef);

		LexicalUnit Lexer();

	private:

		bool IsEOF() const { return m_source[m_currentIndex] == NULL; }
		bool IsBlank() const { return isspace(m_source[m_currentIndex]); }
		bool IsAccepted() const { return std::find(acceptanceStates.begin(), acceptanceStates.end(), m_currentState) != acceptanceStates.end(); }

	private:
		
		int m_currentIndex;
		eStates m_currentState{ eStates::START };
		const std::string m_source;

		std::list<std::string> m_delimiters{ ";", " ", "\t", "\n" };
		

		//, L, D, \.
		int StateTable[NUM_STATES][NUM_INPUTS+1] = 
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

	};

}