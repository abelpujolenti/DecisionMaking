#include "PointerState.h"

PointerState::PointerState(Enemy* context, void (Enemy::*enter)(), void (Enemy::*exit)(), void (Enemy::*update)())
{
	this->context = context;
	this->enter = enter;
	this->exit = exit;
	this->update = update;
}

PointerState::PointerState()
{
	context = nullptr;
	enter = nullptr;
	exit = nullptr;
	update = nullptr;
}

void PointerState::Enter()
{
	(*context.*enter)();
}

void PointerState::Exit()
{
	(*context.*exit)();
}

void PointerState::Update()
{
	(*context.*update)();
}
