#include "../Include/SyntaxAnalyzer.h"
#include <string>
#include <iostream>



/* Use these defines to toggle different modes of output text*/
// There are two pairs of toggles, one for Printing Non-Termainals on function call entry
// the other is to print the rull as it is accepted at the deepest nest of the function.
// both can be on at the same time and both have a verbose option
// the verbose option requires the both of the #define in the pair to be active
// ******************************************************************************************

//#define PRINT_RULE_ON_CALL		
//#define VERBOSE_PRINT_RULE_ON_CALL  // Both modes must be defined for Verbose to work	

//*****************************************************************************************

#define PRINT_RULE_ON_ACCEPT
#define VERBOSE_PRINT_RULE_ON_ACCEPT	// Both modes must be defined for Verbose to work

// **********************************************************************************************

#define PRINT_RECOGNIZE_LABEL

// *********************************************************************************************


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



#pragma region Production Rules
void SyntaxAnalyzer::PrintRule(std::string theRule, std::string theRuleDef) const
{
}


//	<A>	->	<B>	#	<J>	<N>	#
bool SyntaxAnalyzer::A()
{
	std::string rule{ "<A>" };
	std::string ruleDef{ "-> <B> # <J> <N> #" };
	bool isA{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule	
	#ifdef VERBOSE_PRINT_RULE_ON_CALL 
		<< "  ->  <B>  #  <J>  <N>  #";

		#else
		;
		#endif
	#endif

	if (B())
	{
		if (currentPair->second == "#")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED:  #"; 
			#endif

			++currentPair;
			if (J())
			{
				if (N())
				{
					if ('#')
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
						std::cout << "\nRECOGNIZED: #";
						#endif

						++currentPair;
						isA = true;

						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nACCEPTED:   " << rule
							#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT 
							<< "  ->  <B>  #  <J>  <N>  #";
							
							#else
							;
							#endif
						
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
	std::string rule{ "<B>" };
	bool isB{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule

		#ifdef VERBOSE_PRINT_RULE_ON_CALL 
		<< "  ->  <C> | <CC>";

		#else
		;
		#endif
	#endif

	if (C())
	{
		isB = true;
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
			#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT 
				<< "  -> ~<C>~  |  <CC>";

			#else
				;
			#endif
		#endif
	}
	else if (CC())
	{
		isB = true;
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT 
			<< "  ->  <C>  |  ~<CC>~";
#else
			;
#endif
#endif
	}
	else{}

	return isB;
}

//	C	->	D	C'
bool SyntaxAnalyzer::C()
{
	std::string rule{ "<C>" };
	bool isC{ false };
	
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  <D>  <C'>";
		#else
			;
		#endif	
	#endif

	if (D())
	{
		std::cout << "\n<D> ... Recognized";
		if (C_())
		{
			isC = true;
			
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED:   " << rule
				#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  <D>  <C'>";
				#else
					;
				#endif
			#endif
		}
	}

	return isC;
}

//	D	->	function	DD	(	E	)	J	I
bool SyntaxAnalyzer::D()
{
	std::string rule{ "<D>" };
	bool isD{ false };

#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  function <DD>  (  <E>  )  <J>  <I>";
#else	
		;
#endif	
#endif

	if (currentPair->second == "function") // todo this needs to be changed
	{
		++currentPair;
		if (DD())
		{			
			if (currentPair->second == "(")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
				std::cout << "\nRECOGNIZED: (";
				#endif

				++currentPair;
				if (E())
				{
					if (currentPair->second == ")")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
						std::cout << "\nRECOGNIZED: )";
						#endif

						++currentPair;

						if (J())
						{
							if (I())
							{
								isD = true;
								#ifdef PRINT_RULE_ON_ACCEPT 
								std::cout << "\nACCEPTED:   " << rule
									#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT	
										<< "  ->  function  <DD>  (  <E>  )  <J>  <I>";
									#else
										;
									#endif
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
	std::string rule{ "<E>" };
	bool isE{ true };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <F>  |  <CC>";
#else	
		;
#endif	
#endif

	if (F())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 

		std::cout << "\nACCEPTED: " << rule

			#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
						<< " ->  ~<F>~  |  <CC>";
			#else
				;
			#endif
		#endif
	}
	else if (CC())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED :   " << rule
			#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT 
				<< "  ->  <F>  |  ~<CC>~";
			#else 
				;
			#endif
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
	std::string rule{ "<F>" };
	bool isF{ true };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <G>  <F'>";
#else	
		;
#endif	
#endif

	if (G())
	{
		if (F_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED :   " << rule
				#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  <G>  <F'>";
				#else 
					;
				#endif
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
	std::string rule{ "<G>" };
	bool isG{ true };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <M>  <H>";
#else	
		;
#endif	
#endif

	if (M())
	{
		if (H())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED :   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  ->  <M>  <H>";
#else
				;
#endif
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
	std::string rule{ "<H>" };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  integer  |  boolean  |  real";
#else	
		;
#endif	
#endif

	if (currentPair->first == "integer")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: integer";
#endif
		++currentPair;
		return true;
	}
	else if (currentPair->first == "boolean")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: boolean";
#endif
		++currentPair;
		return true;
	}
	else if (currentPair->first == "real")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: real";
#endif
		++currentPair;
		return true;
	}

	return false;
}

//  I	->	{	<N>	}
bool SyntaxAnalyzer::I()
{

	std::string rule{ "<I>" };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->	{  <N>  }";
#else	
		;
#endif	
#endif

	if (currentPair->second == "{")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: {";
#endif
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
				std::cout << "\nRECOGNIZED: {";
#endif
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
	std::string rule{ "<J>" };
	bool isJ{ true }; 
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <K>  |  <CC>";
#else
		;
#endif	
#endif
	if (K())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:  " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< " -> ~<K>~ | <CC>";
#else
			;
#endif
		#endif
	}
	else if (CC())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:  " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< " -> <K> | ~<CC>~";
#else
			;
#endif
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
	std::string rule{ "<K>" };
	bool isK{ true };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <L>  ;  <K'>";
#else	
		;
#endif	
#endif

	if (L())
	{
		if (currentPair->second == ";")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED: ;";
#endif
			++currentPair;
			if (K_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  <L>  ;  <K'>";
#else
					;
#endif
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
	std::string rule{ "<L>" };
#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  integer  <M>  |  boolean  <M>  |  real  <M>";
#else	
		;
#endif	
#endif

	if (currentPair->second == "integer")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: integer";
#endif
		++currentPair;
		if(M()) return true;
	}
	else if (currentPair->second == "boolean")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: integer";
#endif
		++currentPair;
		if(M()) return true;
	}
	else if (currentPair->second == "real")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: real";
#endif
		++currentPair;
		if(M()) return true;
	}

	return false;
}

//	M	->	DD	M'
bool SyntaxAnalyzer::M()
{
	std::string rule{ "<M>" };
	bool isM{ true };

#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <DD>  <M'>";
#else	
		;
#endif
		#endif

	if (DD())
	{
		if (M_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED: " << rule
				#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  <DD> <M'>";
				#else
					;
				#endif
			#endif
		}
		else isM = false;
	}
	else isM = false;


	return isM;
}

// <N>	->	O	<N>'
bool SyntaxAnalyzer::N()
{
	std::string rule{ "<N>" };
	bool isN{ true };

	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <O>  <N'>";
		#else
			;
		#endif	
	#endif

	if (O())
	{
		if (N_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< " ->  <O>  <N'>";
#else
				;
#endif
			#endif
		}
		else isN = false;
	}
	else isN = false;


	return isN;
}

// <O>->	<P>	|	<Q>	|	<R>	|	<S>	|	<T>	|	<U>	|	<V>
bool SyntaxAnalyzer::O()
{
	std::string rule{ "<O>" };
	bool isO{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  <P>  | < Q > | < R > | < S > | < T >  | < U > |  <V>";
		#else 
			;
		#endif // VERBOSE_PRINT_RULE_ON_CALL

	#endif

	if (P())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ~<P>~  | < Q > | < R > | < S > | < T > | < U > |  <V>";
#else
			;
#endif
		#endif
	}
	else if (Q()) 
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <P>  |  ~<Q>~  | < R > | < S > | < T > | < U > |  <V>";
#else
			;
#endif
		#endif
	}
	else if (R())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <P>  | < Q > |  ~<R>~  | < S > | < T > | < U > |  <V>";
#else
			;
#endif
#endif
	}
	else if (S())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <P>  | < Q > | < R > |  ~<S>~  | < T > | < U > |  <V>";
#else
			;
#endif
		#endif
	}
	else if (T())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <P>  | < Q > | < R > | < S > |  ~<T>~  | < U > |  <V>";
#else
			;
#endif
#endif
	}
	else if (U())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <P>  | < Q > | < R > | < S > | < T > |  ~<U>~  |  <V>";
#else
			;
#endif
		#endif
	}
	else if (V())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <P>  |  <Q>  |  <R>  |  <S>  |  <T>  |  <U>  |  ~<V>~";
#else
			;
#endif
		#endif
	}
	else isO = false;


	return isO;
}

// <P>	->	{	<N>	}
bool SyntaxAnalyzer::P()
{
	std::string rule{ "<P>" };
	bool isP{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  {  <N>  }";
			#else
				;
			#endif
		#endif

	if (currentPair->second == "{")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: {";
#endif
		++currentPair;
		if (N())
		{
			if (currentPair->second == "}")
			{
				#ifdef PRINT_RECOGNIZE_LABEL 
				std::cout << "\nRECOGNIZED: }"; 
#endif
				isP = true;
				++currentPair;
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  {  <N>  }";
#else
					;
#endif
				#endif
			}
		}
	}

	return isP;
}

// Q	->	DD	=	Y
bool SyntaxAnalyzer::Q()
{
	std::string rule{ "<Q>" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <DD>  =  <Y>";
#else
		;
#endif
	#endif

	bool isQ{ true };
	if (DD())
	{
		if (currentPair->second == "=")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED: =";
#endif
			++currentPair;
			if (Y())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  <DD>  =  <Y>";
#else
					;
#endif
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
	std::string rule{ "<R>" };
	bool isR{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
	<< "  ->  if  (  <W>  )  <O>  <R'>";
#else
	;
#endif
	#endif

	if (currentPair->second == "if")
	{
		++currentPair;
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED: (";
#endif
			++currentPair;
			if (W())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
					std::cout << "\nRECOGNIZED: )"; 
#endif
					++currentPair;
					if (O())
					{
						if (R_())
						{
							isR = true;
							#ifdef PRINT_RULE_ON_ACCEPT 
							std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
								<< "  ->  if  (  <W>  )  <O>  <R'>";
#else
								;
#endif
							#endif
						}
					}
				}
			}
		}
	}

	return isR;
}

// S	->	return	S'
bool SyntaxAnalyzer::S()
{
	std::string rule{ "<S>" };
	bool isS{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  return  S'";
#else
		;
#endif
#endif

	if (currentPair->second == "return")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: return";
#endif
		++currentPair;
		if (S_())
		{
			isS = true;
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  ->  return  <S'>";
#else
				;
#endif
			#endif
		}
	}

	return isS;
}

// T	->	put	(	Y	)	;
bool SyntaxAnalyzer::T()
{
	std::string rule{ "<T>" };
	bool isT{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  put (  <Y>  )  ;";
#else
		;
#endif
#endif

	if (currentPair->second == "put")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: put";
#endif
		++currentPair;
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED: (";
#endif
			++currentPair;
			if (Y())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
					std::cout << "\nRECOGNIZED: )";
#endif
					++currentPair;
					if (currentPair->second == ";")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
						std::cout << "\nRECOGNIZED: ;";
#endif
						isT = true;
						++currentPair;
						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
							<< "  ->  put  (  <Y>  )  ;";
#else
							;
#endif
#endif

					}
				}
			}
		}
	}

	return isT;
}

// U	->	get	(	M	)	;
bool SyntaxAnalyzer::U()
{
	std::string rule{ "<U>" };
	bool isU{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  -> get  (  <M>  )  ;";
#else
		;
#endif
#endif

	if (currentPair->second == "get")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: get";
#endif
		++currentPair;
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED: (";
#endif
			++currentPair;
			if (M())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
					std::cout << "\nRECOGNIZED: )";
#endif
					++currentPair;
					if (currentPair->second == ";")
					{
						#ifdef PRINT_RECOGNIZE_LABEL 
						std::cout << "\nRECOGNIZED: ;";
#endif
						isU = true;
						++currentPair;
						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
							<< "  ->  get  (  <M>  )  ;";
#else
							;
#endif
#endif

					}
				}
			}
		}
	}

	return isU;

}

