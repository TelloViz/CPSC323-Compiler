#include "../Include/SyntaxAnalyzer.h"
#include <string>
#include <iostream>


//	A	::=	B	#	J	N	#
bool SyntaxAnalyzer::A()
{
	std::string rule{ "A" };
	bool isA{ true };

	if (B())
	{
		if ('#')
		{
			if (J())
			{
				if (N())
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
	bool function{ true };
	if (function) // todo this needs to be changed
	{
		if (DD())
		{
			if ('(')
			{
				if (E())
				{
					if (')')
					{
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
bool SyntaxAnalyzer::I()
{
	bool isOpenBracket{ true };
	bool isCloseBracket{ true };

	if (isOpenBracket)
	{
		if (N())
		{
			if (isCloseBracket)
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
bool SyntaxAnalyzer::L()
{
	bool isInt{ true };
	bool isBool{ true };
	bool isReal{ true };

	if (isInt)
	{
		if(M()) return true;
	}
	else if (isBool)
	{
		if(M()) return true;
	}
	else if (isReal)
	{
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

