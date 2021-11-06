#pragma once
#include <utility>
#include <string>
#include <vector>

class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(std::vector<std::pair<std::string, std::string>> tokenizedSource) : sourcePairs{ tokenizedSource }
	{}
	bool Analyze() { return A(); }
	
private:

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