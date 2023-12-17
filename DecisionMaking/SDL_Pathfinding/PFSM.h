#pragma once
#include "PointerState.h"
#include <vector>
class PFSM
{
protected:
	PointerState currentState;
public:
	PointerState GetCurrentState();
	void SetState(PointerState newState);
};

