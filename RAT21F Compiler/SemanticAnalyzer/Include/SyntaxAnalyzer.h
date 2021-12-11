// SyntaxAnalyzer.h

/* This file is the header that holds the SA class and function signatures for the class.
//  There are also various containers to convert from a simplified representation of non-terminals and
//  a non-abstract version. Currently it is set to simplified only and this feature is not fully implemented.

Author: Joshua Lollis
Last Edited: 11/10/21
CPSC-323 Project 2 Syntax Analyzer
Fall 20218*/

#pragma once
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stack>


class SyntaxAnalyzer
{
public:

  SyntaxAnalyzer(std::vector<std::pair<std::string, std::string>> tokenizedSource, std::string& outputString);

	bool Analyze() { return A(); }
	
	std::string RuleNameConversion(std::string simplifiedRuleName) const
	{
		return AbstractRuleNameConversion.at(simplifiedRuleName);
	}

	std::string GetConversion(std::string simplifiedRuleName) const
	{
		return AbstractEquivalenceMap.at(simplifiedRuleName);
	}

	void error_message(std::ostream& out, std::string msg)
	{
		out << msg;
	}

	void PrintGeneratedInstructions()
	{
		/*for (auto iter : addr_table)
		{
			std::cout << "\n" << iter.first << " " << iter.second;
		}*/

		std::cout << "\n\n******* Semantic Actions / Assembly Instructions **************\n";

		for (auto iter : instr_table)
		{
			std::cout << "\n" << iter.first << " " << iter.second.op << " " << iter.second.oprnd;
		}

	}

	void PrintSymbolTable()
	{
		for (auto iter : symb_table)
		{
			std::cout << "\n" << iter.first << " " << iter.second;
		}
	}

private:

	std::vector<std::string> operatorsVec{ "==", "!=", ">",  "<", "<=","=", ">"};

	std::map<std::string, std::string> AbstractRuleNameConversion
	{
		{"A", "Rat21F"},
		{"E", "Opt Parameter List"},
		{"F", "Parameter List"},
		{"G", "Parameter"},
		{"H", "Qualifier"},
		{"I", "Body"},
		{"J", "Opt Declaration List"},
		{"K", "Declaration List"},
		{"L", "Declaration"},
		{"M", "IDs"},
		{"N", "Statement List"},
		{"O", "Statement"},
		{"P", "Compound"},
		{"Q", "Assign"},
		{"R", "If"},
		{"S", "Return"},
		{"T", "Print"},
		{"U", "Scan"},
		{"V", "While"},
		{"W", "Condition"},
		{"X", "Relop"},
		{"Y", "Expression"},
		{"Z", "Term"},
		{"AA", "Factor"},
		{"BB", "Primary"},
		{"CC", "Empty"},
		{"DD", "Identifier"},
		{"EE", "Integer"},
		{"Y'", "Expression'"},
		{"Z'", "Term'"},
		{"F'","Parameter List'"},
		{"K'", "Declaration List"},
		{"M'", "IDs'"},
		{"N'", "Statement List'"},
		{"R'", "If'"},
		{"S'", "Return'"},
		{"BB'", "Primary'"},
	};

