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
						std::cout << "Production Rule: " << rule;
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
		std::cout << "Production Rule: " << rule;
	}
	else if (CC())
	{
		std::cout << "Production Rule: " << rule;
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
			std::cout << "Production Rule: " << rule;
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
								std::cout << "Production Rule: " << rule;
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
		std::cout << "Production Rule: " << rule;
	}
	else if (CC())
	{
		std::cout << "Production Rule: " << rule;
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
			std::cout << "Production Rule: " << rule;
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
			std::cout << "Production Rule: " << rule;
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

	if (currentPair->second == "integer")
	{
		++currentPair;
		return true;
	}
	else if (currentPair->second == "boolean")
	{
		++currentPair;
		return true;
	}
	else if (currentPair->second == "real")
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
		std::cout << "Production Rule: " << rule;
	}
	else if (CC())
	{
		std::cout << "Production Rule: " << rule;
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
				std::cout << "Production Rule: " << rule;
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
			std::cout << "Production Rule: " << rule;
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
			std::cout << "Production Rule: " << rule;
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
		std::cout << "Production Rule: " << rule;
	}
	else if (Q()) 
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (R())
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (S())
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (T())
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (U())
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (V())
	{
		std::cout << "Production Rule: " << rule;
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
				std::cout << "Production Rule: " << rule;
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
				std::cout << "Production Rule: " << rule;
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
							std::cout << "Production Rule: " << rule;
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
			std::cout << "Production Rule: " << rule;
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

	return isT;
}

// U	->	get	(	M	)	;
bool SyntaxAnalyzer::U()
{
	std::string rule{ "U" };
	bool isU{ true };

	return isU;
}

// V	->	while	(	W	)	O
bool SyntaxAnalyzer::V()
{
	std::string rule{ "V" };
	bool isV{ true };

	return isV;
}

// W	->	Y	X	Y
bool SyntaxAnalyzer::W()
{
	std::string rule{ "W" };
	bool isW{ true };

	return isW;
}

// X	->	==	|	!=	|	>	|	<	|	<=	|	=>
bool SyntaxAnalyzer::X()
{
	std::string rule{ "X" };
	bool isX{ true };

	return isX;
}

// Y	->	Z	Y'
bool SyntaxAnalyzer::Y()
{
	std::string rule{ "Y" };
	bool isY{ true };

	return isY;
}

// Z	->	AA	Z'
bool SyntaxAnalyzer::Z()
{
	std::string rule{ "Z" };
	bool isZ{ true };

	return isZ;
}

// AA	->	-	BB	|	BB
bool SyntaxAnalyzer::AA()
{
	return false;
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
	return false;
}

// Z'	->	*	AA	Z'	|	/	AA	Z'	|	epsilon
bool SyntaxAnalyzer::Z_()
{
	return false;
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
	return true;
}

// M'	->	epsilon	|	,	M
bool SyntaxAnalyzer::M_()
{
	return true;
}

// N'	->	epsilon	|	N
bool SyntaxAnalyzer::N_()
{
	return false;
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