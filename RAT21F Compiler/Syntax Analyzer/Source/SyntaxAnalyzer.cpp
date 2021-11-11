// SyntaxAnalyzer.cpp

/* This file holds the implementation details for the Syntax Analyzer class.
// It is also home to the #defines that toggle various modes of output,
// including color and slow-mode

// The Syntax analyzer is built from a Backus-Naur grammar listing of Rat21F.
// I've removed left recursion and factored where needed.

Author: Josh Lollis
Project 2 Syntax Analysis
CPSC-323 Fall 2021

Last Edit: 11/10/21

*/


#include "../Include/SyntaxAnalyzer.h"




/* Use these defines to toggle different modes of output text*/
// There are two pairs of toggles, one for Printing Non-Termainals on function call entry
// the other is to print the rull as it is accepted at the deepest nest of the function.
// both can be on at the same time and both have a verbose option
// the verbose option requires the both of the #define in the pair to be active
// ******************************************************************************************

#ifndef PRINT_RULE_ON_CALL
#define PRINT_RULE_ON_CALL // Comment out ths line to turn off
#endif

#ifndef VERBOSE_PRINT_RULE_ON_CALL	// Both modes must be defined for Verbose to work
#define VERBOSE_PRINT_RULE_ON_CALL  // Comment out ths line to turn off	
#endif
//*****************************************************************************************
#ifndef PRINT_RULE_ON_ACCEPT
#define PRINT_RULE_ON_ACCEPT
#endif

#ifndef VERBOSE_PRINT_RULE_ON_ACCEPT	// Both modes must be defined for Verbose to work
#define VERBOSE_PRINT_RULE_ON_ACCEPT	// Comment out ths line to turn off
#endif
// **********************************************************************************************

//*****************************************************************************************
#ifndef PRINT_RULE_ON_REJECT
#define PRINT_RULE_ON_REJECT
#endif

#ifndef VERBOSE_PRINT_RULE_ON_REJECT	// Both modes must be defined for Verbose to work
#define VERBOSE_PRINT_RULE_ON_REJECT	// Comment out ths line to turn off
#endif
// **********************************************************************************************

#ifndef PRINT_RECOGNIZE_LABEL
#define PRINT_RECOGNIZE_LABEL	// Comment out ths line to turn off
#endif // !PRINT_RECOGNIZE_LABEL


#ifndef SLOW_MODE
//#define SLOW_MODE		// Comment out ths line to turn off
#endif // !SLOW_MODE

#ifndef COLOR_MODE
#define COLOR_MODE		// Comment out ths line to turn off
#endif // !COLOR_MODE

// *********************************************************************************************

#pragma region Do Not Edit This Region
#ifdef _WIN32
	#include <windows.h>
	#include <wincon.h>

	#ifdef SLOW_MODE
		int slowModeSpeed{ 1000 };			// milliseconds between printing lines
		void mySleep(unsigned milliseconds)
		{
			Sleep(milliseconds);
		}
	#endif
	#ifdef COLOR_MODE
		enum COLOR
		{
			black = 0,
			dark_blue = 1,
			dark_green = 2,
			dark_aqua, dark_cyan = 3,
			dark_red = 4,
			dark_purple = 5, dark_pink = 5, dark_magenta = 5,
			dark_yellow = 6,
			dark_white = 7,
			gray = 8,
			blue = 9,
			green = 10,
			aqua = 11, cyan = 11,
			red = 12,
			purple = 13, pink = 13, magenta = 13,
			yellow = 14,
			white = 15
		};
		COLOR TRYING_COLOR{ COLOR::yellow };
		COLOR RECOGNIZED_COLOR{ COLOR::aqua };
		COLOR ACCEPTED_COLOR{ COLOR::green };
		COLOR REJECTED_COLOR{ COLOR::red };
	#endif
#else
#include <unistd.h>

void sleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000); // takes microseconds
}
#endif
#pragma endregion