	std::map<std::string, std::string> AbstractEquivalenceMap
	{
		{"A", "#  <J>  <N>  #"},
		{"E", "<F>  |  <CC>"},
		{"F", "<G>  <F'>"},
		{"G", "<M>  <H>"},
		{"H", "integer  |  boolean"},
		{"I", "{  <N>  }"},
		{"J", "<K>  |  <CC>"},
		{"K", "<L>  ;  <K'>"},
		{"L", "integer  <M>  |  boolean  <M>"},
		{"M", "<DD>  <M'>"},
		{"N", "<O>  <N'>"},
		{"O", "<P>  |  <Q>  |  <R>  |  <S>  |  <T>  |  <U>  |  <V>"},
		{"P", "{  <N>  }"},
		{"Q", "<DD>  =  <Y>  ;"},										// A1) A -> id  = E { gen_instr (POPM,  get_address(id)) }
		{"R", "if  (  <W>  )  <O>  <R'>"},									// I ->   if ( C )  S   endif
		{"S", "return  <S'>"},
		{"T", "put  (  <Y>  )  ;"},
		{"U", "get  (  <M>  )  ;"},
		{"V", "while  (  <W>  )  <O>"},									// W1) W -> while (  C  )  S 
		{"W", "<Y>  <X>  <Y>"},											// W2) C -> E  R  E
		{"X", "==  |  !=  |  >  |  <  |  <=  |  =>"},						// W3) R ->  == | != | > | < | => | <= 
		{"Y", "<Z>  <Y'>"},												// A2) E ->  T  E’ 
		{"Z", "<AA>  <Z'>"},											// A5) T ->   F  T’ 
		{"AA", "-  <BB>  |  <BB>"},										
		{"BB", "<DD>  <BB'>  |  <EE>  |  (  <Y>  )  |  TRUE  |  FALSE"},
		{"CC", "epsilon"},
		{"DD", "identifier"},											// A8) F -> id { gen_instr (PUSHM, get_address(id) )
		{"EE", "integer"},
		{"Y'", "+  <Z>  <Y'>  |  -  <Z>  <Y'>  |  epsilon"},					// A3) E’ -> + T {  gen_intsr(ADD,  nil) }   E’ //  A4) E’ ->  epsilon
		{"Z'", "*  <AA>  <Z'>  |  /  <AA>  <Z'>  |  epsilon"},					// A6) T’ -> * F { gen_instr (MUL, nil) }  T’ // A7) T’ -> epsilon
		{"F'", ",  <F>  |  epsilon"},
		{"K'", "<K>  |  epsilon"},
		{"M'", ",  <M>  |  epsilon"},
		{"N'", "<N>  |  epsilon"},
		{"R'", "endif  |  else  <O>  endif"},
		{"S'", ";  |  <Y>  ;"},
		{"BB'", "(  <M>  )  |  epsilon"},
	
	};

	std::map<std::string, std::string> EquivalenceMap
	{
		{"Rat21F", "#  <Opt Declaration List>  <Statement List>  #"},
		{"Opt Parameter List", "<Parameter List>  |  <Empty>"},
		{"Parameter List", "<Parameter>  <Parameter List'>"},
		{"Parameter", "<IDs>  <Qualifier>"},
		{"Qualifier", "integer  |  boolean"},
		{"Body", "{  <Statement List>  }"},
		{"Opt Declaration List", "<Declaration List>  |  <Empty>"},
		{"Declaration List", "<Declaration>  ;  <Declaration List'>"},
		{"Declaration", "integer  <IDs>  |  boolean  <IDs>"},
		{"IDs", "<Identifier>  <IDs'>"},
		{"Statement List", "<Statement>  <Statement List'>"},
		{"Statement", "<Compound>  |  <Assign>  |  <If>  |  <Return>  |  <Print>  |  <Scan>  |  <While>"},
		{"Compound", "{  <Statement List>  }"},
		{"Assign", "<Identifier>  =  <Expression>  ;"},
		{"If", "if  (  <Condition>  )  <Statement>  <If'>"},
		{"Return", "return  <Return'>"},
		{"Print", "put  (  <Expression>  )  ;"},
		{"Scan", "get  (  <IDs>  )  ;"},
		{"While", "while  (  <Condition>  )  <Statement>"},
		{"Condition", "<Expression>  <Relop>  <Expression>"},
		{"Relop", "==  |  !=  |  >  |  <  |  <=  |  =>"},
		{"Expression", "<Term>  <Expression'>"},
		{"Term", "<Factor>  <Term'>"},
		{"Factor", "-  <Primary>  |  <Primary>"},
		{"Primary", "<Identifier>  <Primary'>  |  <Integer>  |  (  <Expression>  )  |  TRUE  |  FALSE"},
		{"Empty", "epsilon"},
		{"Identifier", "identifier"},
		{"Integer", "integer"},
		{"Real", "real"},
		{"Expression'", "+  <Term>  <Expression'>  |  -  <Term>  <Expression'>  |  epsilon"},
		{"Term'", "*  <Factor>  <Term'>  |  /  <Factor>  <Term'>  |  epsilon"},
		{"Parameter List'", "epsilon  |  ,  <Parameter List>"},
		{"Declaration List'", "epsilon  |  <Declaration List>"},
		{"IDs'", "epsilon  |  ,  <IDs>"},
		{"Statement List'", "epsilon  |  <Statement List>"},
		{"If'", "endif  |  else  <Statement>  endif"},
		{"Return'", ";  |  <Expression>  ;"},
		{"Primary'", "(  <IDs>  )  |  epsilon"},

	};

#pragma region Production Rules
	bool A();
	bool E( );
	bool F( );
	bool G( );
	bool H( );
	bool I( );
	bool J( );
	bool K( );
	bool L( );
	bool M( );
	bool N( );
	bool O( );
	bool P( );
	bool Q( );
	bool R( );
	bool S( );
	bool T( );
	bool U( );
	bool V( );
	bool W( );
	bool X( );
	bool Y( );
	bool Z( );
	bool AA( );
	bool BB( );
	bool CC( );
	bool DD( );
	bool EE( );
	bool Y_( );
	bool Z_( );
	bool F_( );
	bool K_( );
	bool M_( );
	bool N_( );
	bool R_( );
	bool S_( );
	bool BB_( );

#pragma endregion

#pragma region Print Function Signatures
	void PrintOnCall(std::string ruleName, std::string rule) ;
	void PrintRecognizedString(std::pair<std::string, std::string> tokLex) ;
	void PrintAcceptedRule(std::string ruleName, std::string rule) ;
	void PrintRejectedRule(std::string ruleName, std::string rule) ;
	void PrintSuccessText() ;

