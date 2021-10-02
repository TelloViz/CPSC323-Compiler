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
		UNKNOWN = 5,
		BACKUP = 6
	};

	

	enum class eToken
		// Valid Rat21F tokens
	{
		IDENTIFIER=1, 
		INTEGER=2,
		NO_TOKEN = 3,
		REAL=4,
		KEYWORD, 
		SEPARATOR, 
		BLANK, 
		UNKNOWN
		
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
		BLANK_INPUT=4, 
		UNKNOWN_INPUT
	};

	const int NUM_STATES{ 7 };
	const int NUM_INPUTS{ 4 };

	class LexicalAnalyzer
		// Main class of the lexer phase. This is the LexicalAnalyzer itself.
	{
	public:
		explicit LexicalAnalyzer(std::string sourceRef);

		//LexicalUnit Lexer();
		bool Lexer(LexicalUnit& lexUnit);
		

	private:

		bool IsEOF() const
		{
			return m_currentIndex >= static_cast<int>(m_source.length());
		}

		bool IsEOF(int sourceIndex) const
		{
			return sourceIndex >= static_cast<int>(m_source.length());
		}

		bool IsBlank(char ch) const { return isspace(ch); }
		bool IsDelimiter(char ch) const;
		bool IsAccepted(eStates) const;
		bool IsKeyword(const std::string kw) const;


		void IncrementSourceIndex() { ++m_currentIndex; }

		eInputType InputType(char ch) const;

	private:

		int m_currentIndex;
		eStates m_currentState;
		std::string m_source;

		std::list<char> m_delimiters
		{ 
			';', ' ', '\t', '\n', '{', '}', '(', ')'
		};

		std::list <std::string> m_keywords
		{
			"true",	 "function",	"integer",	"false",	
			"boolean", "real",		"if",		"endif",
			"else",	 "return",	"put",		"get",	 "while"
			
		};

		std::list <std::string> m_operators
		{
			"<=",	 "+",		"-", 	"*",		
			"/",		 ">",		"<",		"=>",
			"!=",	 "="
		};

		std::list<std::string> m_separators
		{
			"}",		"{",		"(",		")",
			",",	";",		
		};

		std::list <eStates> m_acceptStates
		{
			LA::eStates::IDENTIFIER,
			LA::eStates::INTEGER,
			LA::eStates::REAL,
			LA::eStates::UNKNOWN
		};

		eStates StateTable[NUM_STATES][NUM_INPUTS+1] = 
		{
			/*                                                         Input                                           */

			/*               Start                              Letter		               Digit               Period(.)				Space( )			Separator */
			/* State 0 */	  eStates::START,			eStates::IDENTIFIER,	   eStates::INTEGER,	 eStates::UNKNOWN,		eStates::START,
			/* State 1 */	  eStates::IDENTIFIER,		eStates::IDENTIFIER,	   eStates::IDENTIFIER,   eStates::UNKNOWN,		eStates::BACKUP,
			/* State 2 */	  eStates::INTEGER,			eStates::UNKNOWN,		   eStates::INTEGER,	 eStates::INCOMPLETE_REAL, eStates::BACKUP,
			/* State 3 */	  eStates::INCOMPLETE_REAL,   eStates::UNKNOWN,		   eStates::REAL,		 eStates::UNKNOWN,		eStates::UNKNOWN,
			/* State 4 */	  eStates::REAL,			eStates::UNKNOWN,	        eStates::REAL,		 eStates::UNKNOWN,		eStates::BACKUP,
			/* State 5 */	  eStates::UNKNOWN,			eStates::UNKNOWN,		   eStates::UNKNOWN,	 eStates::UNKNOWN,		eStates::BACKUP,
			/* State 6 */	  eStates::BACKUP,			eStates::UNKNOWN,		   eStates::UNKNOWN,      eStates::UNKNOWN,       eStates::BACKUP
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