#pragma region	DO NOT CHANGE THESE VALUES
/***********************************************************************************************************************/
// !!! Do not change the settings in this block !!!
#ifndef PRINT_RULE_ON_CALL				// Verbose only works when PRINT_RULE_ON_CALL is also defined
#ifdef VERBOSE_PRINT_RULE_ON_CALL
#undef VERBOSE_PRINT_RULE_ON_CALL
#endif
#endif // !PRINT_RULE_ON_CALL

/***********************************************************************************************************************/

/***********************************************************************************************************************/
// !!! Do not change the settings in this block !!!
#ifndef PRINT_RULE_ON_ACCEPT				// Verbose only works when PRINT_RULE_ON_ACCEPT is also defined
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
#undef PRINT_RULE_ON_ACCEPT
#endif
#endif // VERBOSE_PRINT_RULE_ON_ACCEPT
/***********************************************************************************************************************/
#pragma endregion


SyntaxAnalyzer::SyntaxAnalyzer(std::vector<std::pair<std::string, std::string>> tokenizedSource) : sourcePairs{ tokenizedSource }
{
	currentPair = sourcePairs.begin();
}

#pragma region Production Rules

//	<A>  ->  <B>	#	<J>	<N>	#
bool SyntaxAnalyzer::A()
{
#ifdef SLOW_MODE
	mySleep(slowModeSpeed);
#endif

	std::string rule{ "A" };
	bool isA{ false };
	

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule)); 
	#endif

	if (B())
	{
		if (currentPair->second == "#")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("#");
			#endif

			++currentPair;
			if (J())
			{

				if (N())
				{
					if (currentPair->second == "#")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
							PrintRecognizedString("#");
						#endif

						++currentPair;
						isA = true;

						#ifdef PRINT_RULE_ON_ACCEPT
							PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));				
						#endif
					}
				}
			}
		}
	}

	return isA;
}

//  <B> ->  C  |  CC      
bool SyntaxAnalyzer::B() 
{
	#ifdef SLOW_MODE
	mySleep(slowModeSpeed);
	#endif

	std::string rule{ "B" };
	bool isB{ false };

	#ifdef PRINT_RULE_ON_CALL 
	PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (C())
	{
		isB = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (CC())
	{
		isB = true;
		
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	return isB;
}

//	C  ->  D	C'
bool SyntaxAnalyzer::C()
{
	std::string rule{ "C" };
	bool isC{ false };
	
	#ifdef PRINT_RULE_ON_CALL 
	PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (D())
	{		
		if (C_())
		{
			isC = true;
			
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	return isC;
}

//	D  ->  function	DD	(	E	)	J	I
bool SyntaxAnalyzer::D()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "D" };
	bool isD{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "function") 
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("function");
		#endif

		++currentPair;

		if (DD())
		{			
			if (currentPair->second == "(")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					PrintRecognizedString("(");
				#endif

				++currentPair;
				if (E())
				{
					if (currentPair->second == ")")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
							PrintRecognizedString(")");
						#endif

						++currentPair;

						if (J())
						{
							if (I())
							{
								isD = true;
								#ifdef PRINT_RULE_ON_ACCEPT
									PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
								#endif
							}
						}
					}
				}
			}
		}
	}

	return isD;
}

//	E  ->  F	|	CC
bool SyntaxAnalyzer::E()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "E" };
	bool isE{ true };
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (F())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (CC())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else
	{
		isE = false;
	}
	return isE;
}

//	F  ->  G	F'
bool SyntaxAnalyzer::F()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "F" };
	bool isF{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (G())
	{
		if (F_())
		{
			isF = true;
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	return isF;
}

//	G  ->  M	H
bool SyntaxAnalyzer::G()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "G" };
	bool isG{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (M())
	{
		if (H())
		{
			isG = true;

			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	return isG;
}

// H  ->  integer	|	boolean	|	real
bool SyntaxAnalyzer::H()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "H" };
	bool isH{ false };
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->first == "integer")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("integer");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
		PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;

		isH = true;
	}
	else if (currentPair->first == "boolean")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("boolean");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
		++currentPair;
		isH = true;
	}
	else if (currentPair->first == "real")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("real");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif


		++currentPair;
		isH = true;
	}

	return isH;
}

