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
