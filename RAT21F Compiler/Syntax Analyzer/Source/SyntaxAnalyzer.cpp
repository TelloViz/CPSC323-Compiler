// SyntaxAnalyzer.cpp

/* This file holds the implementation details for the Syntax Analyzer class.
// It is also home to the #defines that toggle various modes of output,
// including color and slow-mode

// The Syntax analyzer is built from a Backus-Naur grammar listing of Rat21F.
// I've removed left recursion and factored where needed.

Author: Josh Lollis
Project 2 Syntax Analysis
CPSC-323 Fall 2021

Last Edit: 11/11/21

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

#ifndef ABBREVIATED_MODE
#define ABBREVIATED_MODE		// Comment out ths line to turn off
#endif // !ABBREVIATED_MODE


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

	HandlePrintOnCall(rule);

	if (B())
	{
		if (currentPair->second == "#")
		{
			HandlePrintRecognized("#");
			++currentPair;
			if (J())
			{

				if (N())
				{
					if (currentPair->second == "#")
					{
						HandlePrintRecognized("#");

						++currentPair;
						isA = true;

						HandlePrintAccepted(rule);
					}
				}
			}
		}
	}

	if (isA == false)
	{
		#ifdef PRINT_RULE_ON_REJECT
			#ifdef ABBREVIATED_MODE
				//PrintRejectedRule(rule);
			#else
				PrintRejectedRule(RuleNameConversion(rule), EquivalenceMap.at(RuleNameConversion(rule)));
			#endif // ABBREVIATED_MODE											
		#endif
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

	HandlePrintOnCall(rule);

	if (C())
	{
		isB = true;

		HandlePrintAccepted(rule);
	}
	else if (CC())
	{
		isB = true;
		
		HandlePrintAccepted(rule);
	}
	return isB;
}

//	C  ->  D	C'
bool SyntaxAnalyzer::C()
{
	std::string rule{ "C" };
	bool isC{ false };
	
	HandlePrintOnCall(rule);

	if (D())
	{		
		if (C_())
		{
			isC = true;
			
			HandlePrintAccepted(rule);
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "function") 
	{
		HandlePrintRecognized("function");
		++currentPair;

		if (DD())
		{			
			if (currentPair->second == "(")
			{
				HandlePrintRecognized("(");

				++currentPair;
				if (E())
				{
					if (currentPair->second == ")")
					{
						HandlePrintRecognized(")");

						++currentPair;

						if (J())
						{
							if (I())
							{
								isD = true;
								HandlePrintAccepted(rule);									
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

	HandlePrintOnCall(rule);

	if (F())
	{
		HandlePrintAccepted(rule);
	}
	else if (CC())
	{
		HandlePrintAccepted(rule);
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

	HandlePrintOnCall(rule);

	if (G())
	{
		if (F_())
		{
			isF = true;
			HandlePrintAccepted(rule);
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

	HandlePrintOnCall(rule);

	if (M())
	{
		if (H())
		{
			isG = true;

				HandlePrintAccepted(rule);
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
	
	HandlePrintOnCall(rule);

	if (currentPair->first == "integer")
	{
		HandlePrintRecognized("integer");

		HandlePrintAccepted(rule);

		++currentPair;

		isH = true;
	}
	else if (currentPair->first == "boolean")
	{
		HandlePrintRecognized("boolean");

		HandlePrintAccepted(rule);
		++currentPair;
		isH = true;
	}
	else if (currentPair->first == "real")
	{
		HandlePrintRecognized("real");

		HandlePrintAccepted(rule);

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

	HandlePrintOnCall(rule);

	if (currentPair->second == "{")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("{");
		#endif

		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					HandlePrintRecognized("}");
				#endif
						
				HandlePrintAccepted(rule);
					
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

	HandlePrintOnCall(rule);

	if (K())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (CC())
	{
		HandlePrintAccepted(rule);
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
	
	HandlePrintOnCall(rule);

	if (L())
	{
		if (currentPair->second == ";")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized(";");
			#endif
			
			++currentPair;
			if (K_())
			{
				isK = true;
				HandlePrintAccepted(rule);					
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "integer")
	{
		HandlePrintRecognized("integer");

		++currentPair;
		if (M())
		{
			HandlePrintAccepted(rule);

			isL = true;
		}
	}
	else if (currentPair->second == "boolean")
	{
		HandlePrintRecognized("boolean");		

		++currentPair;
		if(M()) 
		{
			HandlePrintAccepted(rule);
				
			isL = true;
		}
	}
	else if (currentPair->second == "real")
	{
		HandlePrintRecognized("real");

		++currentPair;
		if(M()) 
		{
			HandlePrintAccepted(rule);
				
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

	HandlePrintOnCall(rule);

		if (DD())
		{
			if (M_())
			{
				isM = true;

				HandlePrintAccepted(rule);					
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

	HandlePrintOnCall(rule);

	if (O())
	{
		if (N_())
		{
			isN = true;
			HandlePrintAccepted(rule);
				
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
	HandlePrintOnCall(rule);

	if (P())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (Q()) 
	{
		HandlePrintAccepted(rule);
			
	}
	else if (R())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (S())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (T())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (U())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (V())
	{
		HandlePrintAccepted(rule);
			
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "{")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("{");
		#endif
		
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					HandlePrintRecognized("}");
				#endif
				
				isP = true;
				++currentPair;

				HandlePrintAccepted(rule);
					
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
	
	HandlePrintOnCall(rule);

	bool isQ{ false };

	if (DD())
	{
		if (currentPair->second == "=")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("=");
			#endif

			++currentPair;
			
			if (Y())
			{

				if (currentPair->second == ";")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						HandlePrintRecognized(";");
					#endif

					HandlePrintAccepted(rule);
						
					
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "if")
	{
		HandlePrintRecognized("if");
	
		++currentPair;
		
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("(");
			#endif

			++currentPair;

			if (W())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						HandlePrintRecognized(")");
					#endif
					
					++currentPair;
			
					if (O())
					{
						if (R_())
						{							
							HandlePrintAccepted(rule);
								
							
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "return")
	{
		HandlePrintRecognized("return");

		++currentPair;

		if (S_())
		{
			isS = true;

			HandlePrintAccepted(rule);
				
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "put")
	{
		HandlePrintRecognized("put");
		
		++currentPair;
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("(");
			#endif
			
			++currentPair;
			
			if (Y())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						HandlePrintRecognized(")");
					#endif
					
					++currentPair;
					if (currentPair->second == ";")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
							HandlePrintRecognized(";");
						#endif
						
						isT = true;
						++currentPair;

						HandlePrintAccepted(rule);
							
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "get")
	{
		HandlePrintRecognized("get");
		
		++currentPair;
		
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("(");
			#endif
			
			++currentPair;
			
			if (M())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						HandlePrintRecognized(")");
					#endif
					
					++currentPair;
					
					if (currentPair->second == ";")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
							HandlePrintRecognized(";");
						#endif
						
						isU = true;
						++currentPair;
						
						HandlePrintAccepted(rule);
							
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "while")
	{
		HandlePrintRecognized("while");
		
		++currentPair;
		
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("(");
			#endif
			
			++currentPair;
			
			if (W())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
						HandlePrintRecognized(")");
					#endif
					
					++currentPair;
					
					if (O())
					{
						isV = true;

						HandlePrintAccepted(rule);
							
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

	HandlePrintOnCall(rule);

	if (Y())
	{
		if (X())
		{
			if (Y())
			{
				isW = true;
				
				HandlePrintAccepted(rule);
					
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "==")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("==");
		#endif

		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	else if (currentPair->second == "!=")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("!=");
		#endif

		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	else if (currentPair->second == ">")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized(">");
		#endif
		
		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	else if (currentPair->second == "<")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("<");
		#endif
		HandlePrintAccepted(rule);
			
		++currentPair;
	}
	else if (currentPair->second == "<=")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("<=");
		#endif

		HandlePrintAccepted(rule);
			
		++currentPair;
	}
	else if (currentPair->second == "=>")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("=>");
		#endif

		HandlePrintAccepted(rule);
			
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

	HandlePrintOnCall(rule);

	if (Z())
	{
		if (Y_())
		{
			HandlePrintAccepted(rule);
				
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

	HandlePrintOnCall(rule);

	if (AA())
	{
		if (Z_())
		{
			HandlePrintAccepted(rule);
				
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "-")
	{

		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("-");
		#endif
		if (BB())
		{

			HandlePrintAccepted(rule);
				
		}
	}
	else if (BB())
	{
		HandlePrintAccepted(rule);
			
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

	HandlePrintOnCall(rule);
	
	if (currentPair->second == "TRUE")
	{
		isBB = true;

		HandlePrintRecognized("TRUE");

		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	else if (currentPair->second == "FALSE")
		{

		HandlePrintRecognized("FALSE");

		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	if (DD())
	{
		if (BB_())
		{
			HandlePrintAccepted(rule);
				

			isBB = true;
		}
	}
	else if (EE())
	{
		HandlePrintAccepted(rule);
			
	}
	else if (currentPair->second == "(")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("(");
		#endif
		++currentPair;
		if (Y())
		{
			if (currentPair->second == ")")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					HandlePrintRecognized(")");
				#endif

				HandlePrintAccepted(rule);
					
					++currentPair;
					isBB = true;
			}
		}
	}
	else if (FF())
	{
		isBB = true;

		HandlePrintAccepted(rule);
			
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
	
	HandlePrintOnCall(rule);

	HandlePrintRecognized("epsilon");

	HandlePrintAccepted(rule);
		

	return true;
}

// DD -> identifier
bool SyntaxAnalyzer::DD()
{
	bool isDD{ false };
	std::string rule{ "DD" };

	HandlePrintOnCall(rule);

	if (currentPair->first == "identifier")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized(currentPair->second);
		#endif
		HandlePrintAccepted(rule);
			

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
	
	HandlePrintOnCall(rule);

	if (currentPair->first == "integer")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized(currentPair->second);
		#endif

		HandlePrintAccepted(rule);

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

	HandlePrintOnCall(rule);

	if (currentPair->first == "real")
	{
		HandlePrintRecognized("real");

		++currentPair;
		isFF = true;

		HandlePrintAccepted(rule);
			
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
	
	HandlePrintOnCall(rule);

	if (currentPair->second == "+")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("+");
		#endif

		++currentPair;

		if (Z())
		{
			if (Y_())
			{
				isY_ = true;

				HandlePrintAccepted(rule);
					
			}
		}
	}
	else if (currentPair->second == "-")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("-");
		#endif

		++currentPair;

		if (Z())
		{
			if (Y_())
			{
				isY_ = true;

				HandlePrintAccepted(rule);
					
			}
		}
	}
	else // epsilon
	{
		HandlePrintRecognized("epsilon");

		isY_ = true;

		HandlePrintAccepted(rule);
			
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "*")
	{

		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("*");
		#endif

		++currentPair;

		if (AA())
		{
			if (Z_())
			{
				isZ_ = true;

				HandlePrintAccepted(rule);
					
			}
		}
	}
	else if (currentPair->second == "/")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized("/");
		#endif

		++currentPair;

		if (AA())
		{
			if (Z_())
			{
				isZ_ = true;

				HandlePrintAccepted(rule);
					
			}
		}
	}
	else // epsilon
	{

		HandlePrintRecognized("epsilon");

		isZ_ = true; // Because epsilon

		HandlePrintAccepted(rule);
			
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

	HandlePrintOnCall(rule);

	if (C())
	{
		isC_ = true;

	}
	else
	{
		HandlePrintRecognized("epsilon");
		
		isC_ = true;
	}

	HandlePrintAccepted(rule);
		
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

	HandlePrintOnCall(rule);

		if (currentPair->second == ",")
		{
			++currentPair;

			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized(",");
			#endif

			if (F())
			{
				isF_ = true;
			}
		}
		else
		{
			HandlePrintRecognized("epsilon");
			isF_ = true;
		}

		HandlePrintAccepted(rule);
			
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

	HandlePrintOnCall(rule);

	if (K())
	{
		isK_ = true;
	}
	else
	{
		HandlePrintRecognized("epsilon");
		isK_ = true;
	}

	HandlePrintAccepted(rule);
		

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

	HandlePrintOnCall(rule);

	if (currentPair->second == ",")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized(",");
		#endif

		++currentPair;

		if (M())
		{
			isM_ = true;
		}
	}
	else 
	{
		HandlePrintRecognized("epsilon");
		isM_ = true;
	}

	HandlePrintAccepted(rule);
		
	return isM_;
}

// <N'>  ->  <N>  |  epsilon
bool SyntaxAnalyzer::N_()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

		bool isN_{ false };
	std::string rule{ "N'" };

	HandlePrintOnCall(rule);

	if(N())
	{
		isN_ = true;
	}
	else
	{
		HandlePrintRecognized("epsilon");
		isN_ = true;
	}

	HandlePrintAccepted(rule);
		
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

	HandlePrintOnCall(rule);

	if (currentPair->second == "endif")
	{
		HandlePrintRecognized("endif");
		
		++currentPair;
		isR_ = true;
		HandlePrintAccepted(rule);
			
	}
	else if (currentPair->second == "else")
	{
		HandlePrintRecognized("else");

		++currentPair;

		if (O())
		{
			if (currentPair->second == "endif")
			{
				HandlePrintRecognized("endif");
				
				isR_ = true;
				++currentPair;
				HandlePrintAccepted(rule);
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

	HandlePrintOnCall(rule);

	if (currentPair->second == ";")
	{

		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized(";");
		#endif

		++currentPair;
		isS_ = true;

		HandlePrintAccepted(rule);
			
	}
	else if (Y())
	{
		if (currentPair->second == ";")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
				HandlePrintRecognized(";");
			#endif

			++currentPair;
			isS_ = true;

			HandlePrintAccepted(rule);
			
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
	
	HandlePrintOnCall(rule);

	if (currentPair->second == "(")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
			HandlePrintRecognized("(");
		#endif

		++currentPair;

		if (M())
		{
			if (currentPair->second == ")")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
					HandlePrintRecognized(")");
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

	HandlePrintAccepted(rule);
		
	return isBB_;
}

#pragma endregion 


#pragma region Print Functions

void SyntaxAnalyzer::PrintOnCall(std::string ruleName, std::string rule) const
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

void SyntaxAnalyzer::PrintRejectedRule(std::string ruleName, std::string rule) const
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
		REJECTED_COLOR);
#endif // COLOR_MODE


	std::cout << "\nREJECTED:  <" << ruleName << ">"

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
void SyntaxAnalyzer::HandlePrintOnCall(std::string ruleName)
{
	#ifdef PRINT_RULE_ON_CALL 
		#ifdef ABBREVIATED_MODE
			PrintOnCall(ruleName, AbstractEquivalenceMap.at(ruleName));
		#else
			PrintOnCall(RuleNameConversion(ruleName), EquivalenceMap.at(RuleNameConversion(ruleName)));
		#endif // ABBREVIATED_MODE
	#endif
}
void SyntaxAnalyzer::HandlePrintRecognized(std::string symbol)
{
	#ifdef PRINT_RECOGNIZE_LABEL 
		PrintRecognizedString(symbol);
	#endif
}
void SyntaxAnalyzer::HandlePrintAccepted(std::string ruleName)
{
	#ifdef PRINT_RULE_ON_ACCEPT
		#ifdef ABBREVIATED_MODE
			PrintAcceptedRule(ruleName, AbstractEquivalenceMap.at(ruleName));
		#else
			PrintAcceptedRule(RuleNameConversion(ruleName), EquivalenceMap.at(RuleNameConversion(ruleName)));
		#endif // ABBREVIATED_MODE			
	#endif
}
void SyntaxAnalyzer::HandlePrintRejected(std::string ruleName)
{
	#ifdef PRINT_RULE_ON_REJECT
		#ifdef ABBREVIATED_MODE
			PrintRejectedRule(ruleName, AbstractEquivalenceMap.at(ruleName));
		#else
			PrintRejectedRule(RuleNameConversion(ruleName), EquivalenceMap.at(RuleNameConversion(ruleName)));
		#endif // ABBREVIATED_MODE											
	#endif
}
#pragma endregion