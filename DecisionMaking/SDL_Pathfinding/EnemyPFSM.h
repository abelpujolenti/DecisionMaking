#pragma once
#include "PFSM.h"

class EnemyPFSM :
    public PFSM
{
private:
    PointerState wanderState;
    PointerState chaseState;
    PointerState fleeState;
public:
    void SetWanderState();
    void SetChaseState();
    void SetFleeState();
};

