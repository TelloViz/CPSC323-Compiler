
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
bool isExcl(char ch) { return ch == '!'; }
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
enum eInputType 
{ 
	LETTER = 1,	DIGIT = 2,	UNDERSCORE = 3, PERIOD = 4,	  SPACE = 5, 
	OPEN_PAREN=6,	CLOSE_PAREN=7, UNKNOWN = 8,	 OPEN_BRACKET=9, CLOSE_BRACKET=10, 
	PLUS=11,		MINUS=12,		MULTIPLY=13,	 DIVIDE=14,	  EQUAL=15, 
	LEFT_ANGLE, 	RIGHT_ANGLE,	SEMI_COLON,	COMMA, EXCLAMATION 

};
eInputType GetInputType(char ch);


enum eTokenType { IDENTIFIER, INTEGER, REAL, SEPARATOR, OPERATOR, NONE };

#pragma region State Table
// This table maps fairly intuitively.
// Starting from the top left corner on [0][0]...
// Scan across the row for your desired input...
// Note the number stored at the position of your desired input.
// This number is our resulting state of that particular input
// from our current state

//int stateTable[15][8] = // TODO add ; semi-colon to table next, run current source and you'll see why
//{/*			    L   D   _   .   Sp   (    )										*/
//	/*S0*/    0,  1,  2,  8,  8,  0,  11,  13,		// Starting State	 <Accept>	
//	/*S1*/	1,  1,  1,  1,  5,  5,  5,   5,		// In Identifier	 <Accept>	
//	/*S2*/	2,  6,  2,  6,  3,	6,  6,   6,		// In Number		 <Accept>
//	/*S3*/	3,  9,  4,  9,  9,	9,  9,   9,		// Incomplete Real		
//	/*S4*/	4,  6,  4,  7,  7,	7,  7,   7,		// In Real		 <Accept>	
//	/*S5*/	5,  0,  0,  0,  0, 	0,  0,   0,		// End of Identifier <Accept>	 [Back Up]
//	/*S6*/    6,  0,  0,  0,  0,  0,  0,   0,		// End Number		 <Accept>	 [Back Up]
//	/*S7*/    7,  0,  0,  0,  9,  0,  0,   0,		// End Real		 <Accept>	 [Back Up]
//	/*S8*/	8,  10, 10, 10, 10, 10, 10,  10,		// In Unknown result <Accept>
//	/*S9*/	9,  0,  0,  0,  0,  0,  0,   0,		// Reals Invalid			 [Double Back up]
//	/*S10*/  10,  0,  0,  0,  0,  0,  0,   0,		// End Unknown		 <Accept>  [Back up]		
//	/*S11*/  11,  12, 12, 12, 12, 12, 12,  12,		// In (			 <Accept>  
//	/*S12*/  12,  0,  0,  0,  0,  0,  0,   0,		// End (			 <Accept>	 [Back up]
//	/*S13*/  13,  14, 14, 14, 14, 14, 14,  14,		// In )			 <Accept>  
//	/*S14*/  14,  0,  0,  0,  0,  0,  0,   0		// End )			 <Accept>	 [Back up]
//};