//  I  ->  {	<N>	}
bool SyntaxAnalyzer::I()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "I" };
	bool isI{ false };
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "{")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("{");
		#endif

		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					PrintRecognizedString("}");
				#endif

				isI = true;
				++currentPair;
			}
		}
	}
	return isI;
}

//	J ->  <K> | CC
bool SyntaxAnalyzer::J()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "J" };
	bool isJ{ true };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (K())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (CC())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else
	{
		isJ = false;
	}
	return isJ;
}

// K  ->  L	;	K'
bool SyntaxAnalyzer::K()
{

	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "K" };
	bool isK{ false };
	
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (L())
	{
		if (currentPair->second == ";")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString(";");
			#endif
			
			++currentPair;
			if (K_())
			{
				isK = true;
				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}			
		}
	}
	return isK;
}

// L  ->  integer	M	|	boolean	M	|	real	M
bool SyntaxAnalyzer::L()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "L" };
	bool isL{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "integer")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("integer");
		#endif

		++currentPair;
		if (M())
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif

			isL = true;
		}
	}
	else if (currentPair->second == "boolean")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("boolean");
		#endif		

		++currentPair;
		if(M()) 
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif

			isL = true;
		}
	}
	else if (currentPair->second == "real")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("real");
		#endif

		++currentPair;
		if(M()) 
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif

			isL = true;
		}
	}
	return isL;
}

//	M  ->  DD	M'
bool SyntaxAnalyzer::M()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "M" };
	bool isM{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

		if (DD())
		{
			if (M_())
			{
				isM = true;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	return isM;
}

// <N>  ->  <O>	<N'>
bool SyntaxAnalyzer::N()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "N" };
	bool isN{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (O())
	{
		if (N_())
		{
			isN = true;
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	return isN;
}

// <O>->	<P>	|	<Q>	|	<R>	|	<S>	|	<T>	|	<U>	|	<V>
bool SyntaxAnalyzer::O()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "O" };
	bool isO{ true };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (P())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (Q()) 
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (R())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (S())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (T())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (U())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (V())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else isO = false;

	return isO;
}

// <P>  ->  {	<N>	}
bool SyntaxAnalyzer::P()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "P" };
	bool isP{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "{")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("{");
		#endif
		
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					PrintRecognizedString("}");
				#endif
				
				isP = true;
				++currentPair;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	return isP;
}

// Q  ->  DD	=	Y  ;
bool SyntaxAnalyzer::Q()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "Q" };
	
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	bool isQ{ false };

	if (DD())
	{
		if (currentPair->second == "=")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("=");
			#endif

			++currentPair;
			
			if (Y())
			{

				if (currentPair->second == ";")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						PrintRecognizedString(";");
					#endif

					#ifdef PRINT_RULE_ON_ACCEPT
						PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
					#endif
					
					isQ = true;
					++currentPair;
				}
			}
		}
	}
	return isQ;
}

// R  ->  if	(	W	)	O	R'
bool SyntaxAnalyzer::R()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "R" };
	bool isR{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "if")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("if");
		#endif
	
		++currentPair;
		
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("(");
			#endif

			++currentPair;

			if (W())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						PrintRecognizedString(")");
					#endif
					
					++currentPair;
			
					if (O())
					{
						if (R_())
						{							
							#ifdef PRINT_RULE_ON_ACCEPT
								PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
							#endif
							
							isR = true;
						}

					}
				}
			}
		}
	}
	return isR;
}

// S  ->  return	S'
bool SyntaxAnalyzer::S()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "S" };
	bool isS{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "return")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("return");
		#endif

		++currentPair;

		if (S_())
		{
			isS = true;

			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}return isS;
}

