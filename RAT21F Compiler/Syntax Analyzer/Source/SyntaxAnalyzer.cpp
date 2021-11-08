#include "../Include/SyntaxAnalyzer.h"
#include <string>
#include <iostream>




//#define PRINT_RULE_ON_CALL
//#define PRINT_RULE_ON_ACCEPT








#pragma region Production Rules
//	A	::=	B	#	J	N	#
bool SyntaxAnalyzer::A()
{
	std::string rule{ "A" };
	bool isA{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (B())
	{
		if (currentPair->second == "#")
		{
			++currentPair;
			if (J())
			{
				if (N())
				{
					if ('#')
					{
						++currentPair;
						isA = true;

						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nProduction Rule: " << rule << "\tA  ->  B  #  J  N  #";
						#endif
					}
				}
			}
		}
	}

	return isA;
}

//   B ::=	C	|	CC      
bool SyntaxAnalyzer::B() 
{
	std::string rule{ "B" };
	bool isB{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (C())
	{
		isB = true;
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tB  -> ~C~  |  CC";
#endif
	}
	else if (CC())
	{
		isB = true;
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tB  ->  C  |  ~CC~";
#endif
	}
	else{}

	return isB;
}

//	C	->	D	C'
bool SyntaxAnalyzer::C()
{
	std::string rule{ "C" };
	bool isC{ false };
	
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
	#endif

	if (D())
	{
		if (C_())
		{
			isC = true;
			
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tC  ->  D  C'";
			#endif
		}
	}

	return isC;
}

//	D	->	function	DD	(	E	)	J	I
bool SyntaxAnalyzer::D()
{
	std::string rule{ "D" };
	bool isD{ false };

	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule;
	#endif

	if (currentPair->second == "function") // todo this needs to be changed
	{
		++currentPair;
		if (DD())
		{			
			if (currentPair->second == "(")
			{
				++currentPair;
				if (E())
				{
					if (currentPair->second == ")")
					{
						++currentPair;

						if (J())
						{
							if (I())
							{
								isD = true;
								#ifdef PRINT_RULE_ON_ACCEPT 
								std::cout << "\nProduction Rule: " << rule << "\tD  ->  function  DD  (  E  )  J  I";
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

//	E	->	F	|	CC
bool SyntaxAnalyzer::E()
{
	std::string rule{ "E" };
	bool isE{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule;
#endif

	if (F())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tE  ->  ~F~  |  CC";
#endif
	}
	else if (CC())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tE  ->  F  |  ~CC~";
#endif
	}
	else
	{
		isE = false;
	}

	return isE;
}

//	F	->	G	F'
bool SyntaxAnalyzer::F()
{
	std::string rule{ "F" };
	bool isF{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (G())
	{
		if (F_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tF  ->  G  F'";
#endif
		}
		else isF = false;
	}
	else isF = false;


	return isF;
}

//	G	->	M	H
bool SyntaxAnalyzer::G()
{
	std::string rule{ "G" };
	bool isG{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (M())
	{
		if (H())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tG  ->  M  H";
#endif
		}
		else isG = false;
	}
	else isG = false;


	return isG;
}

// H	->	integer	|	boolean	|	real
bool SyntaxAnalyzer::H()
{
	std::string rule{ "H" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->first == "integer")
	{
		++currentPair;
		return true;
	}
	else if (currentPair->first == "boolean")
	{
		++currentPair;
		return true;
	}
	else if (currentPair->first == "real")
	{
		++currentPair;
		return true;
	}

	return false;
}

//  I	->	{	N	}
bool SyntaxAnalyzer::I()
{

	std::string rule{ "I" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "{")
	{
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				++currentPair;
				return true;
			}
			else return false;
		}
		else return false;
	}
	else	return false;
}

//	J -> K | CC
bool SyntaxAnalyzer::J()
{
	std::string rule{ "J" };
	bool isJ{ true }; 
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule;
#endif

	if (K())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tJ -> ~K~ | CC";
#endif
	}
	else if (CC())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tJ -> K | ~CC~";
#endif
	}
	else
	{
		isJ = false;
	}

	return isJ;
}

// K	->	L	;	K'
bool SyntaxAnalyzer::K()
{
	std::string rule{ "K" };
	bool isK{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (L())
	{
		if (currentPair->second == ";")
		{
			++currentPair;
			if (K_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule << "\tK  ->  L  ;  K'";
#endif
			}
			
		}
		else isK = false;
	}
	else isK = false;

	return isK;
}

// L	->	integer	M	|	boolean	M	|	real	M
bool SyntaxAnalyzer::L()
{
	std::string rule{ "L" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "integer")
	{
		++currentPair;
		if(M()) return true;
	}
	else if (currentPair->second == "boolean")
	{
		++currentPair;
		if(M()) return true;
	}
	else if (currentPair->second == "real")
	{
		++currentPair;
		if(M()) return true;
	}

	return false;
}

//	M	->	DD	M'
bool SyntaxAnalyzer::M()
{
	std::string rule{ "M" };
	bool isM{ true };

	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (DD())
	{
		if (M_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tM  ->  DD M'";
#endif
		}
		else isM = false;
	}
	else isM = false;


	return isM;
}

// N	->	O	N'
bool SyntaxAnalyzer::N()
{
	std::string rule{ "N" };
	bool isN{ true };

#ifdef PRINT_RULE_ON_CALL
	std::cout <<"\n" << rule << std::endl;
#endif
	if (O())
	{
		if (N_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tN  ->  O  N'";
#endif
		}
		else isN = false;
	}
	else isN = false;


	return isN;
}

// O	->	P	|	Q	|	R	|	S	|	T	|	U	|	V
bool SyntaxAnalyzer::O()
{
	std::string rule{ "O" };
	bool isO{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (P())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  ~P~  |  Q  |  R  |  S  |  T  |  U  |  V";
#endif
	}
	else if (Q()) 
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  ~Q~  |  R  |  S  |  T  |  U  |  V";
#endif
	}
	else if (R())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  ~R~  |  S  |  T  |  U  |  V";
#endif
	}
	else if (S())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  ~S~  |  T  |  U  |  V";
#endif
	}
	else if (T())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  S  |  ~T~  |  U  |  V";
#endif
	}
	else if (U())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  S  |  T  |  ~U~  |  V";
#endif
	}
	else if (V())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  S  |  T  |  U  |  ~V~";
#endif
	}
	else isO = false;


	return isO;
}

// P	->	{	N	}
bool SyntaxAnalyzer::P()
{
	std::string rule{ "P" };
	bool isP{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "{")
	{
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				++currentPair;
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule << "\tP  ->  {  N  }";
#endif
			}
			else isP = false;
		}
		else isP = false;
	}
	else	isP = false;

	return isP;
}

