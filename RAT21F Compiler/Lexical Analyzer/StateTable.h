//#pragma once
////#include "Include/State.h"
//#include <vector>
//
//struct Transition
//{
//public:
//	Transition(StateTable::eInputType inputTrigger, int targetState)
//	{
//		m_inputTrigger = inputTrigger;
//		m_targetStateID = targetState;
//	}
//
//public:
//	StateTable::eInputType m_inputTrigger;
//	int m_targetStateID;
//};
//
//struct State
//{
//public:
//	State(int ID, bool isAcceptState, std::vector<Transition> transVec);
//	int ID() const { return m_stateID; }
//	bool IsAcceptState() const { return m_isAcceptState; }
//
//	int m_stateID;
//	bool m_isAcceptState;
//	std::vector<Transition> m_transVec;
//};
//
//
//class StateTable
//{
//public:
//	StateTable();
//	enum eInputType{SPACE=0,LETTER,DIGIT, UNDERSCORE, PERIOD, UNKNOWN};
//	int GetNextState(int currentState, int inputType) const;
//
//private:
//
//	std::vector<State> m_states;
//
//
//};
//