// T  ->  put	(	Y	)	;
bool SyntaxAnalyzer::T()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "T" };
	bool isT{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "put")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("put");
		#endif
		
		++currentPair;
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("(");
			#endif
			
			++currentPair;
			
			if (Y())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						PrintRecognizedString(")");
					#endif
					
					++currentPair;
					if (currentPair->second == ";")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
							PrintRecognizedString(";");
						#endif
						
						isT = true;
						++currentPair;

						#ifdef PRINT_RULE_ON_ACCEPT
							PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
						#endif

					}
				}
			}
		}
	}
	return isT;
}

// U  ->  get	(	M	)	;
bool SyntaxAnalyzer::U()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "U" };
	bool isU{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "get")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("get");
		#endif
		
		++currentPair;
		
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("(");
			#endif
			
			++currentPair;
			
			if (M())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						PrintRecognizedString(")");
					#endif
					
					++currentPair;
					
					if (currentPair->second == ";")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
							PrintRecognizedString(";");
						#endif
						
						isU = true;
						++currentPair;
						
						#ifdef PRINT_RULE_ON_ACCEPT
							PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
						#endif
					}
				}
			}
		}
	}
	return isU;
}

// V  ->  while	(	W	)	O
bool SyntaxAnalyzer::V()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "V" };
	bool isV{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "while")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("while");
		#endif
		
		++currentPair;
		
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("(");
			#endif
			
			++currentPair;
			
			if (W())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						PrintRecognizedString(")");
					#endif
					
					++currentPair;
					
					if (O())
					{
						isV = true;

						#ifdef PRINT_RULE_ON_ACCEPT
							PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
						#endif

					}
				}
			}
		}
	}
	return isV;
}

// W  ->  Y	X	Y
bool SyntaxAnalyzer::W()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "W" };
	bool isW{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (Y())
	{
		if (X())
		{
			if (Y())
			{
				isW = true;
				
				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	return isW;
}

// X  ->  ==	|	!=	|	>	|	<	|	<=	|	=>
bool SyntaxAnalyzer::X()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "X" };
	bool isX{ true };

		#ifdef PRINT_RULE_ON_CALL 
			PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
		#endif

	if (currentPair->second == "==")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("==");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else if (currentPair->second == "!=")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("!=");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else if (currentPair->second == ">")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString(">");
		#endif
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else if (currentPair->second == "<")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("<");
		#endif
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else if (currentPair->second == "<=")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("<=");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else if (currentPair->second == "=>")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("=>");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else
	{
		isX = false;
	}

	return isX;
}

// Y  ->  Z	Y'
bool SyntaxAnalyzer::Y()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "Y" };
	bool isY{ true };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (Z())
	{
		if (Y_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	return isY;
}

// <Z>  ->  <AA>	<Z'>
bool SyntaxAnalyzer::Z()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "Z" };
	bool isZ{ true };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (AA())
	{
		if (Z_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}

	return isZ;
}

// AA  ->  -	BB	|	BB
bool SyntaxAnalyzer::AA()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "AA" };
	bool isAA{ true };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "-")
	{

		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("-");
		#endif
		if (BB())
		{

			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	else if (BB())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else
	{
		isAA = false;
	}
	return isAA;
}

// <BB>  ->  <DD>	<BB'>	|	<EE>	|	(	<Y>	)	|	<FF>	|	TRUE	|	FALSE
bool SyntaxAnalyzer::BB() // TODO keep looking into BB function
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "BB" };
	bool isBB{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif
	
	if (currentPair->second == "TRUE")
	{
		isBB = true;

		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("TRUE");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	else if (currentPair->second == "FALSE")
		{

		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("FALSE");
		#endif

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
	}
	if (DD())
	{
		if (BB_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif

			isBB = true;
		}
	}
	else if (EE())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (currentPair->second == "(")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("(");
		#endif
		++currentPair;
		if (Y())
		{
			if (currentPair->second == ")")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					PrintRecognizedString(")");
				#endif

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif

					++currentPair;
					isBB = true;
			}
		}
	}
	else if (FF())
	{
		isBB = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}	
	return isBB;
}

// CC  ->  epsilon
bool SyntaxAnalyzer::CC()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "CC" };
	
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("epsilon");
	#endif

	return true;
}