// Q	->	DD	=	Y
bool SyntaxAnalyzer::Q()
{
	std::string rule{ "Q" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	bool isQ{ true };
	if (DD())
	{
		if (currentPair->second == "=")
		{
			++currentPair;
			if (Y())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule << "\tQ  ->  DD  =  Y";
#endif
			}
			else isQ = false;
		}
		else isQ = false;
	}
	else isQ = false;

	return isQ;
}

// R	->	if	(	W	)	O	R'
bool SyntaxAnalyzer::R()
{
	std::string rule{ "R" };
	bool isR{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "if")
	{
		++currentPair;
		if (currentPair->second == "(")
		{
			++currentPair;
			if (W())
			{
				if (currentPair->second == ")")
				{
					++currentPair;
					if (O())
					{
						if (R_())
						{
							#ifdef PRINT_RULE_ON_ACCEPT 
							std::cout << "\nProduction Rule: " << rule << "\tif  (  W  )  O  R'";
#endif
						}
						else isR = false;
					}
					else isR = false;
				}
				else isR = false;
			}
			else isR = false;
		}
		else isR = false;
	}
	else isR = false;

	return isR;
}

// S	->	return	S'
bool SyntaxAnalyzer::S()
{
	std::string rule{ "S" };
	bool isS{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "return")
	{
		++currentPair;
		if (S_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tS  ->  return  S'";
#endif
		}
		else isS = false;
	}
	else isS = false;

	return isS;
}

