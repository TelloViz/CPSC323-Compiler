//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <iterator>
//#include <unordered_map>
//#include <map>
//#include <stack>
//
//
//#define PrintStatePath
//
//
//#pragma region Boolean Utility Functions
//bool isAlpha(char ch) { return std::isalpha(ch); }
//bool isDigit(char ch) { return std::isdigit(ch); }
//bool isUnderScore(char ch) { return ch == '_'; }
//bool isPeriod(char ch) { return ch == '.'; }
//bool isSpace(char ch) { return ch == ' '; }
//bool isReturn(char ch) { return ch == '\n'; }
//bool isTab(char ch) { return ch == '\t'; }
//bool isOpenParen(char ch) { return ch == '('; }
//bool isCloseParen(char ch) { return ch == ')'; }
//bool isOpenBracket(char ch) { return ch == '{'; }
//bool iscloseBracket(char ch) { return ch == '}'; }
//bool isPlus(char ch) { return ch == '+'; }
//bool isMinus(char ch) { return ch == '-'; }
//bool isAsterisk(char ch) { return ch == '*'; }
//bool isDivide(char ch) { return ch == '/'; }
//bool isEqualSign(char ch) { return ch == '='; }
//bool isLeftAngle(char ch) { return ch == '<'; }
//bool isRightAngle(char ch) { return ch == '>'; }
//bool isSemiColon(char ch) { return ch == ';'; }
//bool isComma(char ch) { return ch == ','; }
//#pragma endregion
//
//
//// These enumerations need to correspond with the column of the particular input character
//enum eInputType { LETTER = 1, DIGIT = 2, UNDERSCORE = 3, PERIOD = 4, SPACE = 5, UNKNOWN = 8 };
//eInputType GetInputType(char ch);
//
//enum eTokenType { IDENTIFIER, INTEGER, REAL, NONE};
//
//#pragma region State Table
//// This table maps fairly intuitively.
//// Starting from the top left corner on [0][0]...
//// Scan across the row for your desired input...
//// Note the number stored at the position of your desired input.
//// This number is our resulting state of that particular input
//// from our current state
//
//int stateTable[9][6] =
//{/*			   L  D  _  .  Sp */
//	/*S0*/    0, 1, 2, 8, 8, 0,		// Starting State		
//	/*S1*/	1, 1, 1, 1, 5, 5,		// In Identifier	 <Accept>	
//	/*S2*/	2, 6, 2, 6, 3,	6,		// In Number		 <Accept>
//	/*S3*/	3, 8, 4, 8, 8,	8,		// Incomplete Real		
//	/*S4*/	4, 6, 4, 7, 7,	7,		// In Real		 <Accept>	
//	/*S5*/	5, 0, 0, 0, 0,	0,		// End of Identifier <Accept>	[Back Up]
//	/*S6*/    6, 0, 0, 0, 0, 0,        // End Number		 <Accept>	[Back Up]
//	/*S7*/    7, 0, 0, 0, 0, 0,		// End Real		 <Accept>	[Back Up]
//	/*S8*/	8, 8, 8, 8, 8, 8		// Unknown result
//};
//
////							  s0     s1     s2     s3     s4     s5     s6     s7     s8    s9
//std::vector<bool> isAcceptState = { false, true,  true,  false, true,  true,  true, true,   false, false};
//std::vector<bool> isBackupState = { false, false, false, false, false, true,  true, true,   false, false };
//std::vector<eTokenType> eTokenLookUp = { NONE, IDENTIFIER, INTEGER, NONE, REAL, IDENTIFIER, INTEGER, REAL, NONE };
//
//std::map<eTokenType, std::string> Token_To_String_Map{ {IDENTIFIER, "identifier"}, {INTEGER, "integer"}, {REAL, "real"}, {NONE, "none"} };
//
//#pragma endregion
//
//
//void PrintGraphIteration(int currentState, char inputChar)
//{
//	std::cout << "(" << currentState << ")--" << inputChar << "-->";
//}
//
//void PrintInt(int num) { std::cout << num; }
//
//std::string source{ "    Josh James Lollis" }; 
//
//std::string::iterator currCharIter{ source.begin() };
//std::string::iterator tokenStartIter{ source.begin() };
//
//std::stack<std::string::iterator> inputHistoryQ;
//std::stack<int> stateHistoryQ;
//
//
//bool Lexer(std::string& token, std::string& lexeme)
//{
//	
//	// First are we looking at a valid char or eof?
//	bool isEOF{ currCharIter == source.end() };
//	bool isEOT{ false };
//
//
//	char currCharCopy;
//	if(!isEOF) currCharCopy =  *currCharIter ;
//	int currentState{ 0 };
//
//
//	std::string foundToken;
//	std::string foundTokenString;
//	eTokenType foundTokenType;
//	while (!isEOF && !isEOT)
//	{		
//
//		eInputType inputType = GetInputType(currCharCopy);		// Get the current input chars eInputType (enum)
//
//
//
//		// currState:inputType->destState 
//		// (The state the table will be in with the given state and input
//		int destState = stateTable[currentState][inputType];		
//		
//
//
//
//
//
//		// If the destination is a backup state, 
//		// we can just stay here and accept this as it is in this state
//		if (isBackupState.at(destState))
//		{	
//			/*NOTE: At this point destState will be index to the Backup State
//					currState will be the state the machine was in just prior to the backup state */
//
//			isEOT = true;
//			
//			foundTokenType = eTokenLookUp[destState];		// look up token type assert(could use destState or currState interchangeably here) 
//													//	See vector tables above
//			
//			
//			foundTokenString = Token_To_String_Map.at(foundTokenType);
//			
//			token = foundTokenString;
//			lexeme = std::string(tokenStartIter, currCharIter);
//		}
//		//else if ((currCharIter+1) != source.end()) // TODO trace the program and check thsi function. I don't think this seems sound
//		//{
//
//		//	currentState = destState;
//		//	currCharCopy = *(++currCharIter); // 
//		//}
//		else
//		{
//			if (isAcceptState[currentState])
//			{
//				
//				isEOT = true;
//				foundTokenType = eTokenLookUp[currentState];
//				foundTokenString = Token_To_String_Map.at(foundTokenType);
//				
//				token = foundTokenString;
//				lexeme = std::string(tokenStartIter, currCharIter);
//			}
//			isEOF = true;
//		}	
//
//		if ((currCharIter + 1) != source.end())
//		{
//			currentState = destState;
//			currCharCopy = *(++currCharIter);
//		}
//
//	}
//	std::cout << foundTokenString;
//	return isEOF;
//}
//
//
//
//
//int main()
//{
//	std::string myToken, myLexeme;
//	
//	bool isEOF{ false };
//	while (!isEOF)
//	{
//		isEOF = Lexer(myToken, myLexeme);
//		std::cout << "\nToken: " << myToken << "\nLexeme: " << myLexeme << "\n\n\n";
//	}
//	
//	std::cout << std::string(20,'\n') ;
//	return 0;
//}// TODO I DON"T THINK STEP BACK IS QUITE WORKING RIGHT
//
//eInputType GetInputType(char ch)
//{
//	if (isAlpha(ch)) return eInputType::LETTER;
//	if (isDigit(ch)) return eInputType::DIGIT;
//	if (isUnderScore(ch)) return eInputType::UNDERSCORE;
//	if (isPeriod(ch)) return eInputType::PERIOD;
//	if (isSpace(ch)) return eInputType::SPACE;
//	else return eInputType::UNKNOWN;
//}

















