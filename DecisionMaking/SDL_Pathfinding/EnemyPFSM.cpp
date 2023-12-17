#include "EnemyPFSM.h"

void EnemyPFSM::SetWanderState()
{
	SetState(wanderState);
}

void EnemyPFSM::SetChaseState()
{
	SetState(chaseState);
}

void EnemyPFSM::SetFleeState()
{
	SetState(fleeState);
}
