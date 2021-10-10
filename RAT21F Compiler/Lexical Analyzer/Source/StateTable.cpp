#include "..\StateTable.h"

State::State(int ID, bool isAcceptState, std::vector<Transition> transVec) : m_stateID{ ID }, m_isAcceptState{ isAcceptState }, m_transVec{transVec}
{


}


StateTable::StateTable()
{
	
}

int StateTable::GetNextState(int currentState, int inputType) const
{
	return 0;
}


