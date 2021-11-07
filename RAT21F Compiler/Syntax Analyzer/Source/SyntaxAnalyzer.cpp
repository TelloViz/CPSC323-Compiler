#include "../Include/SyntaxAnalyzer.h"
#include <string>
#include <iostream>

#pragma region Production Rules
//	A	::=	B	#	J	N	#
bool SyntaxAnalyzer::A()
{
	std::string rule{ "A" };
	bool isA{ true };

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
						std::cout << "\nProduction Rule: " << rule << "\tA  ->  B  #  J  N  #";
					}
					else isA = false;
				}
				else isA = false;
			}
			else isA = false;
		}
		else isA = false;
	}
	else isA = false;

	return isA;
}

//   B ::=	C	|	CC      
bool SyntaxAnalyzer::B() 
{
	std::string rule{ "B" };
	bool isB{ true };

	if (C())
	{
		std::cout << "\nProduction Rule: " << rule << "\tB  -> ~C~  |  CC";
	}
	else if (CC())
	{
		std::cout << "\nProduction Rule: " << rule << "\tB  ->  C  |  ~CC~";
	}
	else
	{
		isB = false;
	}

	return isB;
}

//	C	->	D	C'
bool SyntaxAnalyzer::C()
{
	std::string rule{ "C" };
	bool isC{ true };

	if (D())
	{
		if (C_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tC  ->  D  C'";
		}
		else isC = false;
	}
	else isC = false;


	return isC;
}

//	D	->	function	DD	(	E	)	J	I
bool SyntaxAnalyzer::D()
{
	std::string rule{ "D" };
	bool isD{ true };
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
								std::cout << "\nProduction Rule: " << rule << "\tD  ->  function  DD  (  E  )  J  I";
							}
							else isD = false;
						}
						else isD = false;
					}
					else isD = false;
				}
				else isD = false;
			}
			else isD = false;
		}
		else isD = false;
	}
	else isD = false;

	return isD;
}