// V	->	while	(	W	)	O
bool SyntaxAnalyzer::V()
{
	std::string rule{ "<V>" };
	bool isV{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  while  (  <W>  )  <O>";
#else
		;
#endif
#endif

	if (currentPair->second == "while")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: while";
#endif
		++currentPair;
		if (currentPair->second == "(")
		{
			#ifdef PRINT_RECOGNIZE_LABEL 
			std::cout << "\nRECOGNIZED: (";
#endif
			++currentPair;
			if (W())
			{
				if (currentPair->second == ")")
				{
					#ifdef PRINT_RECOGNIZE_LABEL 
					std::cout << "\nRECOGNIZED: )";
#endif
					++currentPair;
					if (O())
					{
						isV = true;
						#ifdef PRINT_RULE_ON_ACCEPT 
						std::cout << "\nACCEPTED: " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
							<< "  ->  while  (  <W>  )  <O>";
#else
							;
#endif
#endif

					}
				}
			}
		}
	}

	return isV;
}

// W	->	Y	X	Y
bool SyntaxAnalyzer::W()
{
	std::string rule{ "<W>" };
	bool isW{ false };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule; 
#endif


	if (Y())
	{
		if (X())
		{
			if (Y())
			{
				isW = true;
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED: " << rule
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  <Y>  <X>  <Y>";
#else
					;
#endif
#endif
			}
		}
	}

	return isW;
}

