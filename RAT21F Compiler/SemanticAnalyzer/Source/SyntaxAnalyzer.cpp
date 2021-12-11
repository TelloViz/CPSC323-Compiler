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
	for (auto iter : tokenizedSource)
	{
		if (iter.first == "identifier")
		{
			if (!symbolExists(iter.second))
			{
				insert_symbol(SymbAddr(), iter.second);
				IncrSymbAddr();
			}
		}
	}

	currentPair = sourcePairs.begin();
}

#pragma region Production Rules

//	<A>  -> #	<J>	<N>	#
bool SyntaxAnalyzer::A()
{
#ifdef SLOW_MODE
	mySleep(slowModeSpeed);
#endif

	std::string rule{ "A" };
	bool isA{ false };	

	HandlePrintOnCall(rule);
	
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
				else { Expected("#"); }
			}
		}
	}
	else { Expected("#"); }


	if (isA)
	{
		//HandlePrintSuccessText();
		
	}
	else
	{
		HandlePrintRejected(rule);
	}

	return isA;
}

//  <B> ->  C  |  CC      



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

// L  ->  integer	M	|	boolean	M
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

// <Compound>
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

		std::string tempValChecker = currentPair->second;
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

//		Q  ->  DD	 = Y  ;
// A1)	A  ->  id  = E           { gen_instr (POPM,  get_address(id)) }
bool SyntaxAnalyzer::Q()
{
	#ifdef SLOW_MODE
		mySleep(slowModeSpeed);
	#endif

	std::string rule{ "Q" };
	
	HandlePrintOnCall(rule);

	bool isQ{ false };

	if (DD())  // if Token == identifier type
	{
		std::string saveSymbol = (currentPair-1)->second; // cache the identifier for use lower down
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
			GenerateInstruction("POPM", std::to_string(get_address(saveSymbol))); // TODO remove this awful pointer arithmetic
		}
		else { Expected("="); }
	}
	/*else
	{
		Expected("identifier");
	}*/

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

			W();
			
			if (currentPair->second == ")")
			{
				HandlePrintRecognized(*currentPair);					
				++currentPair;
			
				O();
				BackPatch(InstrAddr());
				if (R_())
				{	
					GenerateInstruction("LABEL", "nil");
					HandlePrintAccepted(rule);
								
					isR = true;
				}
				//else Expected("Expected endif");
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

	}/*
	else { Expected("return"); }*/
	
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

//		  V  ->  while	 (  W  )	O
//  W1)     W  ->  while  (  C  )  S 
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
		int addr = InstrAddr(); // this is the address of while instruction
		GenerateInstruction("LABEL", "nil");
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
					GenerateInstruction("JUMP", std::to_string(addr));
					// TODO put BackPatch here not sure if right becaues my program operates just slightly differently so check back here
					BackPatch(InstrAddr());
					
				}
				else error_message(std::cout, "Expected )");
			}
		}else error_message(std::cout, "Expected (");
	}
	else error_message(std::cout, "Expected while");

	if (isV == false)
	{
		HandlePrintRejected(rule);
	}


	return isV;
}

//		W  ->  Y	X  Y
// W2)    C  - > E  R  E 
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
		std::string relopString{ currentPair->second }; // This will grab the Relop before its changed in subsequent function calls.
		if (X())
		{
			// if you've made it here, then you do have a relational operator in relopString
			if (Y())
			{
				auto rhs = *(currentPair-1);
				isW = true;
				HandlePrintAccepted(rule);					
			}

			auto iter = std::find(operatorsVec.begin(), operatorsVec.end(), relopString);
			if (iter != operatorsVec.end())
			{
				int idx = iter - operatorsVec.begin();

				//  ==  |	 != 	 |   >	|	<	|	<=	|  =>
				switch (idx)
				{
				case 0: // ==
					break;
				case 1: // !=
					break;
				case 2: // >
					GenerateInstruction("GRT", "nil");
					jmpStack.push(InstrAddr());
					GenerateInstruction("", "");

					break;
				case 3: // <
					GenerateInstruction("LES", "nil");
					jmpStack.push(InstrAddr());   /* another stack need */
					GenerateInstruction("JUMPZ", "nil");
					break;
				case 4: // <=
					break;
				case 5: // =>
					break;
				}
			}
		}
	}

	if (isW == false)
	{
		HandlePrintRejected(rule);
	}


	return isW;
}

//		X  ->  ==	|	!=	|	>	|	<	|	<=	|  =>
// W3)    R  ->  == |    !=   |    >    |    <    |    =>   |  <=
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

//		Y  ->  Z	Y'
// A2)	E  ->  T  E’ 
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
// A5) T  ->   F  T’
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
		++currentPair; // I just added this after turning in the previous assignment, this was an oversight.
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

	std::string saveID = currentPair->second;
	if (DD())
	{
		GenerateInstruction("PUSHM", std::to_string(get_address(saveID))); // need to replace "token" with actual token


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
			else { Expected(")"); }
		}
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

//	  DD -> identifier
// A8) F  -> id { gen_instr (PUSHM, get_address(id) )
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
	/*else
	{
		Expected("identifier");
	}*/


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
		GenerateInstruction("PUSHI", currentPair->second); // need to replace "token" with actual token
		++currentPair;
		isEE =  true;
	}
	else { Expected("integer"); }

	if (isEE == false)
	{
		HandlePrintRejected(rule);
	}



	return isEE;
}


// Y'  ->  +	Z	Y'	|	-	Z	Y'	|	epsilon
// A3) E’ -> + T {  gen_intsr(ADD,  nil) }   E’ 
// A4) E’ ->  epsilon
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
			GenerateInstruction("ADD", "nil");
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
// A6) T’ -> * F { gen_instr (MUL, nil) }  T’ 
// A7) T’ -> epsilon  
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
			GenerateInstruction("MUL", "nil");

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
			else { Expected("endif"); }
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
		tempStringStream << "  ->  " << rule << std::endl;
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