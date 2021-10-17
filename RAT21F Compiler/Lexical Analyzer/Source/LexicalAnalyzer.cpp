// LexicalAnalyzer.cpp

// this file holds the definitions to the functions declared in the LexicalAnalyzer.h file
// Functions used here are documented in header file with comment headers on each signature.

// Author: Joshua Lollis
// Last Edited: 10/16/21
// CPSC 323 James Choi, Fall 2021
// Assignment 1 Lexical Analyzer

#include "../Include/LexicalAnalyzer.h"
#include <algorithm>


LexicalAnalyzer::LexicalAnalyzer(std::string sourceString) : source{ sourceString }
{
	source = RemoveComments(source, "/*", "*/"); // removal of comments in our local copy
}

bool LexicalAnalyzer::Lexer(std::string& token, std::string& lexeme)
{

	if (isFirstRun) // Initalizes the iterators on the first calling
	{
		currCharIter = source.begin();
		tokenStartIter = source.begin();
		isFirstRun = false;
	}

	// clearing out token/lexeme pair on each calling
	lexeme = "";
	token = "";


	// Local data initialization
	eInputType inputType;
	std::stack<char> INPUT_STACK;
	std::stack<int> STATE_STACK;
	std::stack<char> LEXEME_STACK;



	
	bool isEOT{ false }; // End of Token :: true means the end of a token has been discovered
	bool isEOF{ false }; // End of File :: true means the end of a file has been discovered


	// just a copy of the character at the current source position
	char currCharCopy;

	if (currCharIter == source.end()) // if the current position is the end, set the flags
	{
		isEOF = true;
		isEOT = true;
	}
	// Verify iterator validity then copy value pointed to by iterator 
	if (!isEOF) currCharCopy = *currCharIter;

	// sets default state to 0 each call to Lexer;
	int currentState{ 0 };


	// Lexer scoped strings for storing the values uncovered in analysis
	std::string foundToken, foundTokenString;

	// An enumeration for tranlating token types 
	eTokenType foundTokenType;


	// prepare a flag for when backups are needed in the loop
	bool shouldBackUp{ false };


	// This while loop will skip any leading white 
	// space on any give lexer call
	while (!isEOF && isSpace(currCharCopy))
	{
		++currCharIter;
		if (currCharIter == source.end())
		{
			isEOF = true;
		}
		else currCharCopy = *currCharIter;
	}

	// Before we start processing, simply check if the character is a simple operator or separator
	// If so we can skip the state table altogether.
	eInputType precheckInputType = GetInputType(currCharCopy);
	bool isPreChecked{ false };
	if (!isEOF)
	{

		switch (precheckInputType)
		{
		case UNDERSCORE:
			isEOT = true;
			isPreChecked = true;
			lexeme = "_";
			token = Token_To_String_Map.at(NONE);
			break;
		case PERIOD:
			isEOT = true;
			isPreChecked = true;
			lexeme = ".";
			token = Token_To_String_Map.at(NONE);
			break;
		case OPEN_PAREN:
			isEOT = true;
			isPreChecked = true;
			lexeme = "(";
			token = Token_To_String_Map.at(SEPARATOR);
			break;
		case CLOSE_PAREN:
			isEOT = true;
			isPreChecked = true;
			lexeme = ")";
			token = Token_To_String_Map.at(SEPARATOR);
			break;
		case UNKNOWN:
			isEOT = true;
			isPreChecked = true;
			token = Token_To_String_Map.at(NONE);
			break;
		case OPEN_BRACKET:
			isEOT = true;
			isPreChecked = true;
			lexeme = "{";
			token = Token_To_String_Map.at(SEPARATOR);
			break;
		case CLOSE_BRACKET:
			isEOT = true;
			isPreChecked = true;
			lexeme = "}";
			token = Token_To_String_Map.at(SEPARATOR);
			break;
		case PLUS:
			isEOT = true;
			isPreChecked = true;
			lexeme = "+";
			token = Token_To_String_Map.at(OPERATOR);
			break;
		case MINUS:
			isEOT = true;
			isPreChecked = true;
			lexeme = "-";
			token = Token_To_String_Map.at(OPERATOR);
			break;
		case MULTIPLY:
			isEOT = true;
			isPreChecked = true;
			lexeme = "*";
			token = Token_To_String_Map.at(OPERATOR);
			break;
		case SEMI_COLON:
			isEOT = true;
			isPreChecked = true;
			lexeme = ";";
			token = Token_To_String_Map.at(SEPARATOR);
			break;
		case COMMA:
			isEOT = true;
			isPreChecked = true;
			lexeme = ",";
			token = Token_To_String_Map.at(SEPARATOR);
			break;
		default:
			break;
		}

	}

	// This while loop is where the actual state traversal and analysis happens
	while (!isEOT && !isEOF)
	{
		// Safety check to ensure good iterator access
		if (currCharIter == source.end() || *currCharIter < 0)
		{
			isEOF = true; // otherwise set flags
			isEOT = true;

		}
		if (isEOF) break;
		// NOTE:

		/*     currState:inputType->destState     */

		// Push current state onto state stack
		STATE_STACK.push(currentState);

		// are we at a backup state? if so we're done and need to back up
		if (isBackupState.at(currentState))
		{

			isEOT = true;
			STATE_STACK.pop();
			LEXEME_STACK.pop();
			--currCharIter;

			// I also have one double backup state that is supposed to recover invalid reals to useable tokens 
			// by backing up the iterator to the integer portion before a double period:: Not sure its working correctly
			if (isDoubleBackupState.at(currentState))
			{
				assert(!STATE_STACK.empty());
				STATE_STACK.pop();
				assert(!LEXEME_STACK.empty());
				LEXEME_STACK.pop();
				assert(!LEXEME_STACK.empty());
				LEXEME_STACK.pop();
				--currCharIter;
				--currCharIter;
			}


		}

		// Else not a backup state, then keep processing
		else
		{
			LEXEME_STACK.push(currCharCopy); // Push current lexeme being built char by char

			inputType = GetInputType(currCharCopy);	// Get the current input chars eInputType (enum)	
			INPUT_STACK.push(currCharCopy);	// push current input onto stack, these are used for debugging as well as some operations throughout

			int destState = stateTable[currentState][inputType]; // Get resulting destination state

			// increment our source position
			currCharIter++;
			// verify EOF
			if (currCharIter == source.end()) { STATE_STACK.push(destState); }
			else {
				// Increment for next loop
				currentState = destState;
				currCharCopy = *currCharIter;
			}


		}



	} // END OF LEXER WHILE LOOP

	// Are we at the end of a token? As indicated by isEOT flag
	if (isEOT)
	{
		// if we prechecked before the loop then we need
		// to take special consideraton of our iterators and things
		if (!isPreChecked && isAcceptState.at(STATE_STACK.top()))
		{

			//loop through lexeme stack popping to lexeme string, then reverse for correct order
			while (!LEXEME_STACK.empty()) // Use LEXEME_QUEUE to populate param Lexeme string
			{
				lexeme.push_back(LEXEME_STACK.top());
				LEXEME_STACK.pop();
			}
			std::reverse(lexeme.begin(), lexeme.end());

			// Lookup type of token on top of state stack
			eTokenType tokType = eTokenLookUp.at(STATE_STACK.top());
			// assign discovered value
			token = Token_To_String_Map.at(tokType);

			// the following 5 lines cover checking Identifiers for Keyword status change
			auto kwIdx = std::find(keywordVec.begin(), keywordVec.end(), lexeme);
			if (kwIdx != keywordVec.end())
			{
				token = "keyword";
			}


		}

		if (isPreChecked) // if we did a precheck go here for special considerations
		{
			++currCharIter;
			if (currCharIter == source.end())
			{
				isEOF = true;
				isEOT = true;
			}
		}
	}

	return isEOF;		// Return the end of file status, this will be the lexers signal that its done

} // END OF LEXER FUNCTION