// T	->	put	(	Y	)	;
bool SyntaxAnalyzer::T()
{
	std::string rule{ "T" };
	bool isT{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "put")
	{
		++currentPair;
		if (currentPair->second == "(")
		{
			++currentPair;
			if (Y())
			{
				if (currentPair->second == ")")
				{
					++currentPair;
					if (currentPair->second == ";")
					{
						++currentPair;
						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nProduction Rule: " << rule << "\tput  (  Y  )  ;";
#endif

					}
					else isT = false;
				}
				else isT = false;
			}
			else isT = false;
		}
		else isT = false;
	}
	else isT = false;

	return isT;
}

// U	->	get	(	M	)	;
bool SyntaxAnalyzer::U()
{
	std::string rule{ "U" };
	bool isU{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "get")
	{
		++currentPair;
		if (currentPair->second == "(")
		{
			++currentPair;
			if (M())
			{
				if (currentPair->second == ")")
				{
					++currentPair;
					if (currentPair->second == ";")
					{
						++currentPair;
						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nProduction Rule: " << rule << "\tU  ->  get  (  M  )  ;";
#endif

					}
					else isU = false;
				}
				else isU = false;
			}
			else isU = false;
		}
		else isU = false;
	}
	else isU = false;

	return isU;

}

// V	->	while	(	W	)	O
bool SyntaxAnalyzer::V()
{
	std::string rule{ "V" };
	bool isV{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "while")
	{
		++currentPair;
		if (currentPair->second == "(")
		{
			++currentPair;
			if (W())
			{
				if (currentPair->second == ")")
				{
					++currentPair;
					if (O())
					{
						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nProduction Rule: " << rule << "\tV  ->  while  (  W  )  O";
#endif

					}
					else isV = false;
				}
				else isV = false;
			}
			else isV = false;
		}
		else isV = false;
	}
	else isV = false;

	return isV;
}

// W	->	Y	X	Y
bool SyntaxAnalyzer::W()
{
	std::string rule{ "W" };
	bool isW{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif


	if (Y())
	{
		if (X())
		{
			if (Y())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule << "\tW  ->  Y  X  Y";
#endif
			}
			else isW = false;
		}
		else isW = false;
	}
	else isW = false;

	return isW;
}

// X	->	==	|	!=	|	>	|	<	|	<=	|	=>
bool SyntaxAnalyzer::X()
{
	std::string rule{ "X" };
	bool isX{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "==")
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ~==~  |  !=  |  >  |  <  |  <=  |  =>";
#endif
	}
	else if (currentPair->second == "!=")
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  ~!=~  |  >  |  <  |  <=  |  =>";
#endif
	}
	else if (currentPair->second == ">")
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  ~>~  |  <  |  <=  |  =>";
#endif
	}
	else if (currentPair->second == "<")
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  >  |  ~<~  |  <=  |  =>";
#endif
	}
	else if (currentPair->second == "<=")
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  >  |  <  |  ~<=~  |  =>";
#endif
	}
	else if (currentPair->second == "=>")
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  >  |  <  |  <=  |  ~=>~";
#endif
	}
	else
	{
		isX = false;
	}

	return isX;
}

// Y	->	Z	Y'
bool SyntaxAnalyzer::Y()
{
	std::string rule{ "Y" };
	bool isY{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (Z())
	{
		if (Y_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tY  ->  Z  Y'";
#endif
		}
	}

	return isY;
}

// Z	->	AA	Z'
bool SyntaxAnalyzer::Z()
{
	std::string rule{ "Z" };
	bool isZ{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (AA())
	{
		if (Z_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tZ  ->  AA  Z'";
#endif
		}
	}

	return isZ;
}

// AA	->	-	BB	|	BB
bool SyntaxAnalyzer::AA()
{
	std::string rule{ "AA" };
	bool isAA{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == "-")
	{
		if (BB())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tAA  ->  ~-BB~  |  BB";
#endif
		}
	}
	else if (BB())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tAA  ->  -BB  |  ~BB~";
#endif
	}
	else
	{
		isAA = false;
	}

	return isAA;
}