#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <map>
#include <stack>
#include <cassert>






#pragma region Boolean Utility Functions
bool isAlpha(char ch) { return std::isalpha(ch); }
bool isDigit(char ch) { return std::isdigit(ch); }
bool isUnderScore(char ch) { return ch == '_'; }
bool isPeriod(char ch) { return ch == '.'; }
bool isSpace(char ch) { return ch == ' '; }
bool isReturn(char ch) { return ch == '\n'; }
bool isTab(char ch) { return ch == '\t'; }
bool isOpenParen(char ch) { return ch == '('; }
bool isCloseParen(char ch) { return ch == ')'; }
bool isOpenBracket(char ch) { return ch == '{'; }
bool iscloseBracket(char ch) { return ch == '}'; }
bool isPlus(char ch) { return ch == '+'; }
bool isMinus(char ch) { return ch == '-'; }
bool isAsterisk(char ch) { return ch == '*'; }
bool isDivide(char ch) { return ch == '/'; }
bool isEqualSign(char ch) { return ch == '='; }
bool isLeftAngle(char ch) { return ch == '<'; }
bool isRightAngle(char ch) { return ch == '>'; }
bool isSemiColon(char ch) { return ch == ';'; }
bool isComma(char ch) { return ch == ','; }
#pragma endregion




