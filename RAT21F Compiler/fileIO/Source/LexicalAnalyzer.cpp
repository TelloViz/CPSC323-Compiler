//#include "../Include/LexicalAnalyzer.h"
//
//#pragma region Boolean Utility Functions
//bool isAlpha(char ch) { return std::isalpha(ch); }
//bool isDigit(char ch) { return std::isdigit(ch); }
//bool isUnderScore(char ch) { return ch == '_'; }
//bool isPeriod(char ch) { return ch == '.'; }
//bool isExcl(char ch) { return ch == '!'; }
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
//bool LexicalAnalyzer::Lexer(std::string& token, std::string& lexeme)
//{
//	eInputType inputType;
//	lexeme = "";
//	token = "";
//
//	std::stack<char> INPUT_STACK;
//	std::stack<int> STATE_STACK;
//	std::stack<char> LEXEME_QUEUE;
//
//
//
//	// End of Token :: true means the end of a token has been discovered
//	bool isEOT{ false };
//	bool isEOF{ false };
//
//
//	// just a copy of the character at the current source position
//	char currCharCopy;
//
//	// Verify iterator validity then copy value pointed to by iterator 
//	if (!isEOF) currCharCopy = *currCharIter;
//
//	// sets default state to 0 each call to Lexer;
//	int currentState{ 0 };
//
//
//	// Lexer scoped strings for storing the values uncovered in analysis
//	std::string foundToken, foundTokenString;
//
//	// An enumeration for tranlating token types 
//	eTokenType foundTokenType;
//
//
//	// prepare a flag for when backups are needed in the loop
//	bool shouldBackUp{ false };
//
//
//	// This while loop will skip any leading white 
//	// space on any give lexer call
//	while (!isEOF && isSpace(currCharCopy))
//	{
//		++currCharIter;
//		if (currCharIter == source.end())
//		{
//			isEOF = true;
//			//isEOT = true;
//		}
//		else currCharCopy = *currCharIter;
//	}
//
//	// Before we start processing, simply check if the character is a simple operator or separator
//	// If so we can skip the state table altogether.
//	eInputType precheckInputType = GetInputType(currCharCopy);
//	bool isPreChecked{ false };
//	switch (precheckInputType)
//	{
//	case UNDERSCORE:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "_";
//		token = Token_To_String_Map.at(NONE);
//		break;
//	case PERIOD:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = ".";
//		token = Token_To_String_Map.at(NONE);
//		break;
//	case OPEN_PAREN:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "(";
//		token = Token_To_String_Map.at(SEPARATOR);
//		break;
//	case CLOSE_PAREN:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = ")";
//		token = Token_To_String_Map.at(SEPARATOR);
//		break;
//	case UNKNOWN:
//		isEOT = true;
//		isPreChecked = true;
//		token = Token_To_String_Map.at(NONE);
//		break;
//	case OPEN_BRACKET:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "{";
//		token = Token_To_String_Map.at(SEPARATOR);
//		break;
//	case CLOSE_BRACKET:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "}";
//		token = Token_To_String_Map.at(SEPARATOR);
//		break;
//	case PLUS:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "+";
//		token = Token_To_String_Map.at(OPERATOR);
//		break;
//	case MINUS:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "-";
//		token = Token_To_String_Map.at(OPERATOR);
//		break;
//	case MULTIPLY:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = "*";
//		token = Token_To_String_Map.at(OPERATOR);
//		break;
//	case SEMI_COLON:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = ";";
//		token = Token_To_String_Map.at(SEPARATOR);
//		break;
//	case COMMA:
//		isEOT = true;
//		isPreChecked = true;
//		lexeme = ",";
//		token = Token_To_String_Map.at(SEPARATOR);
//		break;
//	default:
//		break;
//	}
//
//
//	while (!isEOT && !isEOF)
//	{
//		if (currCharIter == source.end())
//		{
//			isEOF = true;
//			isEOT = true;
//
//		}
//		if (isEOF) break;
//		// NOTE:
//
//		/*     currState:inputType->destState     */
//
//		//STATE_STACK.push(currentState);
//		//LEXEME_QUEUE.push(currCharCopy);
//
//		//eInputType inputType = GetInputType(currCharCopy);	// Get the current input chars eInputType (enum)	
//		//INPUT_STACK.push(currCharCopy);
//
//
//
//		/*STATE_STACK.push(currentState);
//		LEXEME_QUEUE.push(currCharCopy);*/
//		STATE_STACK.push(currentState);
//		if (isBackupState.at(currentState))
//		{
//
//			isEOT = true;
//			STATE_STACK.pop();
//			LEXEME_QUEUE.pop();
//			--currCharIter;
//
//			if (isDoubleBackupState.at(currentState))
//			{
//				assert(!STATE_STACK.empty());
//				STATE_STACK.pop();
//				assert(!LEXEME_QUEUE.empty());
//				LEXEME_QUEUE.pop();
//				assert(!LEXEME_QUEUE.empty());
//				LEXEME_QUEUE.pop();
//				--currCharIter;
//				--currCharIter;
//			}
//
//
//		}
//		else
//		{
//
//			/*auto next = currCharIter + 1;
//			if (next == source.end())
//			{
//				isEOF = true;
//				isEOT = true;
//			}*/
//			//else
//			//{
//
//
//				//STATE_STACK.push(currentState);
//			LEXEME_QUEUE.push(currCharCopy);
//
//			inputType = GetInputType(currCharCopy);	// Get the current input chars eInputType (enum)	
//			INPUT_STACK.push(currCharCopy);
//			int destState = stateTable[currentState][inputType]; // Get resulting destination state
//
//			currCharIter++;
//			if (currCharIter == source.end()) { STATE_STACK.push(destState); }
//			else {
//
//				currentState = destState;
//				currCharCopy = *currCharIter;
//			}
//
//			//}
//
//
//
//		}
//
//
//
//	} // END OF LEXER WHILE LOOP
//
//
//	if (isEOT)
//	{
//		if (!isPreChecked && isAcceptState.at(STATE_STACK.top()))
//		{
//
//			while (!LEXEME_QUEUE.empty()) // Use LEXEME_QUEUE to populate param Lexeme string
//			{
//				lexeme.push_back(LEXEME_QUEUE.top());
//				LEXEME_QUEUE.pop();
//			}
//			std::reverse(lexeme.begin(), lexeme.end());
//
//			eTokenType tokType = eTokenLookUp.at(STATE_STACK.top());
//			token = Token_To_String_Map.at(tokType);
//
//
//		}
//
//		if (isPreChecked)
//		{
//			++currCharIter;
//		}
//	}
//
//	return isEOF;		// Return the end of file status, this will be the lexers signal that its done
//
//}
//
//
//
//
//LexicalAnalyzer::eInputType LexicalAnalyzer::GetInputType(char ch)
//{
//	if (isOpenBracket(ch)) return eInputType::OPEN_BRACKET;
//	if (iscloseBracket(ch)) return eInputType::CLOSE_BRACKET;
//	if (isPlus(ch)) return eInputType::PLUS;
//	if (isMinus(ch)) return eInputType::MINUS;
//	if (isAsterisk(ch)) return eInputType::MULTIPLY;
//	if (isDivide(ch)) return eInputType::DIVIDE;
//	if (isEqualSign(ch)) return eInputType::EQUAL;
//	if (isLeftAngle(ch)) return eInputType::LEFT_ANGLE;
//	if (isRightAngle(ch)) return eInputType::RIGHT_ANGLE;
//	if (isSemiColon(ch)) return eInputType::SEMI_COLON;
//	if (isComma(ch)) return eInputType::COMMA;
//	if (isOpenParen(ch)) return eInputType::OPEN_PAREN;
//	if (isCloseParen(ch)) return eInputType::CLOSE_PAREN;
//	if (isAlpha(ch)) return eInputType::LETTER;
//	if (isDigit(ch)) return eInputType::DIGIT;
//	if (isUnderScore(ch)) return eInputType::UNDERSCORE;
//	if (isPeriod(ch)) return eInputType::PERIOD;
//	if (isSpace(ch)) return eInputType::SPACE;
//	if (isSemiColon(ch))  return eInputType::SEMI_COLON;
//	if (isExcl(ch)) return eInputType::EXCLAMATION;
//	if (isComma(ch)) return eInputType::COMMA;
//	else return eInputType::UNKNOWN;
//}
//
