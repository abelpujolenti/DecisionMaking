#pragma once
typedef void (*funcPointer)(void);

class Enemy;

class PointerState
{
protected:
	Enemy* context;
	void (Enemy::*enter)();
	void (Enemy::*exit)();
	void (Enemy::*update)();
public:
	PointerState(Enemy* context, void (Enemy::*enter)(), void (Enemy::*exit)(), void (Enemy::*update)());
	PointerState();
	void Enter();
	void Exit();
	void Update();
};