//	E	->	F	|	CC
bool SyntaxAnalyzer::E()
{
	std::string rule{ "E" };
	bool isE{ true };

	if (F())
	{
		std::cout << "\nProduction Rule: " << rule << "\tE  ->  ~F~  |  CC";
	}
	else if (CC())
	{
		std::cout << "\nProduction Rule: " << rule << "\tE  ->  F  |  ~CC~";
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

	if (G())
	{
		if (F_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tF  ->  G  F'";
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

	if (M())
	{
		if (H())
		{
			std::cout << "\nProduction Rule: " << rule << "\tG  ->  M  H";
		}
		else isG = false;
	}
	else isG = false;


	return isG;
}

// H	->	integer	|	boolean	|	real
bool SyntaxAnalyzer::H()
{
	bool isInt{ true };
	bool isBool{ true };
	bool isReal{ true };

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

	if (K())
	{
		std::cout << "\nProduction Rule: " << rule << "\tJ -> ~K~ | CC";
	}
	else if (CC())
	{
		std::cout << "\nProduction Rule: " << rule << "\tJ -> K | ~CC~";
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

	if (L())
	{
		if (currentPair->second == ";")
		{
			++currentPair;
			if (K_())
			{
				std::cout << "\nProduction Rule: " << rule << "\tK  ->  L  ;  K'";
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
	bool isInt{ true };
	bool isBool{ true };
	bool isReal{ true };

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

	if (DD())
	{
		if (M_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tM  ->  DD M'";
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

	if (O())
	{
		if (N_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tN  ->  O  N'";
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

	if (P())
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  ~P~  |  Q  |  R  |  S  |  T  |  U  |  V";
	}
	else if (Q()) 
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  ~Q~  |  R  |  S  |  T  |  U  |  V";
	}
	else if (R())
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  ~R~  |  S  |  T  |  U  |  V";
	}
	else if (S())
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  ~S~  |  T  |  U  |  V";
	}
	else if (T())
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  S  |  ~T~  |  U  |  V";
	}
	else if (U())
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  S  |  T  |  ~U~  |  V";
	}
	else if (V())
	{
		std::cout << "\nProduction Rule: " << rule << "\tO  ->  P  |  Q  |  R  |  S  |  T  |  U  |  ~V~";
	}
	else isO = false;


	return isO;
}

// P	->	{	N	}
bool SyntaxAnalyzer::P()
{
	std::string rule{ "P" };
	bool isP{ true };
	if (currentPair->second == "{")
	{
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				++currentPair;
				std::cout << "\nProduction Rule: " << rule << "\tP  ->  {  N  }";
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

	bool isQ{ true };
	if (DD())
	{
		if (currentPair->second == "=")
		{
			++currentPair;
			if (Y())
			{
				std::cout << "\nProduction Rule: " << rule << "\tQ  ->  DD  =  Y";
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
							std::cout << "\nProduction Rule: " << rule << "\tif  (  W  )  O  R'";
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

	if (currentPair->second == "return")
	{
		++currentPair;
		if (S_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tS  ->  return  S'";
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
						std::cout << "\nProduction Rule: " << rule << "\tput  (  Y  )  ;";

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
						std::cout << "\nProduction Rule: " << rule << "\tU  ->  get  (  M  )  ;";

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
						std::cout << "\nProduction Rule: " << rule << "\tV  ->  while  (  W  )  O";

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

	if (Y())
	{
		if (X())
		{
			if (Y())
			{
				std::cout << "\nProduction Rule: " << rule << "\tW  ->  Y  X  Y";
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

	if (currentPair->second == "==")
	{
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ~==~  |  !=  |  >  |  <  |  <=  |  =>";
	}
	else if (currentPair->second == "!=")
	{
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  ~!=~  |  >  |  <  |  <=  |  =>";
	}
	else if (currentPair->second == ">")
	{
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  ~>~  |  <  |  <=  |  =>";
	}
	else if (currentPair->second == "<")
	{
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  >  |  ~<~  |  <=  |  =>";
	}
	else if (currentPair->second == "<=")
	{
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  >  |  <  |  ~<=~  |  =>";
	}
	else if (currentPair->second == "=>")
	{
		std::cout << "\nProduction Rule: " << rule << "\tX  ->  ==  |  !=  |  >  |  <  |  <=  |  ~=>~";
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

	if (Z())
	{
		if (Y_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tY  ->  Z  Y'";
		}
	}

	return isY;
}

// Z	->	AA	Z'
bool SyntaxAnalyzer::Z()
{
	std::string rule{ "Z" };
	bool isZ{ true };

	if (AA())
	{
		if (Z_())
		{
			std::cout << "\nProduction Rule: " << rule << "\tZ  ->  AA  Z'";
		}
	}

	return isZ;
}

// AA	->	-	BB	|	BB
bool SyntaxAnalyzer::AA()
{
	std::string rule{ "AA" };
	bool isAA{ true };

	if (currentPair->second == "-")
	{
		if (BB())
		{
			std::cout << "\nProduction Rule: " << rule << "\tAA  ->  ~-BB~  |  BB";
		}
	}
	else if (BB())
	{
		std::cout << "\nProduction Rule: " << rule << "\tAA  ->  -BB  |  ~BB~";
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
	return false;
}

// CC	->	epsilon
bool SyntaxAnalyzer::CC()
{
	return true;
}

// DD -> identifier
bool SyntaxAnalyzer::DD()
{
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

	if (currentPair->second == "+")
	{
		++currentPair;
		if (Z())
		{
			if (Y_())
			{
				std::cout << "\nProduction Rule: " << rule << "\tY'  ->  ~+  Z  Y'~  |  -  Z  Y'  |  epsilon";
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
				std::cout << "\nProduction Rule: " << rule << "\tY'  ->  +  Z  Y'  |  ~-  Z  Y'~  |  epsilon";
			}
			else isY_ = false;
		}
		else isY_ = false;
	}
	else // epsilon
	{
		std::cout << "\nProduction Rule: " << rule << "\tY'  ->  +  Z  Y'  |  -  Z  Y'  |  ~epsilon~";
	}

	return isY_;
}

// Z'	->	*	AA	Z'	|	/	AA	Z'	|	epsilon
bool SyntaxAnalyzer::Z_()
{
	std::string rule{ "Z_" };
	bool isZ_{ true };

	if (currentPair->second == "*")
	{
		++currentPair;
		if (AA())
		{
			if (Z_())
			{
				std::cout << "\nProduction Rule: " << rule;
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
				std::cout << "\nProduction Rule: " << rule;
			}
			else isZ_ = false;
		}
		else isZ_ = false;
	}
	else // epsilon
	{
		std::cout << "\nProduction Rule: " << rule;
	}

	return isZ_;
}

// C'	->	epsilon	|	C
bool SyntaxAnalyzer::C_()
{
	return true;
}

// F'	->	epsilon	|	,	F
bool SyntaxAnalyzer::F_()
{
	return true;
}

// K'	->	epsilon	|	K
bool SyntaxAnalyzer::K_()
{
	std::string rule{ "K_" };
	if (K())
	{
		std::cout << "\nProduction Rule: " << rule;
	}
	return true;
}

// M'	->	epsilon	|	,	M
bool SyntaxAnalyzer::M_()
{
	std::string rule{ "M_"};

	if (currentPair->second == ",")
	{
		++currentPair;
		if (M())
		{
			std::cout << "\nProduction Rule: " << rule << "\tM'  ->  ~,M~  |  epsilon";
		}
	}
	else std::cout << "\nProduction Rule: " << rule << "\tM'  ->  ,M  |  ~epsilon~";
	return true;
}

// N'	->	epsilon	|	N
bool SyntaxAnalyzer::N_()
{
	std::string rule{ "N_" };
	if (N())
	{
		std::cout << "\nProduction Rule: " << rule << "\tN'  ->  ~N~  |  epsilon";
	}
	else std::cout << "\nProduction Rule: " << rule << "\tN'  ->  N  |  ~epsilon~";
	return true; // because of the epsilon
}

// R'	->	endif	|	else	O	endif
bool SyntaxAnalyzer::R_()
{
	return false;
}

// S'	->	;	|	Y	;
bool SyntaxAnalyzer::S_()
{
	return false;
}

// BB'	->	epsilon	|	(	M	)
bool SyntaxAnalyzer::BB_()
{
	return true;
}

#pragma endregion 