// The function that converts from char to input type enumeration.
LexicalAnalyzer::eInputType LexicalAnalyzer::GetInputType(char ch)
{
	if (isOpenBracket(ch)) return eInputType::OPEN_BRACKET;
	if (iscloseBracket(ch)) return eInputType::CLOSE_BRACKET;
	if (isPlus(ch)) return eInputType::PLUS;
	if (isMinus(ch)) return eInputType::MINUS;
	if (isAsterisk(ch)) return eInputType::MULTIPLY;
	if (isDivide(ch)) return eInputType::DIVIDE;
	if (isEqualSign(ch)) return eInputType::EQUAL;
	if (isLeftAngle(ch)) return eInputType::LEFT_ANGLE;
	if (isRightAngle(ch)) return eInputType::RIGHT_ANGLE;
	if (isSemiColon(ch)) return eInputType::SEMI_COLON;
	if (isComma(ch)) return eInputType::COMMA;
	if (isOpenParen(ch)) return eInputType::OPEN_PAREN;
	if (isCloseParen(ch)) return eInputType::CLOSE_PAREN;
	if (isAlpha(ch)) return eInputType::LETTER;
	if (isDigit(ch)) return eInputType::DIGIT;
	if (isUnderScore(ch)) return eInputType::UNDERSCORE;
	if (isPeriod(ch)) return eInputType::PERIOD;
	if (isSpace(ch)) return eInputType::SPACE;
	if (isSemiColon(ch))  return eInputType::SEMI_COLON;
	if (isExcl(ch)) return eInputType::EXCLAMATION;
	if (isComma(ch)) return eInputType::COMMA;
	else return eInputType::UNKNOWN;
}

