#include "PFSM.h"

PointerState PFSM::GetCurrentState()
{
    return currentState;
}

void PFSM::SetState(PointerState newState)
{
    currentState.Exit();
    currentState = newState;
    currentState.Enter();
}