// DD -> identifier
bool SyntaxAnalyzer::DD()
{
	bool isDD{ false };
	std::string rule{ "DD" };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->first == "identifier")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString(currentPair->second);
		#endif
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

		++currentPair;
		isDD = true;;
	}

	return isDD;	
}

// EE -> integer
bool SyntaxAnalyzer::EE()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	bool isEE{ false };
	std::string rule{ "EE" };
	
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->first == "integer")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString(currentPair->second);
		#endif

		++currentPair;
		isEE =  true;
	}	
	return isEE;
}

// FF -> real
bool SyntaxAnalyzer::FF()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	bool isFF{ false };
	std::string rule{ "FF" };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->first == "real")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("real");
		#endif

		++currentPair;
		isFF = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	return isFF;
}

// Y'  ->  +	Z	Y'	|	-	Z	Y'	|	epsilon
bool SyntaxAnalyzer::Y_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "Y'" };
	bool isY_{ false };
	
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "+")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("+");
		#endif

		++currentPair;

		if (Z())
		{
			if (Y_())
			{
				isY_ = true;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	else if (currentPair->second == "-")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("-");
		#endif

		++currentPair;

		if (Z())
		{
			if (Y_())
			{
				isY_ = true;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	else // epsilon
	{
		isY_ = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	return isY_;
}

// Z'  ->  *	AA	Z'	|	/	AA	Z'	|	epsilon
bool SyntaxAnalyzer::Z_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "Z'" };
	bool isZ_{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "*")
	{

		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("*");
		#endif

		++currentPair;

		if (AA())
		{
			if (Z_())
			{
				isZ_ = true;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	else if (currentPair->second == "/")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString("/");
		#endif

		++currentPair;

		if (AA())
		{
			if (Z_())
			{
				isZ_ = true;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	else // epsilon
	{
		isZ_ = true; // Because epsilon

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	return isZ_;
}

// C'  ->  C | epsilon
bool SyntaxAnalyzer::C_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	bool isC_{ false };
	std::string rule{ "C'" };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (C())
	{
		isC_ = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif

	}
	return isC_;
}

// F'  ->  ,	F  |  epsilon
bool SyntaxAnalyzer::F_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	bool isF_{ true };				// always true because of epsilon
	std::string rule{ "F'" };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

		if (currentPair->second == ",")
		{
			++currentPair;

			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString(",");
			#endif

			if (F())
			{
				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	return isF_;
}

// K'  ->  K  |  epsilon
bool SyntaxAnalyzer::K_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	bool isK_{ false };
	std::string rule{ "K'" };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (K())
	{
		isK_ = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else isK_ = true;

	return isK_;
}

// M'  ->  ,  M  |  epsilon
bool SyntaxAnalyzer::M_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

		bool isM_{ true };
	std::string rule{ "M'"};

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == ",")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString(",");
		#endif

		++currentPair;

		if (M())
		{
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	else {
			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
	}
	return isM_;
}

// <N'>  ->  <N>  |  epsilon
bool SyntaxAnalyzer::N_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

		bool isN_{ true };
	std::string rule{ "N'" };

		#ifdef PRINT_RULE_ON_CALL 
			PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
		#endif

	if(N())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else
	{
		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	return isN_; // because of the epsilon
}

// R'  ->  endif	|	else	O	endif
bool SyntaxAnalyzer::R_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "R'" };
	bool isR_{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "endif")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("endif");
		#endif
		
		++currentPair;
		isR_ = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (currentPair->second == "else")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("else");
		#endif

		++currentPair;

		if (O())
		{
			if (currentPair->second == "endif")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					PrintRecognizedString("endif");
				#endif
				
				isR_ = true;
				++currentPair;

				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif
			}
		}
	}
	return isR_;
}

// S'  ->  ;	|	Y	;
bool SyntaxAnalyzer::S_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "S'" };
	bool isS_{ false };

	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == ";")
	{

		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString(";");
		#endif

		++currentPair;
		isS_ = true;

		#ifdef PRINT_RULE_ON_ACCEPT
			PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
		#endif
	}
	else if (Y())
	{
		if (currentPair->second == ";")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				PrintRecognizedString(";");
			#endif

			++currentPair;
			isS_ = true;

			#ifdef PRINT_RULE_ON_ACCEPT
				PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
			#endif
		}
	}
	return isS_;
}

