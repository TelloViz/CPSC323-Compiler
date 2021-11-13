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
#include "../Include/SA_Config.h"
#include <sstream>

using namespace SA_cfg;


SyntaxAnalyzer::SyntaxAnalyzer(std::vector<std::pair<std::string, std::string>> tokenizedSource, std::string& outputString) 
	: sourcePairs{ tokenizedSource }, outputStringRef{outputString}

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

			HandlePrintRecognized(*currentPair);

			++currentPair;
			if (J())
			{

				if (N())
				{
					if (currentPair->second == "#")
					{

						HandlePrintRecognized(*currentPair);

						++currentPair;
						isA = true;

						HandlePrintAccepted(rule);
					}
				}
			}
		}
	}


	if (isA)
	{
		HandlePrintSuccessText();
	}
	else
	{
		HandlePrintRejected(rule);
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

	if (isB == false)
	{
		HandlePrintRejected(rule);
		return isB;
	}
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

	if (isC == false)
	{
		HandlePrintRejected(rule);
		return isC;
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
		HandlePrintRecognized(*currentPair);

		++currentPair;

		if (DD())
		{			
			if (currentPair->second == "(")
			{
				
        HandlePrintRecognized(*currentPair);


				++currentPair;
				if (E())
				{
					if (currentPair->second == ")")
					{
						HandlePrintRecognized(*currentPair);

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

	if (isD == false)
	{
		HandlePrintRejected(rule);
		return isD;
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

	if (isE == false)
	{
		HandlePrintRejected(rule);
		return isE;
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

	if (isF == false)
	{
		HandlePrintRejected(rule);
		return isF;
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

	if (isG == false)
	{
		HandlePrintRejected(rule);
		return isG;
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
		HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);

		++currentPair;

		isH = true;
	}
	else if (currentPair->first == "boolean")
	{
		HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);
		++currentPair;
		isH = true;
	}
	else if (currentPair->first == "real")
	{
		HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);

		++currentPair;
		isH = true;
	}

	if (isH == false)
	{
		HandlePrintRejected(rule);
		return isH;
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
		HandlePrintRecognized(*currentPair);
		++currentPair;


		if (N())
		{
			if (currentPair->second == "}")
			{
				 
				HandlePrintRecognized(*currentPair);						

				HandlePrintAccepted(rule);
					
				isI = true;
				++currentPair;
			}
		}
	}

	if (isI == false)
	{
		HandlePrintRejected(rule);
		return isI;
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

	if (isJ == false)
	{
		HandlePrintRejected(rule);
		return isJ;
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
			HandlePrintRecognized(*currentPair);

			
			++currentPair;
			if (K_())
			{
				isK = true;
				HandlePrintAccepted(rule);					
			}			
		}
	}

	if (isK == false)
	{
		HandlePrintRejected(rule);
		return isK;
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
		HandlePrintRecognized(*currentPair);


		++currentPair;
		if (M())
		{
			HandlePrintAccepted(rule);

			isL = true;
		}
	}
	else if (currentPair->second == "boolean")
	{
		HandlePrintRecognized(*currentPair);		


		++currentPair;
		if(M()) 
		{
			HandlePrintAccepted(rule);
				
			isL = true;
		}
	}
	else if (currentPair->second == "real")
	{
		HandlePrintRecognized(*currentPair);


		++currentPair;
		if(M()) 
		{
			HandlePrintAccepted(rule);
				
			isL = true;
		}
	}

	if (isL == false)
	{
		HandlePrintRejected(rule);
		return isL;
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

		if (isM == false)
		{
			HandlePrintRejected(rule);
			return isM;
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

	if (isN == false)
	{
		HandlePrintRejected(rule);
		return isN;
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
	else
	{
		HandlePrintRejected(rule);
		isO = false;
	}


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
		HandlePrintRecognized(*currentPair);

		
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				 
				HandlePrintRecognized(*currentPair);

				
				isP = true;
				++currentPair;

				HandlePrintAccepted(rule);
					
			}
		}
	}

	if (isP == false)
	{
		HandlePrintRejected(rule);
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
			HandlePrintRecognized(*currentPair);
			
			++currentPair;
			
			if (Y())
			{

				if (currentPair->second == ";")
				{
					HandlePrintRecognized(*currentPair);

					HandlePrintAccepted(rule);
						
					
					isQ = true;
					++currentPair;
				}
			}
		}
	}

	if (isQ == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);

	
		++currentPair;
		
		if (currentPair->second == "(")
		{
			HandlePrintRecognized(*currentPair);


			++currentPair;

			if (W())
			{
				if (currentPair->second == ")")
				{
					HandlePrintRecognized(*currentPair);

					
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

	if (isR == false)
	{
		HandlePrintRejected(rule);
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

		HandlePrintRecognized(*currentPair);


		++currentPair;

		if (S_())
		{
			isS = true;

			HandlePrintAccepted(rule);
				
		}

  }
	
	if (isS == false)
	{
		HandlePrintRejected(rule);
	}

	return isS;

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

    HandlePrintRecognized(*currentPair);

		
		++currentPair;
		if (currentPair->second == "(")
		{

      HandlePrintRecognized(*currentPair);

			
			++currentPair;
			
			if (Y())
			{
				if (currentPair->second == ")")
				{
					 HandlePrintRecognized(*currentPair);

					++currentPair;
					if (currentPair->second == ";")
					{
						HandlePrintRecognized(*currentPair);

						
						isT = true;
						++currentPair;

						HandlePrintAccepted(rule);
							
					}
				}
			}
		}
	}


	if (isT == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);

		
		++currentPair;
		
		if (currentPair->second == "(")
		{
			 HandlePrintRecognized(*currentPair);

			
			++currentPair;
			
			if (M())
			{
				if (currentPair->second == ")")
				{
					 HandlePrintRecognized(*currentPair);

					
					++currentPair;
					
					if (currentPair->second == ";")
					{
						HandlePrintRecognized(*currentPair);

						
						isU = true;
						++currentPair;
						
						HandlePrintAccepted(rule);
							
					}
				}
			}
		}
	}

	if (isU == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);

		
		++currentPair;
		
		if (currentPair->second == "(")
		{
			HandlePrintRecognized(*currentPair);

			
			++currentPair;
			
			if (W())
			{
				if (currentPair->second == ")")
				{
					HandlePrintRecognized(*currentPair);

					
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

	if (isV == false)
	{
		HandlePrintRejected(rule);
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

	if (isW == false)
	{
		HandlePrintRejected(rule);
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

		HandlePrintRecognized(*currentPair);

		HandlePrintAccepted(rule);			


		++currentPair;
	}
	else if (currentPair->second == "!=")
	{

		HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	else if (currentPair->second == ">")
	{

		 
		HandlePrintRecognized(*currentPair);

		
		HandlePrintAccepted(rule);
			

		++currentPair;
	}
	else if (currentPair->second == "<")
	{
		 
		HandlePrintRecognized(*currentPair);

		HandlePrintAccepted(rule);
			
		++currentPair;
	}
	else if (currentPair->second == "<=")
	{
		 
		HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);
			
		++currentPair;
	}
	else if (currentPair->second == "=>")
	{
		 
		HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);
			
		++currentPair;
	}
	else
	{
		isX = false;
		HandlePrintRejected(rule);

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

	if (isY == false)
	{
		HandlePrintRejected(rule);
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

	if (isZ == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);

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
		HandlePrintRejected(rule);

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

		HandlePrintRecognized(*currentPair);

		HandlePrintAccepted(rule);			


		++currentPair;
	}
	else if (currentPair->second == "FALSE")
		{

		HandlePrintRecognized(*currentPair);

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
		HandlePrintRecognized(*currentPair);

		++currentPair;


		if (Y())
		{
			if (currentPair->second == ")")
			{
				HandlePrintRecognized(*currentPair);


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

	if (isBB == false)
	{
		HandlePrintRejected(rule);
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

	std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
	HandlePrintRecognized(tempPair);


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
		HandlePrintRecognized(*currentPair);

		HandlePrintAccepted(rule);
			

		++currentPair;
		isDD = true;;
	}

	if (isDD == false)
	{
		HandlePrintRejected(rule);
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
		 HandlePrintRecognized(*currentPair);


		HandlePrintAccepted(rule);

		++currentPair;
		isEE =  true;
	}	

	if (isEE == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);


		++currentPair;
		isFF = true;

		HandlePrintAccepted(rule);
			
	}

	if (isFF == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);


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
		HandlePrintRecognized(*currentPair);


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
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);


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
		HandlePrintRecognized(*currentPair);


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
		HandlePrintRecognized(*currentPair);


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
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);

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
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);

		
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
			HandlePrintRecognized(*currentPair);
			++currentPair;
			

			if (F())
			{
				isF_ = true;
			}
		}
		else
		{
			std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
			HandlePrintRecognized(tempPair);

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
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);

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
		HandlePrintRecognized(*currentPair);


		++currentPair;

		if (M())
		{
			isM_ = true;
		}
	}
	else 
	{
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);

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
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);

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
		HandlePrintRecognized(*currentPair);

		
		++currentPair;
		isR_ = true;
		HandlePrintAccepted(rule);
			
	}
	else if (currentPair->second == "else")
	{
		HandlePrintRecognized(*currentPair);


		++currentPair;

		if (O())
		{
			if (currentPair->second == "endif")
			{
				HandlePrintRecognized(*currentPair);

				
				isR_ = true;
				++currentPair;
				HandlePrintAccepted(rule);
			}
		}
	}

	if (isR_ == false)
	{
		HandlePrintRejected(rule);
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
		HandlePrintRecognized(*currentPair);


		++currentPair;
		isS_ = true;

		HandlePrintAccepted(rule);
			
	}
	else if (Y())
	{
		if (currentPair->second == ";")
		{
			HandlePrintRecognized(*currentPair);


			++currentPair;
			isS_ = true;

			HandlePrintAccepted(rule);
			
		}
	}

	if (isS_ == false)
	{
		HandlePrintRejected(rule);
	}
	return isS_;
}

// BB'  ->  (	M	)  |  epsilon

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
		 HandlePrintRecognized(*currentPair);


		++currentPair;

		if (M())
		{
			if (currentPair->second == ")")
			{
				 HandlePrintRecognized(*currentPair);

				++currentPair;
				isBB_ = true;
			}
		}
	}
	else // epsilon
	{
		std::pair<std::string, std::string> tempPair{ "epsilon", "epsilon" };
		HandlePrintRecognized(tempPair);

		isBB_ = true;
	}

	HandlePrintAccepted(rule);
		
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


	std::stringstream tempStringStream;
	tempStringStream << "\nTrying Rule :: <" << ruleName << ">";
	std::cout << tempStringStream.str();
	outputStringRef.append(tempStringStream.str());
	tempStringStream.str(std::string{ "" });

	#ifdef VERBOSE_PRINT_RULE_ON_CALL
		tempStringStream << "  ->  " << rule;
		std::cout << tempStringStream.str();
		outputStringRef.append(tempStringStream.str());
		tempStringStream.str(std::string{ "" });


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

void SyntaxAnalyzer::PrintRecognizedString(std::pair<std::string , std::string> tokLex) 

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

		std::stringstream tempStringStream;
		tempStringStream << "\n\nRECOGNIZED................................................................ TOKEN: " << tokLex.first << "\tLEXEME: " << tokLex.second << "\n";
		std::cout << tempStringStream.str();
		outputStringRef.append(tempStringStream.str());
		tempStringStream.str(std::string{""});


	#ifdef COLOR_MODE
		//set the ttribute to the original one
		SetConsoleTextAttribute(
			m_hConsole,
			m_currentConsoleAttr);
	#endif
}

void SyntaxAnalyzer::PrintAcceptedRule(std::string ruleName, std::string rule)
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

	std::stringstream tempStringStream;
	tempStringStream << "\nACCEPTED:  <" << ruleName << ">";
	std::cout << tempStringStream.str();
	outputStringRef.append(tempStringStream.str());
	tempStringStream.str(std::string{ "" });

	#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
		tempStringStream << "  ->  " << rule;
		std::cout << tempStringStream.str();
		outputStringRef.append(tempStringStream.str());
		tempStringStream.str(std::string{ "" });

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

void SyntaxAnalyzer::PrintRejectedRule(std::string ruleName, std::string rule) 

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


	std::stringstream tempStringStream;
	tempStringStream << "\nREJECTED:  <" << ruleName << ">";
	std::cout << tempStringStream.str();
	outputStringRef.append(tempStringStream.str());
	tempStringStream.str(std::string{ "" });

#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
		tempStringStream << "  ->  " << rule;
		std::cout << tempStringStream.str();
		outputStringRef.append(tempStringStream.str());
		tempStringStream.str(std::string{ "" });

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

void SyntaxAnalyzer::PrintSuccessText() 
{
	std::stringstream tempStringStream;
	tempStringStream << "\n\nSyntax Correct!\n\n";
	std::cout << tempStringStream.str();
	outputStringRef.append(tempStringStream.str());
	tempStringStream.str(std::string{ "" });
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
void SyntaxAnalyzer::HandlePrintRecognized(std::pair<std::string, std::string> tokLex)
{
	#ifdef PRINT_RECOGNIZE_LABEL
		PrintRecognizedString(tokLex);

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
void SyntaxAnalyzer::HandlePrintSuccessText()
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
		SUCCESS_COLOR);
#endif // COLOR_MODE

	PrintSuccessText();

#ifdef COLOR_MODE
	//set the ttribute to the original one
	SetConsoleTextAttribute(
		m_hConsole,
		m_currentConsoleAttr);
#endif

}

#pragma endregion