#pragma once
#include "Include/State.h"
#include <vector>
class StateTable
{
public:
	StateTable(std::vector<State> stateVec);
	enum eInputType{SPACE=0,LETTER,DIGIT, UNKNOWN};
	int GetNextState(int currentState, int inputType) const;

private:
	std::vector<State> states{};


};

