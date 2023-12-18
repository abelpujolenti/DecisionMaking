#pragma once
#include "PointerState.h"
#include <vector>
class PFSM
{
protected:
	PointerState* currentState;
public:
	PFSM(PointerState defaultState);
	PointerState GetCurrentState();
	void SetState(PointerState newState);
};