// BB'  ->  epsilon	|	(	M	)
bool SyntaxAnalyzer::BB_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "BB'" };
	bool isBB_{ false };
	
	#ifdef PRINT_RULE_ON_CALL 
		PrintOnCall(rule, AbstractEquivalenceMap.at(rule));
	#endif

	if (currentPair->second == "(")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			PrintRecognizedString("(");
		#endif

		++currentPair;

		if (M())
		{
			if (currentPair->second == ")")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					PrintRecognizedString(")");
				#endif
								
				#ifdef PRINT_RULE_ON_ACCEPT
					PrintAcceptedRule(rule, AbstractEquivalenceMap.at(rule));
				#endif

				++currentPair;
				isBB_ = true;
			}
		}
	}
	else // epsilon
	{
		isBB_ = true;
	}
	return isBB_;
}

#pragma endregion 


#pragma region Print Functions

void SyntaxAnalyzer::PrintOnCall(std::string ruleName, std::string rule)
{
	#ifdef COLOR_MODE
		HANDLE                      m_hConsole;
		WORD                        m_currentConsoleAttr;
		CONSOLE_SCREEN_BUFFER_INFO   csbi;

		//retrieve and save the current attributes
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(m_hConsole, &csbi))
			m_currentConsoleAttr = csbi.wAttributes;

		//change the attribute to what you like
		SetConsoleTextAttribute(
			m_hConsole,
			TRYING_COLOR);
	#endif // COLOR_MODE


	std::cout << "\nTrying Rule :: <" << ruleName << ">"

	#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  " << rule;
	#else
			;
	#endif // VERBOSE_PRINT_RULE_ON_CALL




	#ifdef COLOR_MODE
		//set the ttribute to the original one
		SetConsoleTextAttribute(
			m_hConsole,
			m_currentConsoleAttr);
	#endif
}

void SyntaxAnalyzer::PrintRecognizedString(std::string symbol) const
{
	#ifdef COLOR_MODE
		HANDLE                      m_hConsole;
		WORD                        m_currentConsoleAttr;
		CONSOLE_SCREEN_BUFFER_INFO   csbi;

		//retrieve and save the current attributes
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(m_hConsole, &csbi))
			m_currentConsoleAttr = csbi.wAttributes;

		//change the attribute to what you like
		SetConsoleTextAttribute(
			m_hConsole,
			RECOGNIZED_COLOR);
	#endif // COLOR_MODE



	std::cout << "\n\nRECOGNIZED............................................................................. " << symbol << "\n";


	#ifdef COLOR_MODE
		//set the ttribute to the original one
		SetConsoleTextAttribute(
			m_hConsole,
			m_currentConsoleAttr);
	#endif
}

void SyntaxAnalyzer::PrintAcceptedRule(std::string ruleName, std::string rule) const
{
	#ifdef COLOR_MODE
		HANDLE                      m_hConsole;
		WORD                        m_currentConsoleAttr;
		CONSOLE_SCREEN_BUFFER_INFO   csbi;

		//retrieve and save the current attributes
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(m_hConsole, &csbi))
			m_currentConsoleAttr = csbi.wAttributes;

		//change the attribute to what you like
		SetConsoleTextAttribute(
			m_hConsole,
			ACCEPTED_COLOR);
	#endif // COLOR_MODE


	std::cout << "\nACCEPTED:  <" << ruleName << ">"

	#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  " << rule;
	#else
			;
	#endif

	#ifdef COLOR_MODE
		//set the ttribute to the original one
		SetConsoleTextAttribute(
			m_hConsole,
			m_currentConsoleAttr);
	#endif
}
#pragma endregion