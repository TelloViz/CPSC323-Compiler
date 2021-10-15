#pragma once


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


class LexicalAnalyzer
{
public:

	LexicalAnalyzer(std::string sourceString);
	bool Lexer(std::string& token, std::string& lexeme);
private:
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
		LETTER = 1, DIGIT = 2, UNDERSCORE = 3, PERIOD = 4, SPACE = 5,
		OPEN_PAREN = 6, CLOSE_PAREN = 7, UNKNOWN = 8, OPEN_BRACKET = 9, CLOSE_BRACKET = 10,
		PLUS = 11, MINUS = 12, MULTIPLY = 13, DIVIDE = 14, EQUAL = 15,
		LEFT_ANGLE = 16, RIGHT_ANGLE = 17, SEMI_COLON = 18, COMMA = 19, EXCLAMATION = 20

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
	{//                 L    D    _    .    SP   (     )    UNK   {      }    +     -     *     /     =     <     >     ;     ,     !
		/*S0*/    0,   1,   2,   8,   8,   0,   11,   13,   8,   15,   17,   19,   21,   23,   25,   27,   33,   35,   39,   41,   41, // (S0)START								<Accept>					
		/*S1*/    1,	1,	1,	1,	5,	5,	 5,	  5,	  5,	   5,    5,	5,	 5,	  5,    5,    5,    5,    5,    5,    5,    5, // (S1)IN IDENTIFIER						<Accept>					
		/*S2*/    2,	6,	2,	6,	3,	6,	 6,	  6,	  6,    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,    6, // (S2)IN NUMBER							<Accept>					
		/*S3*/    3,   9,   4,   9,   9,   9,    9,    9,   9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9, // (S3)INCOMPLETE REAL
		/*S4*/    4,   6,	4,	7,	7,	7,	 7,	  7,	  7,	   7,    7,    7,    7,    7,    7,    7,    7,    7,    7,    7,    7, // (S4)IN REAL							<Accept>
		/*S5*/    5,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S5)END IDENTIFIER		[Back Up]			<Accept>
		/*S6*/    6,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S6)END NUMBER			[Back Up]			<Accept>
		/*S7*/    7,   0,	0,   0,   9,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S7)END REAL			[Back Up]			<Accept>
		/*S8*/    8,  10,  10,  10,  10,  10,   10,   10,  10,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,   10, // (S8)IN UNKNOWN							<Accept>
		/*S9*/    9,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S9)REAL INVALID		[Double Back Up]    <Accept>
		/*S10*/  10,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S10)END UNKNOWN		[Back Up]			<Accept>
		/*S11*/  11,  12,  12,  12,  12,  12,   12,   12,  12,   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,   12, // (S11)IN (								<Accept>
		/*S12*/  12,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S12)END (			[Back Up]			<Accept>
		/*S13*/  13,  14,  14,  14,  14,  14,   14,   14,  14,   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,   14, // (S13)IN )								<Accept>
		/*S14*/  14,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S14)END )			[Back Up]			<Accept>
		/*S15*/  15,  16,  16,  16,  16,  16,   16,   16,  16,   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,   16, // (S15)IN {								<Accept>
		/*S16*/  16,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S16)END {			[Back Up]			<Accept>
		/*S17*/  17,  18,  18,  18,  18,  18,   18,   18,  18,   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,   18, // (S17)IN }								<Accept>
		/*S18*/  18,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S18)END }			[Back Up]			<Accept>
		/*S19*/  19,  20,  20,  20,  20,  20,   20,   20,  20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20,   20, // (S19)IN +								<Accept>
		/*S20*/  20,   0,   0,   0,   0,   0,    0,    0,   0,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22, // (S20)END +			[Back Up]			<Accept>
		/*S21*/  21,  22,  22,  22,  22,  22,   22,   22,  22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,   22, // (S21)IN -								<Accept>
		/*S22*/  22,   0,   0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S22)END -			[Back Up]			<Accept>
		/*S23*/  23,  24,  24,  24,  24,  24,   24,   24,  24,   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,   24, // (S23)IN *								<Accept>
		/*S24*/  24,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S24)END *			[Back Up]			<Accept>
		/*S25*/  25,  26,  26,  26,  26,  26,   26,   26,  26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26,   26, // (S25)IN /								<Accept>
		/*S26*/  26,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S26)END /			[Back Up]			<Accept>
		/*S27*/  27,  28,  28,  28,  28,  28,   28,   28,  28,   28,   28,   28,   28,   28,   28,   29,   28,   31,   28,   28,   28, // (S27)IN =								<Accept>
		/*S28*/  28,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S28)END =			[Back Up]			<Accept>
		/*S29*/  29,  30,  30,  30,  30,  30,   30,   30,  30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,   30, // (S29)IN ==							<Accept>
		/*S30*/  30,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S30)END ==			[Back Up]			<Accept>
		/*S31*/  31,  32,  32,  32,  32,  32,   32,   32,  32,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32, // (S31)IN =>							<Accept>
		/*S32*/  32,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S32)END =>			[Back Up]			<Accept>
		/*S33*/  33,  34,  34,  34,  34,  34,   34,   34,  34,   34,   34,   34,   34,   34,   34,   37,   34,   34,   34,   34,   34, // (S33)IN <								<Accept>
		/*S34*/  34,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S34)END <			[Back Up]			<Accept>
		/*S35*/  35,  36,  36,  36,  36,  36,   36,   36,  36,   36,   36,   36,   36,   36,   36,   37,   36,   36,   36,   36,   36, // (S35)IN >								<Accept>
		/*S36*/  36,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S36)END >			[Back Up]			<Accept>
		/*S37*/  37,  38,  38,  38,  38,  38,   38,   38,  38,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38, // (S37)IN <=							<Accept>
		/*S38*/  38,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S38)END <=			[Back Up]			<Accept>
		/*S39*/  39,  40,  40,  40,  40,  40,   40,   40,  40,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40, // (S39)IN ;								<Accept>
		/*S40*/  40,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S40)END ;			[Back Up]			<Accept>
		/*S41*/  41,  42,  42,  42,  42,  42,   42,   42,  42,   42,   42,   42,   42,   42,   42,   45,   42,   42,   42,   42,   42, // (S41)IN ,								<Accept>
		/*S42*/  42,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S42)END ,			[Back Up]			<Accept>
		/*S43*/  43,  44,  44,  44,  44,  44,   44,   44,  44,   44,   44,   44,   44,   44,   44,   45,   44,   44,   44,   44,   44, // (S43)IN !								<Accept>
		/*S44*/  44,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S44)END !			[Back Up]			<Accept>
		/*S45*/  45,  46,  46,  46,  46,  46,   46,   46,  46,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46, // (S45)IN !=							<Accept>
		/*S46*/  46,   0,	0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // (S46)END !=			[Back Up]			<Accept>
	};

	//								    s0    s1      s2       s3     s4     s5     s6     s7     s8     s9    s10   s11   s12     s13     s14	  s15    s16    s17    s18     s19     s20    s21    s22    s23   s24     s25    s26    s27    s28     s29   s30     s31   s32     s33   s34     s35   s36     s37   s38     s39    s40    s41    s42     s43    s44    s45   s46
	std::vector<bool> isAcceptState = { true, true,    true,   false,  true,  true,  true,  true,  true,  true, true,  true, true,   true,  true,    true,  true,  true,  true ,  true,   true ,  true, true , true, true ,  true,   true , true,   true , true,  true , true,  true , true,  true , true, true ,  true, true , true,   true , true, true ,  false, true , true, true };
	std::vector<bool> isBackupState = { false, false, false,   false, false,  true,  true,  true,  false, true, true,  false, true,  false,  true,  false,  true,  false,  true,  false,  true,   false, true,  false, true,  false, true,  false,  true,  false, true,  false, true,  false, true,  false, true,  false, true,  false, true , false, true ,  false, true , false, true };
	std::vector<bool> isDoubleBackupState = { false, false, false,   false, false,  false, false, false, false, true, false, false, false, false,  false, false,  false, false,  false, false,  false,  false, false, false, false, false, false, false,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  false, false, false, false, };

	std::vector<eTokenType> eTokenLookUp = { NONE, IDENTIFIER, INTEGER, NONE, REAL, IDENTIFIER, INTEGER, REAL, NONE, NONE, NONE, SEPARATOR, SEPARATOR, SEPARATOR, SEPARATOR, NONE,  SEPARATOR, NONE, SEPARATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR , OPERATOR, OPERATOR , OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR, SEPARATOR, SEPARATOR, SEPARATOR, SEPARATOR, OPERATOR, OPERATOR, OPERATOR, OPERATOR };
	//								   s0     s1          s2      s3    s4     s5          s6      s7    s8    s9    s10   s11         s12        s13        s14	      s15     s16      s17     s18         s19       s20      s21       s22       s23        s24      s25        s26       s27       s28        s29       s30       s31       s32        s33       s34       s35       s36       s37       s38     s39      s40     s41    s42       s43      s44      s45   s46






	std::map<eTokenType, std::string> Token_To_String_Map{ {IDENTIFIER, "identifier"}, {INTEGER, "integer"}, {REAL, "real"}, {SEPARATOR, "separator"}, {OPERATOR, "operator"}, {NONE, "none"} };

#pragma endregion
#pragma region Keywords
	std::vector<std::string> keywordVec{ "if", "endif", "else", "put", "get", "true", "integer", "boolean", "real", "function", "return", "while", "false" };
#pragma endregion
#pragma region Operators
	std::vector<std::string> compoundOperatorsVec{ "==", "!=", "<=", "=>" };
#pragma endregion


	std::string source; // TODO left off here. recognizing as an integer incorrectly

	std::string::iterator currCharIter{ /*source.begin()*/};
	std::string::iterator tokenStartIter{ /*source.begin()*/ };

	bool isFirstRun{ true };

	
	

};