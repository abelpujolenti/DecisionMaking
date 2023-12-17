#include "PointerState.h"

PointerState::PointerState(func_t enter, func_t exit, func_t update)
{
	this->enter = enter;
	this->exit = exit;
	this->update = update;
}

void PointerState::Enter()
{
	enter();
}

void PointerState::Exit()
{
	exit();
}

void PointerState::Update()
{
	update();
}
