#pragma once

class State
{
public:
	State(int ID, bool isAcceptState);
	int ID() const { return m_stateID; }
	bool IsAcceptState() const { return m_isAcceptState; }
private:
	int m_stateID;
	bool m_isAcceptState;
};

