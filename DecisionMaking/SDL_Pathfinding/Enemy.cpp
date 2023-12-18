#include "Enemy.h"



Enemy::Enemy()
{
	void (Enemy:: *wanderEnter)();
	wanderEnter = &Enemy::WanderEnter;
	void (Enemy:: *wanderExit)();
	wanderExit = &Enemy::WanderExit;
	void (Enemy:: *wanderUpdate)();
	wanderUpdate = &Enemy::WanderUpdate;
	PointerState wanderState(this, wanderEnter, wanderExit, wanderUpdate);
	void (Enemy:: *chaseEnter)();
	chaseEnter = &Enemy::ChaseEnter;
	void (Enemy:: *chaseExit)();
	chaseExit = &Enemy::ChaseExit;
	void (Enemy:: *chaseUpdate)();
	chaseUpdate = &Enemy::ChaseUpdate;
	PointerState chaseState(this, chaseEnter, chaseExit, chaseUpdate);
	void (Enemy:: *fleeEnter)();
	fleeEnter = &Enemy::FleeEnter;
	void (Enemy:: *fleeExit)();
	fleeExit = &Enemy::FleeExit;
	void (Enemy::*fleeUpdate)();
	fleeUpdate = &Enemy::FleeUpdate;
	PointerState fleeState(this, fleeEnter, fleeExit, fleeUpdate);

	enemyPFSM = new EnemyPFSM(wanderState);
	enemyPFSM->AddState("Wander", wanderState);
	enemyPFSM->AddState("Chase", chaseState);
	enemyPFSM->AddState("Flee", fleeState);
}

void Enemy::update(float dtime, SDL_Event* event)
{
	Agent::update(dtime, event);
	enemyPFSM->GetCurrentState().Update();
}

void Enemy::WanderEnter()
{
}

void Enemy::WanderExit()
{
}

void Enemy::WanderUpdate()
{
	setPosition(getPosition() + Vector2D(.05, 0));
}

void Enemy::ChaseEnter()
{
}

void Enemy::ChaseExit()
{
}

void Enemy::ChaseUpdate()
{
}

void Enemy::FleeEnter()
{
}

void Enemy::FleeExit()
{
}

void Enemy::FleeUpdate()
{
}