	void HandlePrintOnCall(std::string ruleName);
	void HandlePrintRecognized(std::pair<std::string, std::string> tokLex);
	void HandlePrintAccepted(std::string ruleName);
	void HandlePrintRejected(std::string ruleName);
	void HandlePrintSuccessText();

	void Expected(std::string msg) const { std::cout << "\nExpected " << msg; }
	
#pragma endregion

#pragma region Symbol Table Handling

	const int FIRST_SYMTBL_ADDR{ 7000 };
	const int FINAL_SYMTBL_ADDR{ 7999 };
	int symbAddr{ FIRST_SYMTBL_ADDR};

	int FirstSymbAddr() const { return FIRST_SYMTBL_ADDR; }
	int SymbAddr() const { return symbAddr; }
	void IncrSymbAddr() { ++symbAddr; }

	std::map<int, std::string> symb_table;
	std::map<std::string, int> addr_table;

	void	insert_symbol(int addr, std::string symbol) 
	{ 
		symb_table[addr] = symbol; 
		addr_table[symbol] = addr;
	}
	bool		symbolExists(int addr) { return symb_table.find(addr) != symb_table.end(); }
	bool		symbolExists(std::string symbol) { return addr_table.find(symbol) != addr_table.end(); }
	int		get_address(std::string token) { return addr_table[token]; } // TODO finish implementing symbol table

#pragma endregion
	

#pragma region Instruction Handling
	const int FIRST_INSTR_ADDR{ 0 };
	const int FINAL_INSTR_ADDR{ 999 };

	int instrAddr{ FIRST_INSTR_ADDR + 1 };

	int FirstInstrAddr() const { return FIRST_INSTR_ADDR; }
	int InstrAddr() const { return instrAddr; }
	void IncrInstrAddr() { ++instrAddr; }

	struct Instruction
	{
		int address;
		std::string op;
		std::string oprnd;
	};

	std::map<int, Instruction> instr_table;

	void GenerateInstruction(std::string op, std::string oprnd)
	{

		instr_table[InstrAddr()].address = InstrAddr();
		instr_table[InstrAddr()].op = op;
		instr_table[InstrAddr()].oprnd = oprnd;
		IncrInstrAddr();

	}

	std::stack<int> jmpStack;
	void BackPatch(int jmpAddr)
	{
		int tempAddr = jmpStack.top();
		jmpStack.pop();
		instr_table[tempAddr].oprnd = std::to_string(jmpAddr);
	}

	
#pragma endregion

	std::vector<std::pair<std::string, std::string>> sourcePairs;
	std::vector<std::pair<std::string, std::string>>::iterator currentPair;

	std::string& outputStringRef;



};