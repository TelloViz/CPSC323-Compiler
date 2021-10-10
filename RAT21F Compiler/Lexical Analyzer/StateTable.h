#pragma once
//#include "Include/State.h"
#include <vector>

class Transition
{
public:
	Transition(StateTable::eInputType inputTrigger, int targetState) : m_inputTrigger{ inputTrigger }, m_targetStateID{ targetState } {}
	StateTable::eInputType m_inputTrigger;
	int m_targetStateID;
};

class State
{
public:
	State(int ID, bool isAcceptState, std::vector<Transition> transVec);
	int ID() const { return m_stateID; }
	bool IsAcceptState() const { return m_isAcceptState; }
private:
	int m_stateID;
	bool m_isAcceptState;
	std::vector<Transition> m_transVec;
};


class StateTable
{
public:
	StateTable();
	enum eInputType{SPACE=0,LETTER,DIGIT, UNDERSCORE, PERIOD, UNKNOWN};
	int GetNextState(int currentState, int inputType) const;

private:

	std::vector<State> m_states
	{
		State( 0, false,		
			std::vector<Transition>
				{
					Transition(eInputType::LETTER, 1),
					Transition(eInputType::DIGIT, 2)
				}
		),
		State( 1, true,
			std::vector<Transition>
				{
					Transition(eInputType::LETTER, 1),
					Transition(eInputType::DIGIT, 1),
					Transition(eInputType::UNDERSCORE, 1)
				}
		),
		State(2, true,
		std::vector<Transition>
			{
				Transition(eInputType::DIGIT, 2),
				Transition(eInputType::PERIOD, 3)
			}
		),
		State(3, false,
		std::vector<Transition>
			{
				Transition(eInputType::DIGIT, 4)
			}
		),
		State(4, true,
		std::vector<Transition>
			{
				Transition(eInputType::DIGIT, 4)
			}
		)
	};
	
	std::vector<State> m_stateVec
	{
		State()

	}
	


};

