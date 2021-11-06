#include "../Include/SyntaxAnalyzer.h"
#include <string>
#include <iostream>

#pragma region Production Rules
//	A	::=	B	#	J	N	#
bool SyntaxAnalyzer::A(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "A" };
	bool isA{ true };

	if (B(tokenLexPair))
	{
		if (tokenLexPair.second == "#")
		{
			if (J(tokenLexPair))
			{
				if (N(tokenLexPair))
				{
					if ('#')
					{
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
bool SyntaxAnalyzer::B(std::pair<std::string, std::string> tokenLexPair) 
{
	std::string rule{ "B" };
	bool isB{ true };

	if (C(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (CC(tokenLexPair))
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
bool SyntaxAnalyzer::C(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "C" };
	bool isC{ true };

	if (D(tokenLexPair))
	{
		if (C_(tokenLexPair))
		{
			std::cout << "Production Rule: " << rule;
		}
		else isC = false;
	}
	else isC = false;


	return isC;
}

//	D	->	function	DD	(	E	)	J	I
bool SyntaxAnalyzer::D(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "D" };
	bool isD{ true };
	bool function{ true };
	if (function) // todo this needs to be changed
	{
		if (DD(tokenLexPair))
		{
			if ('(')
			{
				if (E(tokenLexPair))
				{
					if (')')
					{
						if (J(tokenLexPair))
						{
							if (I(tokenLexPair))
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
bool SyntaxAnalyzer::E(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "E" };
	bool isE{ true };

	if (F(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (CC(tokenLexPair))
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
bool SyntaxAnalyzer::F(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "F" };
	bool isF{ true };

	if (G(tokenLexPair))
	{
		if (F_(tokenLexPair))
		{
			std::cout << "Production Rule: " << rule;
		}
		else isF = false;
	}
	else isF = false;


	return isF;
}

//	G	->	M	H
bool SyntaxAnalyzer::G(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "G" };
	bool isG{ true };

	if (M(tokenLexPair))
	{
		if (H(tokenLexPair))
		{
			std::cout << "Production Rule: " << rule;
		}
		else isG = false;
	}
	else isG = false;


	return isG;
}

// H	->	integer	|	boolean	|	real
bool SyntaxAnalyzer::H(std::pair<std::string, std::string> tokenLexPair)
{
	bool isInt{ true };
	bool isBool{ true };
	bool isReal{ true };

	if (isInt)
	{
		return true;
	}
	else if (isBool)
	{
		return true;
	}
	else if (isReal)
	{
		return true;
	}

	return false;
}

//  I	->	{	N	}
bool SyntaxAnalyzer::I(std::pair<std::string, std::string> tokenLexPair)
{
	if ('{')
	{
		if (N(tokenLexPair))
		{
			if ('}')
			{
				return true;
			}
			else return false;
		}
		else return false;
	}
	else	return false;
}

//	J -> K | CC
bool SyntaxAnalyzer::J(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "J" };
	bool isJ{ true };

	if (K(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (CC(tokenLexPair))
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
bool SyntaxAnalyzer::K(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "K" };
	bool isK{ true };

	if (L(tokenLexPair))
	{
		if (';')
		{
			std::cout << "Production Rule: " << rule;
		}
		else isK = false;
	}
	else isK = false;

	return isK;
}

// L	->	integer	M	|	boolean	M	|	real	M
bool SyntaxAnalyzer::L(std::pair<std::string, std::string> tokenLexPair)
{
	bool isInt{ true };
	bool isBool{ true };
	bool isReal{ true };

	if (isInt)
	{
		if(M(tokenLexPair)) return true;
	}
	else if (isBool)
	{
		if(M(tokenLexPair)) return true;
	}
	else if (isReal)
	{
		if(M(tokenLexPair)) return true;
	}

	return false;
}

//	M	->	DD	M'
bool SyntaxAnalyzer::M(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "M" };
	bool isM{ true };

	if (DD(tokenLexPair))
	{
		if (M_(tokenLexPair))
		{
			std::cout << "Production Rule: " << rule;
		}
		else isM = false;
	}
	else isM = false;


	return isM;
}

// N	->	O	N'
bool SyntaxAnalyzer::N(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "N" };
	bool isN{ true };

	if (O(tokenLexPair))
	{
		if (N_(tokenLexPair))
		{
			std::cout << "Production Rule: " << rule;
		}
		else isN = false;
	}
	else isN = false;


	return isN;
}

// O	->	P	|	Q	|	R	|	S	|	T	|	U	|	V
bool SyntaxAnalyzer::O(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "O" };
	bool isO{ true };

	if (P(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (Q(tokenLexPair)) 
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (R(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (S(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (T(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (U(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else if (V(tokenLexPair))
	{
		std::cout << "Production Rule: " << rule;
	}
	else isO = false;


	return isO;
}

// P	->	{	N	}
bool SyntaxAnalyzer::P(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "P" };
	bool isP{ true };
	if ('{')
	{
		if (N(tokenLexPair))
		{
			if ('}')
			{
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
bool SyntaxAnalyzer::Q(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "Q" };

	bool isQ{ true };
	if (DD(tokenLexPair))
	{
		if ('=')
		{
			if (Y(tokenLexPair))
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
bool SyntaxAnalyzer::R(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "R" };
	bool isR{ true };

	return isR;
}

// S	->	return	S'
bool SyntaxAnalyzer::S(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "S" };
	bool isS{ true };

	return isS;
}

// T	->	put	(	Y	)	;
bool SyntaxAnalyzer::T(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "T" };
	bool isT{ true };

	return isT;
}

// U	->	get	(	M	)	;
bool SyntaxAnalyzer::U(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "U" };
	bool isU{ true };

	return isU;
}

// V	->	while	(	W	)	O
bool SyntaxAnalyzer::V(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "V" };
	bool isV{ true };

	return isV;
}

// W	->	Y	X	Y
bool SyntaxAnalyzer::W(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "W" };
	bool isW{ true };

	return isW;
}

// X	->	==	|	!=	|	>	|	<	|	<=	|	=>
bool SyntaxAnalyzer::X(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "X" };
	bool isX{ true };

	return isX;
}

// Y	->	Z	Y'
bool SyntaxAnalyzer::Y(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "Y" };
	bool isY{ true };

	return isY;
}

// Z	->	AA	Z'
bool SyntaxAnalyzer::Z(std::pair<std::string, std::string> tokenLexPair)
{
	std::string rule{ "Z" };
	bool isZ{ true };

	return isZ;
}

// AA	->	-	BB	|	BB
bool SyntaxAnalyzer::AA(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// BB	->	DD	BB'	|	EE	|	(	Y	)	|	FF	|	TRUE	|	FALSE
bool SyntaxAnalyzer::BB(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// CC	->	epsilon
bool SyntaxAnalyzer::CC(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// DD -> identifier
bool SyntaxAnalyzer::DD(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// EE -> integer
bool SyntaxAnalyzer::EE(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// FF -> real
bool SyntaxAnalyzer::FF(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// Y'	->	+	Z	Y'	|	-	Z	Y'	|	epsilon
bool SyntaxAnalyzer::Y_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// Z'	->	*	AA	Z'	|	/	AA	Z'	|	epsilon
bool SyntaxAnalyzer::Z_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// C'	->	epsilon	|	C
bool SyntaxAnalyzer::C_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// F'	->	epsilon	|	,	F
bool SyntaxAnalyzer::F_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// K'	->	epsilon	|	K
bool SyntaxAnalyzer::K_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// M'	->	epsilon	|	,	M
bool SyntaxAnalyzer::M_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// N'	->	epsilon	|	N
bool SyntaxAnalyzer::N_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// R'	->	endif	|	else	O	endif
bool SyntaxAnalyzer::R_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// S'	->	;	|	Y	;
bool SyntaxAnalyzer::S_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

// BB'	->	epsilon	|	(	M	)
bool SyntaxAnalyzer::BB_(std::pair<std::string, std::string> tokenLexPair)
{
	return false;
}

#pragma endregion 