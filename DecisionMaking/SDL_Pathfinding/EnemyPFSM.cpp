#include "EnemyPFSM.h"

EnemyPFSM::EnemyPFSM(PointerState defaultState) : PFSM(defaultState)
{
}

void EnemyPFSM::AddState(std::string name, PointerState newState)
{
	states[name] = newState;
}

void EnemyPFSM::SetStateByName(std::string name)
{
	SetState(states[name]);
}


