//#include "..\StateTable.h"
//
//State::State(int ID, bool isAcceptState, std::vector<Transition> transVec) 
//	: m_stateID( ID ), m_isAcceptState( isAcceptState ), m_transVec(transVec)
//{
//
//	
//
//
//}
//
//
//StateTable::StateTable()
//{
//	
//;
//	std::vector<Transition> tranVec0;
//	Transition tempTrans01;
//	tempTrans01.m_targetStateID = 1((StateTable::eInputType::LETTER, 1));
//	Transition tempTrans02{ (StateTable::eInputType::DIGIT, 2) };
//	tranVec0.push_back(tempTrans01);
//	tranVec0.push_back(tempTrans02);
//
//	std::vector<Transition> tranVec1;
//	Transition tempTrans11{ (StateTable::eInputType::LETTER, 1) };
//	Transition tempTrans12{ (StateTable::eInputType::DIGIT, 1) };
//	Transition tempTrans13{ (StateTable::eInputType::UNDERSCORE, 1) };
//	tranVec1.push_back(tempTrans11);
//	tranVec1.push_back(tempTrans12);
//	tranVec1.push_back(tempTrans13);
//
//	std::vector<Transition> tranVec2;
//	Transition tempTrans21{ (StateTable::eInputType::DIGIT, 2) };
//	Transition tempTrans22{ (StateTable::eInputType::PERIOD, 3) };
//	tranVec2.push_back(tempTrans21);
//	tranVec2.push_back(tempTrans22);
//
//	std::vector<Transition> tranVec3;
//	Transition tempTrans31{ (StateTable::eInputType::DIGIT, 4) };
//	tranVec3.push_back(tempTrans31);
//
//
//	std::vector<Transition> tranVec4;
//	Transition tempTrans41{ (StateTable::eInputType::DIGIT, 4) };
//	tranVec4.push_back(tempTrans41);		
//	
//	m_states.push_back(State(0, false, tranVec0));
//	m_states.push_back(State(1, true, tranVec1));
//	m_states.push_back(State(2, true, tranVec2));
//	m_states.push_back(State(3, true, tranVec3));
//	m_states.push_back(State(4, true, tranVec4));
//
//	
//};
//
//
//int StateTable::GetNextState(int currentState, int inputType) const
//{
//	return m_states[currentState].m_transVec[inputType].m_targetStateID;	
//	
//}
//
//