// These enumerations need to correspond with the column of the particular input character
enum eInputType { LETTER = 1, DIGIT = 2, UNDERSCORE = 3, PERIOD = 4, SPACE = 5, UNKNOWN = 8 };
eInputType GetInputType(char ch);

enum eTokenType { IDENTIFIER, INTEGER, REAL, SEPARATOR, OPERATOR, NONE };

#pragma region State Table
// This table maps fairly intuitively.
// Starting from the top left corner on [0][0]...
// Scan across the row for your desired input...
// Note the number stored at the position of your desired input.
// This number is our resulting state of that particular input
// from our current state

int stateTable[11][6] =
{/*			   L  D  _  .  Sp */
	/*S0*/    0, 1, 2, 8, 8, 0,		// Starting State	 <Accept>	
	/*S1*/	1, 1, 1, 1, 5, 5,		// In Identifier	 <Accept>	
	/*S2*/	2, 6, 2, 6, 3,	6,		// In Number		 <Accept>
	/*S3*/	3, 9, 4, 9, 9,	9,		// Incomplete Real		
	/*S4*/	4, 6, 4, 7, 7,	7,		// In Real		 <Accept>	
	/*S5*/	5, 0, 0, 0, 0,	0,		// End of Identifier <Accept>	[Back Up]
	/*S6*/    6, 0, 0, 0, 0, 0,        // End Number		 <Accept>	[Back Up]
	/*S7*/    7, 0, 0, 0, 0, 0,		// End Real		 <Accept>	[Back Up]
	/*S8*/	8, 10, 10, 10, 10, 10,	// In Unknown result <Accept>
	/*S9*/	9, 0, 0, 0, 0, 0,		// Reals Invalid			[Double Back up]
	/*S10*/  10, 0, 0, 0, 0, 0		// End Unknown		<Accept>  [Back up]		
};

//								    s0    s1     s2     s3     s4     s5     s6     s7     s8    s9	 s10
std::vector<bool> isAcceptState =		{ true, true,  true,  false, true,  true,  true, true,  true, false, true };
std::vector<bool> isBackupState =		{ false, false, false, false, false, true,  true, true,  true, true, true };
std::vector<bool> isDoubleBackupState = { false, false, false, false, false, false, false,false, false, true, false };
std::vector<eTokenType> eTokenLookUp = { NONE, IDENTIFIER, INTEGER, NONE, REAL, IDENTIFIER, INTEGER, REAL, NONE, NONE, NONE };

std::map<eTokenType, std::string> Token_To_String_Map{ {IDENTIFIER, "identifier"}, {INTEGER, "integer"}, {REAL, "real"}, {SEPARATOR, "separator"}, {OPERATOR, "operator"}, {NONE, "none"} };

#pragma endregion