// BB	->	DD	BB'	|	EE	|	(	Y	)	|	FF	|	TRUE	|	FALSE
bool SyntaxAnalyzer::BB()
{
	std::string rule{ "BB" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif
	return false;
}

// CC	->	epsilon
bool SyntaxAnalyzer::CC()
{
	std::string rule{ "CC" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif
	return true;
}

// DD -> identifier
bool SyntaxAnalyzer::DD()
{
	std::string rule{ "DD" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif
	if (currentPair->first == "identifier")
	{
		++currentPair;
		return true;
	}

	return false;
	
}

// EE -> integer
bool SyntaxAnalyzer::EE()
{

	std::string rule{ "EE" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->first == "integer")
	{
		++currentPair;
		return true;
	}
	return false;
}

// FF -> real
bool SyntaxAnalyzer::FF()
{
	std::string rule{ "FF" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->first == "real")
	{
		++currentPair;
		return true;
	}
	return false;
}

// Y'	->	+	Z	Y'	|	-	Z	Y'	|	epsilon
bool SyntaxAnalyzer::Y_()
{
	std::string rule{ "Y_" };
	bool isY_{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule;
#endif

	if (currentPair->second == "+")
	{
		++currentPair;
		if (Z())
		{
			if (Y_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule << "\tY'  ->  ~+  Z  Y'~  |  -  Z  Y'  |  epsilon";
#endif
			}
			else isY_ = false;
		}
		else isY_ = false;
	}
	else if (currentPair->second == "-")
	{
		++currentPair;
		if (Z())
		{
			if (Y_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule << "\tY'  ->  +  Z  Y'  |  ~-  Z  Y'~  |  epsilon";
#endif
			}
			else isY_ = false;
		}
		else isY_ = false;
	}
	else // epsilon
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tY'  ->  +  Z  Y'  |  -  Z  Y'  |  ~epsilon~";
#endif
	}

	return isY_;
}

// Z'	->	*	AA	Z'	|	/	AA	Z'	|	epsilon
bool SyntaxAnalyzer::Z_()
{
	std::string rule{ "Z_" };
	bool isZ_{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule;
#endif

	if (currentPair->second == "*")
	{
		++currentPair;
		if (AA())
		{
			if (Z_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule;
#endif
			}
			else isZ_ = false;
		}
		else isZ_ = false;
	}
	else if (currentPair->second == "/")
	{
		++currentPair;
		if (AA())
		{
			if (Z_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nProduction Rule: " << rule;
#endif
			}
			else isZ_ = false;
		}
		else isZ_ = false;
	}
	else // epsilon
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule;
#endif
	}

	return isZ_;
}

// C'	->	epsilon	|	C
bool SyntaxAnalyzer::C_()
{
	std::string rule{ "C_" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif
	return true;
}

// F'	->	epsilon	|	,	F
bool SyntaxAnalyzer::F_()
{
	std::string rule{ "F_" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule;
#endif
	return true;
}

// K'	->	epsilon	|	K
bool SyntaxAnalyzer::K_()
{
	std::string rule{ "K_" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule; 
#endif


	if (K())
	{
		#ifdef PRINT_RULE_ON_CALL 
		std::cout << "\nProduction Rule: " << rule;
#endif
	}
	return true;
}

// M'	->	epsilon	|	,	M
bool SyntaxAnalyzer::M_()
{
	std::string rule{ "M_"};
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif

	if (currentPair->second == ",")
	{
		++currentPair;
		if (M())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nProduction Rule: " << rule << "\tM'  ->  ~,M~  |  epsilon";
#endif
		}
	}
	else {
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tM'  ->  ,M  |  ~epsilon~";
#endif
	}
	return true;
}

// N'	->	epsilon	|	N
bool SyntaxAnalyzer::N_()
{
	std::string rule{ "N_" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule; 
#endif

	if (N())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tN'  ->  ~N~  |  epsilon";
#endif
	}
	else
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nProduction Rule: " << rule << "\tN'  ->  N  |  ~epsilon~";
#endif
	}
	return true; // because of the epsilon
}

// R'	->	endif	|	else	O	endif
bool SyntaxAnalyzer::R_()
{
	std::string rule{ "N_" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule;
#endif
	return false;
}

// S'	->	;	|	Y	;
bool SyntaxAnalyzer::S_()
{
	std::string rule{ "S_" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule; 
#endif
	return false;
}

// BB'	->	epsilon	|	(	M	)
bool SyntaxAnalyzer::BB_()
{
	std::string rule{ "BB_" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule; 
#endif
	return true;
}

#pragma endregion 