int stateTable[47][21] = 
{//                 L    D    _    .    SP   (     )    UNK   {      }    +     -     *     /     =     >     <     ;     ,     !
	/*S0*/    0,   1,   2,   8,   8,   0,   11,   13,   8,   15,   17,   19,   21,   23,   25,   27,   33,   35,   39,   41,   41, // (S0)START								
	/*S1*/    1,	1,	1,	1,	5,	5,	 5,	  5,	  5,	   5,    5,	5,	 5,	  5,    5,    5,    5,    5,    5,    5,    5, // (S1)IN IDENTIFIER						
	/*S2*/    2,	6,	2,	6,	3,	6,	 6,	  6,	  6,    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,    6, // (S2)IN NUMBER							
	/*S3*/    3,   9,   4,   9,   9,   9,    9,    9,   9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9, // (S3)INCOMPLETE REAL
	/*S4*/    4,   6,	4,	7,	7,	7,	 7,	  7,	  7,	   7,    7,    7,    7,    7,    7,    7,    7,    7,    7,    7,    7, // (S4)IN REAL
	/*S5*/    5,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S5)END IDENTIFIER		[Back Up]			<Accept>
	/*S6*/    6,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S6)END NUMBER			[Back Up]			<Accept>
	/*S7*/    7,   0,	0,   0,   9,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S7)END REAL			[Back Up]			<Accept>
	/*S8*/    8,  10,  10,  10,  10,  10,   10,   10,  10,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10, // (S8)IN UNKNOWN
	/*S9*/    9,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S9)REAL INVALID		[Double Back Up]    <Accept>
	/*S10*/  10,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S10)END UNKNOWN		[Back Up]			<Accept>
	/*S11*/  11,  12,  12,  12,  12,  12,   12,   12,  12,   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,   12, // (S11)IN (
	/*S12*/  12,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S12)END (			[Back Up]			<Accept>
	/*S13*/  13,  14,  14,  14,  14,  14,   14,   14,  14,   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,   14, // (S13)IN )
	/*S14*/  14,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S14)END )			[Back Up]			<Accept>
	/*S15*/  15,  16,  16,  16,  16,  16,   16,   16,  16,   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,   16, // (S15)IN {
	/*S16*/  16,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S16)END {			[Back Up]			<Accept>
	/*S17*/  17,  18,  18,  18,  18,  18,   18,   18,  18,   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,   18, // (S17)IN }
	/*S18*/  18,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S18)END }			[Back Up]			<Accept>
	/*S19*/  19,  20,  20,  20,  20,  20,   20,   20,  20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20, // (S19)IN +
	/*S20*/  20,   0,   0,   0,   0,   0,    0,    0,   0,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22, // (S20)END +			[Back Up]			<Accept>
	/*S21*/  21,  22,  22,  22,  22,  22,   22,   22,  22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22, // (S21)IN -
	/*S22*/  22,   0,   0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S22)END -			[Back Up]			<Accept>
	/*S23*/  23,  24,  24,  24,  24,  24,   24,   24,  24,   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,   24, // (S23)IN *
	/*S24*/  24,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S24)END *			[Back Up]			<Accept>
	/*S25*/  25,  26,  26,  26,  26,  26,   26,   26,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26, // (S25)IN /
	/*S26*/  26,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S26)END /			[Back Up]			<Accept>
	/*S27*/  27,  28,  28,  28,  28,  28,   28,   28,  28,   28,   28,   28,   28,   28,   28,   29,   28,   31,   28,   28,   28, // (S27)IN =
	/*S28*/  28,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S28)END =			[Back Up]			<Accept>
	/*S29*/  29,  30,  30,  30,  30,  30,   30,   30,  30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30, // (S29)IN ==
	/*S30*/  30,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S30)END ==			[Back Up]			<Accept>
	/*S31*/  31,  32,  32,  32,  32,  32,   32,   32,  32,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32, // (S31)IN =>
	/*S32*/  32,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S32)END =>			[Back Up]			 <Accept>
	/*S33*/  33,  34,  34,  34,  34,  34,   34,   34,  34,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34, // (S33)IN >
	/*S34*/  34,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S34)END >			[Back Up]			<Accept>
	/*S35*/  35,  36,  36,  36,  36,  36,   36,   36,  36,   36,   36,   36,   36,   36,   36,   37,   36,   36,   36,   36,   36, // (S35)IN <
	/*S36*/  36,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S36)END <			[Back Up]			<Accept>
	/*S37*/  37,  38,  38,  38,  38,  38,   38,   38,  38,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38, // (S37)IN <=
	/*S38*/  38,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S38)END <=			[Back Up]			<Accept>
	/*S39*/  39,  40,  40,  40,  40,  40,   40,   40,  40,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40, // (S39)IN ;
	/*S40*/  40,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S40)END ;			[Back Up]			<Accept>
	/*S41*/  41,  42,  42,  42,  42,  42,   42,   42,  42,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42, // (S41)IN ,
	/*S42*/  42,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S42)END ,			[Back Up]			<Accept>
	/*S43*/  43,  44,  44,  44,  44,  44,   44,   44,  44,   44,   44,   44,   44,   44,   44,   45,   44,   44,   44,   44,   44, // (S43)IN !
	/*S44*/  44,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S44)END !			[Back Up]			<Accept>
	/*S45*/  45,  46,  46,  46,  46,  46,   46,   46,  46,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46, // (S45)IN !=
	/*S46*/  46,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S46)END !=			[Back Up]			 <Accept>
}