void PrintGraphIteration(int currentState, char inputChar)
{
	std::cout << "(" << currentState << ")--" << inputChar << "-->";
}


std::string source{ " 24 ...35  " };

std::string::iterator currCharIter{ source.begin() };
std::string::iterator tokenStartIter{ source.begin() };

std::stack<std::string::iterator> inputHistoryQ;
std::stack<int> stateHistoryQ;

bool Lexer(std::string& token, std::string& lexeme);

int main()
{

	std::string myToken, myLexeme;

	bool isEOF{ false };
	while (!isEOF)
	{
		isEOF = Lexer(myToken, myLexeme);
		if (myToken.empty() || myLexeme.empty())
		{

		}
		else	std::cout << "\nToken: " << myToken << "\nLexeme: " << myLexeme << "\n\n\n";
	}

	std::cout << std::string(20, '\n');
	return 0;
}

















bool Lexer(std::string& token, std::string& lexeme)
{

	lexeme = "";
	token = "";

	std::stack<char> INPUT_STACK;
	std::stack<int> STATE_STACK;
	std::stack<char> LEXEME_QUEUE;



	// End of Token :: true means the end of a token has been discovered
	bool isEOT{ false };
	bool isEOF{ false };


	// just a copy of the character at the current source position
	char currCharCopy;

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
			//isEOT = true;
		}
		else currCharCopy = *currCharIter;
	}


	// Check up front for potential EOF


	while (!isEOT && !isEOF)
	{

		// NOTE:

		/*     currState:inputType->destState     */

		//STATE_STACK.push(currentState);
		//LEXEME_QUEUE.push(currCharCopy);

		eInputType inputType = GetInputType(currCharCopy);	// Get the current input chars eInputType (enum)	
		INPUT_STACK.push(currCharCopy);

		

		STATE_STACK.push(currentState);
		LEXEME_QUEUE.push(currCharCopy);

		if (isBackupState.at(currentState))
		{

			isEOT = true;
			STATE_STACK.pop();
			LEXEME_QUEUE.pop();
			//--currCharIter;

			if (isDoubleBackupState.at(currentState))
			{
				assert(!STATE_STACK.empty());
				STATE_STACK.pop();
				assert(!LEXEME_QUEUE.empty());
				LEXEME_QUEUE.pop();
				assert(!LEXEME_QUEUE.empty());
				LEXEME_QUEUE.pop();
				--currCharIter;
				--currCharIter;
			}
			

		}		
		else
		{

			auto next = currCharIter + 1;
			if (next == source.end())
			{
				isEOF = true;
				isEOT = true;
			}
			else
			{
				currCharIter++;
				int destState = stateTable[currentState][inputType]; // Get resulting destination state
				currentState = destState;
				currCharCopy = *currCharIter;
			}
			
			

		}



	} // END OF LEXER WHILE LOOP


	if (isEOT)
	{
		if (isAcceptState.at(STATE_STACK.top()))
		{
			
			while (!LEXEME_QUEUE.empty()) // Use LEXEME_QUEUE to populate param Lexeme string
			{
				lexeme.push_back(LEXEME_QUEUE.top());
				LEXEME_QUEUE.pop();
			}
			std::reverse(lexeme.begin(), lexeme.end());

				eTokenType tokType = eTokenLookUp.at(STATE_STACK.top());
			token = Token_To_String_Map.at(tokType);


		}
	}

	return isEOF;		// Return the end of file status, this will be the lexers signal that its done

} // END OF LEXER FUNCTION

eInputType GetInputType(char ch)
{
	if (isAlpha(ch)) return eInputType::LETTER;
	if (isDigit(ch)) return eInputType::DIGIT;
	if (isUnderScore(ch)) return eInputType::UNDERSCORE;
	if (isPeriod(ch)) return eInputType::PERIOD;
	if (isSpace(ch)) return eInputType::SPACE;
	else return eInputType::UNKNOWN;
}
