#include "PFSM.h"

PFSM::PFSM(PointerState defaultState)
{
    currentState = new PointerState(defaultState);
}

PointerState PFSM::GetCurrentState()
{
    return *currentState;
}

void PFSM::SetState(PointerState newState)
{
    currentState->Exit();
    *currentState = newState;
    currentState->Enter();
}