// X	->	==	|	!=	|	>	|	<	|	<=	|	=>
bool SyntaxAnalyzer::X()
{
	std::string rule{ "<X>" };
	bool isX{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  ==  |  !=  |  >  |  <  |  <=  |  =>\n";
#else
		;
#endif
#endif

	if (currentPair->second == "==")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: ==";
#endif
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ~==~  |  !=  |  >  |  <  |  <=  |  =>";
#else
			;
#endif
#endif
	}
	else if (currentPair->second == "!=")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: !=";
		#endif
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED: " << rule 
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ==  |  ~!=~  |  >  |  <  |  <=  |  =>";
#else
			;
#endif
#endif
	}
	else if (currentPair->second == ">")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: >";
#endif
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ==  |  !=  |  ~>~  |  <  |  <=  |  =>";
#else
			;
#endif
#endif
	}
	else if (currentPair->second == "<")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: <";
#endif
#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ==  |  !=  |  >  |  ~<~  |  <=  |  =>";
#else
			;
#endif
#endif
	}
	else if (currentPair->second == "<=")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: <=";
#endif
#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
			<< " ->  ==  |  !=  |  >  |  <  |  ~<=~  |  =>";
#else
			;
#endif
#endif
	}
	else if (currentPair->second == "=>")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: =>";
#endif
#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef  VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ==  |  !=  |  >  |  <  |  <=  |  ~=>~";
#else
			;