//								    s0    s1      s2       s3     s4     s5     s6    s7     s8     s9    s10   s11   s12     s13    s14	  s15    s16    s17  s18     s19    s20    s21    s22    s23   s24     s25    s26    s27    s28     s29   s30     s31   s32     s33   s34     s35   s36     s37   s38     s39    s40    s41    s42     s43    s44    s45   s46
std::vector<bool> isAcceptState =		{ false, false,  false,  false, false,  true,  true, true,  false, true, true, false, true,  false,  true, false, true, false,true , false, true , false, true , false, true , false, true , false,  true , false, true , false, true , false, true , false, true , false, true , false, true , false, true ,  false, true , false, true};
std::vector<bool> isBackupState =		{ false, false, false, false, false, true,  true, true,  false, true, true, false, true, false, true };
std::vector<bool> isDoubleBackupState = { false, false, false, false, false, false, false,false, false, true, false, false, false, false, false };
std::vector<eTokenType> eTokenLookUp = {  NONE, IDENTIFIER, INTEGER, NONE, REAL, IDENTIFIER, INTEGER, REAL, NONE, NONE, NONE, SEPARATOR, SEPARATOR, SEPARATOR, SEPARATOR };

std::map<eTokenType, std::string> Token_To_String_Map{ {IDENTIFIER, "identifier"}, {INTEGER, "integer"}, {REAL, "real"}, {SEPARATOR, "separator"}, {OPERATOR, "operator"}, {NONE, "none"} };

#pragma endregion


#pragma region Keywords
std::vector<std::string> keywordVec{ "if", "endif", "else", "put", "get", "true", "integer", "boolean", "real", "function", "return", "while", "false"};
#pragma endregion

#pragma region Operators
std::vector<std::string> compoundOperatorsVec{ "==", "!=", "<=", "=>" };
#pragma endregion


std::string source{ ";,*+><====>" }; // TODO left off here. recognizing as an integer incorrectly

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
	eInputType inputType;
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

	// Before we start processing, simply check if the character is a simple operator or separator
	// If so we can skip the state table altogether.
	eInputType precheckInputType = GetInputType(currCharCopy);
	bool isPreChecked{ false };
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
	//case SPACE:
	//	//do nothing
	//	isEOT = true;
	//	break;
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
		break;;
	case PLUS:
		break;
	case MINUS:
		break;
	case MULTIPLY:
		break;
	case DIVIDE:
		break;
	case EQUAL: // TODO this one is only here for debugging the rest, this is a special case needinging handling elswhere
		isEOT = true;
		isPreChecked = true;
		lexeme = "=";
		token = Token_To_String_Map.at(OPERATOR);
		break;
	case LEFT_ANGLE:
		isEOT = true;
		isPreChecked = true;
		lexeme = "<";
		token = Token_To_String_Map.at(OPERATOR);
		break;
	case RIGHT_ANGLE:
		break;
	case SEMI_COLON:
		isEOT = true;
		isPreChecked = true;
		lexeme = ";";
		token = Token_To_String_Map.at(SEPARATOR);
		break;
	case COMMA:
		break;
	default:
		break;
	}


	while (!isEOT && !isEOF)
	{
		if (currCharIter == source.end())
		{
			isEOF = true;
			isEOT = true;
			
		}
		if (isEOF) break;
		// NOTE:

		/*     currState:inputType->destState     */

		//STATE_STACK.push(currentState);
		//LEXEME_QUEUE.push(currCharCopy);

		//eInputType inputType = GetInputType(currCharCopy);	// Get the current input chars eInputType (enum)	
		//INPUT_STACK.push(currCharCopy);

		

		/*STATE_STACK.push(currentState);
		LEXEME_QUEUE.push(currCharCopy);*/
		STATE_STACK.push(currentState);
		if (isBackupState.at(currentState))
		{

			isEOT = true;
			STATE_STACK.pop();
			LEXEME_QUEUE.pop();
			--currCharIter;

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

			/*auto next = currCharIter + 1;
			if (next == source.end())
			{
				isEOF = true;
				isEOT = true;
			}*/
			//else
			//{


				//STATE_STACK.push(currentState);
				LEXEME_QUEUE.push(currCharCopy);

				inputType  = GetInputType(currCharCopy);	// Get the current input chars eInputType (enum)	
				INPUT_STACK.push(currCharCopy);

				currCharIter++;
				if (currCharIter == source.end()) {}
				else {
					int destState = stateTable[currentState][inputType]; // Get resulting destination state
					currentState = destState;
					currCharCopy = *currCharIter;
				}
				
			//}
			
			

		}



	} // END OF LEXER WHILE LOOP


	if (isEOT)
	{
		if (!isPreChecked && isAcceptState.at(STATE_STACK.top()))
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

		if (isPreChecked)
		{
			++currCharIter;
		}
	}

	return isEOF;		// Return the end of file status, this will be the lexers signal that its done

} // END OF LEXER FUNCTION

eInputType GetInputType(char ch)
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
	else return eInputType::UNKNOWN;
}
