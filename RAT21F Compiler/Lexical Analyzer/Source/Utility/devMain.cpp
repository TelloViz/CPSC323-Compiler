#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#define PrintStatePath


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

#pragma region State Table
// This table maps fairly intuitively.
// Starting from the top left corner on [0][0]...
// Scan across the row for your desired input...
// Note the number stored at the position of your desired input.
// This number is our resulting state of that particular input
// from our current state

int stateTable[9][6] =
{/*			   L  D  _  .  Sp */
	/*S0*/    0, 1, 2, 8, 8, 1,		// Starting State		
	/*S1*/	1, 1, 1, 1, 5, 5,		// In Identifier	 <Accept>	
	/*S2*/	2, 6, 2, 6, 3,	6,		// In Number		 <Accept>
	/*S3*/	3, 8, 4, 8, 8,	8,		// Incomplete Real		
	/*S4*/	4, 6, 4, 7, 7,	7,		// In Real		 <Accept>	
	/*S5*/	5, 0, 0, 0, 0,	0,		// End of Identifier <Accept>	[Back Up]
	/*S6*/    6, 0, 0, 0, 0, 0,        // End Number		 <Accept>	[Back Up]
	/*S7*/    7, 0, 0, 0, 0, 0,		// End Real		 <Accept>	[Back Up]
	/*S8*/	8, 8, 8, 8, 8, 8		// Unknown result
};

//							s0     s1     s2     s3     s4     s5     s6     s7     s8
std::vector<bool> isAcceptState = {false, true,  true,  false, true,  true, true, true,  false, false};
std::vector<bool> isBackupState = { false, false, false, false, false, true,  true, true,   false, false };


#pragma endregion

// These enumerations need to correspond with the column of the particular input character
enum eInputType{LETTER=1, DIGIT=2, UNDERSCORE=3, PERIOD=4, SPACE=5, UNKNOWN = 8};
eInputType GetInputType(char ch);


void PrintInt(int num) { std::cout << num; }

std::string source{ "abc" };
std::string::iterator currCharIter{ source.begin() };
std::string::iterator tokenStartIter{ source.begin() };

bool Lexer(std::string& token, std::string& lexeme)
{
	
	// First are we looking at a valid char or eof?
	bool isEOF{ currCharIter == source.end() };
	bool isEOT{ false };


	char currCharCopy{ *currCharIter };
	int currentState{ 0 };
	
	PrintInt(currentState);

	std::string foundToken;
	while (!isEOF && !isEOT)
	{
		
		eInputType inputType = GetInputType(currCharCopy);
		int destState = stateTable[currentState][inputType];
		
		// If the destination is a backup state, 
		// we can just stay here and accept this as it is in this state
		if (isBackupState.at(destState))
		{
			//PrintInt(currentState);

			lexeme = std::string(tokenStartIter, currCharIter);
			isEOT = true;
		}
		else if ((++currCharIter) != source.end())
		{
			//PrintInt(currentState);

			currCharCopy = *currCharIter;
			currentState = destState;
		}
		else
		{
			//PrintInt(currentState);

			if (isAcceptState[currentState])
			{
				lexeme = std::string(tokenStartIter, currCharIter);
			}
			isEOF = true;
		}

		std::cout << " --" << currCharCopy << "-->"; // TODO left off here, doesn't quite print right but works prettty good actually
		PrintInt(currentState);

	}
	
	return isEOF;
}




int main()
{
	std::string myToken, myLexeme;
	Lexer(myToken, myLexeme);

	std::cout << "\nToken: " << myToken << " Lexeme: " << myLexeme << std::endl;




	return 0;
}

eInputType GetInputType(char ch)
{
	if (isAlpha(ch)) return eInputType::LETTER;
	if (isDigit(ch)) return eInputType::DIGIT;
	if (isUnderScore(ch)) return eInputType::UNDERSCORE;
	if (isPeriod(ch)) return eInputType::PERIOD;
	if (isSpace(ch)) return eInputType::SPACE;
	else return eInputType::UNKNOWN;
}