#endif
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
	std::string rule{ "<Y>" };
	bool isY{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <Z>  <Y'>";
#else
		;
#endif
#endif

	if (Z())
	{
		if (Y_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED:   " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  -> <Z> <Y'>";
#else 
			;
#endif
#endif
		}
	}

	return isY;
}

// <Z>	->	<AA>	<Z'>
bool SyntaxAnalyzer::Z()
{
	std::string rule{ "<Z>" };
	bool isZ{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <AA>  <Z'>";
#else
		;
#endif
#endif



	if (AA())
	{
		if (Z_())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  ->  <AA>  <Z'>";
#else
				;
#endif
#endif
		}
	}

	return isZ;
}

// AA	->	-	BB	|	BB
bool SyntaxAnalyzer::AA()
{
	std::string rule{ "<AA>" };
	bool isAA{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  -  <BB>  |  <BB>";
#else
		;
#endif
#endif

	if (currentPair->second == "-")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: -";
#endif
		if (BB())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  ->  ~-<BB>~  |  <BB>";
#else
				;
#endif
#endif
		}
	}
	else if (BB())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  -<BB>  |  ~<BB>~";
#else
			;
#endif
#endif
	}
	else
	{
		isAA = false;
	}

	return isAA;
}

// <BB>	->	<DD>	<BB'>	|	<EE>	|	(	<Y>	)	|	<FF>	|	TRUE	|	FALSE
bool SyntaxAnalyzer::BB()
{
	std::string rule{ "<BB>" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <DD> <BB'>  |  <EE>  |  (  <Y>  |  <FF>  TRUE  |  FALSE";
#else
		;
#endif
#endif
	return false;
}

// CC	->	epsilon
bool SyntaxAnalyzer::CC()
{
	std::string rule{ "<CC>" };
	#ifdef PRINT_RULE_ON_CALL 
		std::cout << "\n" << rule
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  epsilon";
		#else
			;
		#endif
	#endif
	return true;
}

// DD -> identifier
bool SyntaxAnalyzer::DD()
{
	std::string rule{ "<DD>" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule 
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  identifier";
		#else
			;
		#endif
	#endif
	if (currentPair->first == "identifier")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: identifier";
#endif
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  identifier";
			#else
				;
			#endif
		#endif

		++currentPair;
		return true;
	}

	return false;
	
}

// EE -> integer
bool SyntaxAnalyzer::EE()
{

	std::string rule{ "<EE>" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  integer";
#else
		;
#endif
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
	std::string rule{ "<FF>" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  real";
#else
		;
#endif
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
	std::string rule{ "<Y_>" };
	bool isY_{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  +  <Z>  <Y'>  |  -  <Z>  <Y'>  |  epsilon";
#else
		;
#endif
#endif

	if (currentPair->second == "+")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: +";
#endif
		++currentPair;
		if (Z())
		{
			if (Y_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED:   " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  ~+ <Z> <Y'>~  |  - <Z><Y'> |  epsilon";
#else 
				;
#endif
#endif
			}
			else isY_ = false;
		}
		else isY_ = false;
	}
	else if (currentPair->second == "-")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: -";
#endif
		++currentPair;
		if (Z())
		{
			if (Y_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED:   " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->  +  <Z>  <Y'>  |  ~-  <Z>  <Y'>~  |  epsilon";
#else 
				;
#endif
#endif
			}
			else isY_ = false;
		}
		else isY_ = false;
	}
	else // epsilon
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  + <Z> <Y'>  |  -  <Z>  <Y'>  |  ~epsilon~";
#else 
		;
#endif
#endif
	}

	return isY_;
}

// Z'	->	*	AA	Z'	|	/	AA	Z'	|	epsilon
bool SyntaxAnalyzer::Z_()
{
	std::string rule{ "<Z_>" };
	bool isZ_{ true };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  *  <AA>  <Z'>  |  /  <AA>  <Z'>  |  epsilon";
#else
		;
#endif
#endif

	if (currentPair->second == "*")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: *";
#endif
		++currentPair;
		if (AA())
		{
			if (Z_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "->	*	AA	Z'	|	/	AA	Z'	|	epsilon";
#else
					;
#endif
#endif
			}
			else isZ_ = false;
		}
		else isZ_ = false;
	}
	else if (currentPair->second == "/")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: /";
#endif
		++currentPair;
		if (AA())
		{
			if (Z_())
			{
				#ifdef PRINT_RULE_ON_ACCEPT 
				std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
					<< "  ->	*	AA	Z'	|	/	AA	Z'	|	epsilon";
#else
					;
#endif
#endif
			}
			else isZ_ = false;
		}
		else isZ_ = false;
	}
	else // epsilon
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->	*	AA	Z'	|	/	AA	Z'	|	epsilon";
#else
			;
