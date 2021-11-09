#pragma once
#include <utility>
#include <string>
#include <vector>
#include <map>

class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(std::vector<std::pair<std::string, std::string>> tokenizedSource) : sourcePairs{ tokenizedSource }
	{
		currentPair = sourcePairs.begin();
	}
	bool Analyze() { return A(); }
	
	std::string RuleNameConversion(std::string simplifiedRuleName) const
	{
		return AbstractRuleNameConversion.at(simplifiedRuleName);
	}

	std::string GetConversion(std::string simplifiedRuleName) const
	{
		return AbstractEquivalenceMap.at(simplifiedRuleName);
	}

private:

	void PrintRule(std::string theRule, std::string theRuleDef) const;

	std::map<std::string, std::string> AbstractRuleNameConversion
	{
		{"A", "Rat21F"},
		{"B", "Opt Function Definitions"},
		{"C", "Function Definitions"},
		{"D", "Function"},
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
		{"DD", "Function'"},
		{"EE", "Opt Parameter List'"},
		{"FF", "Parameter List'"},
		{"Y'", "Expression'"},
		{"Z'", "Term'"},
		{"C'","Function Definitions'"},
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
		{"A", "<B>  #  <J>  <N>  #"},
		{"B", "<C>  |  <CC>"},
		{"C", "<D>  <C'>"},
		{"D", "function  <DD>  (  <E>  )  <J>  <I>"},
		{"E", "<F>  |  <CC>"},
		{"F", "<G>  <F'>"},
		{"G", "<M>  <H>"},
		{"H", "integer  |  boolean  |  real"},
		{"I", "{  <N>  }"},
		{"J", "<K>  |  <CC>"},
		{"K", "<L>  ;  <K'>"},
		{"L", "integer  <M>  |  boolean  <M>  |  real  <M>"},
		{"M", "<DD>  <M'>"},
		{"N", "<O>  <N'>"},
		{"O", "<P>  |  <Q>  |  <R>  |  <S>  |  <T>  |  <U>  |  <V>"},
		{"P", "{  <N>  }"},
		{"Q", "<DD>  =  <Y>"},
		{"R", "if  (  <W>  )  <O>  <R'>"},
		{"S", "return  <S'>"},
		{"T", "put  (  <Y>  )  ;"},
		{"U", "get  (  <M>  )  ;"},
		{"V", "while  (  <W>  )  <O>"},
		{"W", "<Y>  <X>  <Y>"},
		{"X", "==  |  !=  |  >  |  <  |  <=  |  =>"},
		{"Y", "<Z>  <Y'>"},
		{"Z", "<AA>  <Z'>"},
		{"AA", "-  <BB>  |  <BB>"},
		{"BB", "<DD>  <BB'>  |  <EE>  |  (  <Y>  )  |  <FF>  |  TRUE  |  FALSE"},
		{"CC", "epsilon"},
		{"DD", "identifier"},
		{"EE", "integer"},
		{"FF", "real"},
		{"Y'", "+  <Z>  <Y'>  |  -  <Z>  <Y'>  |  epsilon"},
		{"Z'", "*  <AA>  <Z'>  |  /  <AA>  <Z'>  |  epsilon"},
		{"C'", "epsilon  |  <C>"},
		{"F'", "epsilon  |  ,  <F>"},
		{"K'", "epsilon  |  <K>"},
		{"M'", "epsilon  |  ,  <M>"},
		{"N'", "epsilon  |  <N>"},
		{"R'", "endif  |  else  <O>  endif"},
		{"S'", ";  |  <Y>  ;"},
		{"BB'", "epsilon  |  (  <M>  )"},
	
	};

	std::map<std::string, std::string> EquivalenceMap
	{
		{"Rat21F", "<Opt Function Definitions>  #  <Opt Declaration List>  <Statement List>  #"},
		{"Opt Function Definitions", "<Function Definitions>  |  <Empty>"},
		{"Function Definitions", "<Function>  <Function Definitions'>"},
		{"Function", "function  <Identifier>  (  <FunctionOpt Parameter List>  )  <Opt Declaration List>  <Body>"},
		{"FunctionOpt Parameter List", "<Parameter List>  |  <Empty>"},
		{"Parameter List", "<Parameter>  <Parameter List'>"},
		{"Parameter", "<IDs>  <Qualifier>"},
		{"Qualifier", "integer  |  boolean  |  real"},
		{"Body", "{  <Statement List>  }"},
		{"Opt Declaration List", "<Declaration List>  |  <Empty>"},
		{"Declaration List", "<Declaration>  ;  <Declaration List'>"},
		{"Declaration", "integer  <IDs>  |  boolean  <IDs>  |  real  <IDs>"},
		{"IDs", "<Identifier>  <IDs'>"},
		{"Statement List", "<Statement>  <Statement List'>"},
		{"Statement", "<Compound>  |  <Assign>  |  <If>  |  <Return>  |  <Print>  |  <Scan>  |  <While>"},
		{"Compound", "{  <Statement List>  }"},
		{"Assign", "<Identifier>  =  <Expression>"},
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
		{"Primary", "<Identifier>  <Primary'>  |  <Integer>  |  (  <Expression>  )  |  <Real>  |  TRUE  |  FALSE"},
		{"Empty", "epsilon"},
		{"Identifier", "identifier"},
		{"Integer", "integer"},
		{"FF", "real"},
		{"Expression'", "+  <Term>  <Expression'>  |  -  <Term>  <Expression'>  |  epsilon"},
		{"Term'", "*  <Factor>  <Term'>  |  /  <Factor>  <Term'>  |  epsilon"},
		{"Function Definitions'", "epsilon  |  <Function Definitions>"},
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
	bool B( );
	bool C( );
	bool D( );
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
	bool FF( );
	bool Y_( );
	bool Z_( );
	bool C_( );
	bool F_( );
	bool K_( );
	bool M_( );
	bool N_( );
	bool R_( );
	bool S_( );
	bool BB_( );
#pragma endregion

	std::vector<std::pair<std::string, std::string>> sourcePairs;
	std::vector<std::pair<std::string, std::string>>::iterator currentPair;

};