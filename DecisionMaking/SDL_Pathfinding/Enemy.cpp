#include "Enemy.h"

Enemy::Enemy(Grid* layer, Player* player) : Agent(layer)
{
	this->player = player;

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

	max_velocity = 100;
	draw_path = false;
}

void Enemy::update(float dtime, SDL_Event* event)
{
	Agent::update(dtime, event);
	Vector2D cellPos = layer->pix2cell(position);
	if (currentTargetIndex == -1 && !layer->isValidCell(cellPos)) {
		if (layer->isValidCell(cellPos + Vector2D(1, 0))) {
			setPosition(layer->cell2pix(cellPos + Vector2D(1, 0)));
		}
		else if (layer->isValidCell(cellPos + Vector2D(-1, 0))) {
			setPosition(layer->cell2pix(cellPos + Vector2D(-1, 0)));
		}
		else if (layer->isValidCell(cellPos + Vector2D(0, 1))) {
			setPosition(layer->cell2pix(cellPos + Vector2D(0, 1)));
		}
		else {
			setPosition(layer->cell2pix(cellPos + Vector2D(0, -1)));
		}
	}
	enemyPFSM->GetCurrentState().Update();
}

void Enemy::WanderEnter()
{
}

void Enemy::WanderExit()
{
	clearPath();
}

void Enemy::WanderUpdate()
{
	if (Vector2D::Distance(layer->pix2cell(position), layer->pix2cell(player->getPosition())) <= chaseDistance) {
		enemyPFSM->SetStateByName("Chase");
		return;
	}

	if (currentTargetIndex == -1) {
		Vector2D enemyPosition = Vector2D(-1, -1);
		while ((!layer->isValidCell(enemyPosition)))
			enemyPosition = Vector2D((float)(rand() % layer->getNumCellX()), (float)(rand() % layer->getNumCellY()));
		LoadPath(position, layer->cell2pix(enemyPosition), *layer);
	}
}

void Enemy::ChaseEnter()
{
}

void Enemy::ChaseExit()
{
	clearPath();
}

void Enemy::ChaseUpdate()
{
	if (Vector2D::Distance(layer->pix2cell(position), layer->pix2cell(player->getPosition())) > chaseDistance) {
		enemyPFSM->SetStateByName("Wander");
		return;
	}

	if (player->hasGun) {
		enemyPFSM->SetStateByName("Flee");
		return;
	}

	if (currentTargetIndex == -1 && Vector2D::Distance(layer->pix2cell(position), layer->pix2cell(player->getPosition())) > 1) {
		LoadPath(position, player->getPosition(), *layer);
	}
}

void Enemy::FleeEnter()
{
}

void Enemy::FleeExit()
{
}

void Enemy::FleeUpdate()
{
	if (Vector2D::Distance(layer->pix2cell(position), layer->pix2cell(player->getPosition())) > chaseDistance) {
		enemyPFSM->SetStateByName("Wander");
		return;
	}

	if (!player->hasGun) {
		enemyPFSM->SetStateByName("Chase");
		return;
	}

	if (currentTargetIndex == -1) {
		Vector2D enemyPosition = Vector2D(-1, -1);
		int i = 0;
		while ((!layer->isValidCell(enemyPosition)) || Vector2D::Distance(enemyPosition, layer->pix2cell(player->getPosition())) < fleeDistance - i / 3) {
			enemyPosition = Vector2D((float)(rand() % layer->getNumCellX()), (float)(rand() % layer->getNumCellY()));
			i++;
		}
		LoadPath(position, layer->cell2pix(enemyPosition), *layer);
	}
}