#endif
#endif
	}

	return isZ_;
}

// C'	->	epsilon	|	C
bool SyntaxAnalyzer::C_()
{
	std::string rule{ "<C_>" };
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  ->  <C>  |  epsilon";
#else
		;
#endif
#endif
	return true;
}

// F'	->	epsilon	|	,	F
bool SyntaxAnalyzer::F_()
{
	std::string rule{ "<F_>" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
	<< "  ->  ,  <F>  |  epsilon";
#else
	;
#endif
#endif
	return true;
}

// K'	->	epsilon	|	K
bool SyntaxAnalyzer::K_()
{
	std::string rule{ "<K_>" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule 
#ifdef VERBOSE_PRINT_RULE_ON_CALL
	<< "  ->  <K>  |  epsilon";
#else
	;
#endif
#endif


	if (K())
	{
		#ifdef PRINT_RULE_ON_ACCEPT
		std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  <K>  |  epsilon";
#else
			;
#endif

#endif
	}
	return true;
}

// M'	->	epsilon	|	,	M
bool SyntaxAnalyzer::M_()
{
	std::string rule{ "<M_>"};
	#ifdef PRINT_RULE_ON_CALL 
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
	<< "  -> ,  <M>  |  epsilon";
#else
	;
#endif
#endif

	if (currentPair->second == ",")
	{
		#ifdef PRINT_RECOGNIZE_LABEL 
		std::cout << "\nRECOGNIZED: ,";
#endif
		++currentPair;
		if (M())
		{
			#ifdef PRINT_RULE_ON_ACCEPT 
			std::cout << "\nACCEPTED:   " << rule
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  ->  ~, <M>~  |  epsilon";
#else 
				;
#endif
#endif
		}
	}
	else {
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule 
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
			<< "  ->  ,<M>  |  ~epsilon~";
#else 
			;
#endif
#endif
	}
	return true;
}

// <N'>	->	epsilon	|	<N>
bool SyntaxAnalyzer::N_()
{
	std::string rule{ "<N_>" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
		<< "  -> <N>  |  epsilon";
#else
	;
#endif
	#endif

	if(N())
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
			#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
				<< "  ->  ~<N>~  |  epsilon";
			#else
				;
			#endif
		 
		#endif
	}
	else
	{
		#ifdef PRINT_RULE_ON_ACCEPT 
		std::cout << "\nACCEPTED:   " << rule
			#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT 
				<< "  ->  <N>  |  ~epsilon~";
			#else
				;
			#endif
		#endif
	}
	return true; // because of the epsilon
}

// R'	->	endif	|	else	O	endif
bool SyntaxAnalyzer::R_()
{
	std::string rule{ "<R_>" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule
#ifdef VERBOSE_PRINT_RULE_ON_CALL
	<< "  ->  endif  |  else <O>  endif";
#else
	;
#endif
#endif
	return false;
}

// S'	->	;	|	Y	;
bool SyntaxAnalyzer::S_()
{
	std::string rule{ "<S_>" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule 
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  ;  |  Y  ;";
		#else
			;
		#endif		
	#endif
	return false;
}

// BB'	->	epsilon	|	(	M	)
bool SyntaxAnalyzer::BB_()
{
	std::string rule{ "<BB_>" };
	#ifdef PRINT_RULE_ON_CALL
	std::cout << "\n" << rule
		#ifdef VERBOSE_PRINT_RULE_ON_CALL
			<< "  ->  (  M  )  |  epsilon";
		#else
			;
		#endif // VERBOSE_PRINT_RULE_ON_CALL
	#endif

	return true;
}

#pragma endregion 