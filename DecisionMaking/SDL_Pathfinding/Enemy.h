#pragma once
#include "Agent.h"
#include "EnemyPFSM.h"
#include "Player.h"

class Enemy :
    public Agent
{
private:
    Player* player;

    EnemyPFSM* enemyPFSM;
    void WanderEnter();
    void WanderExit();
    void WanderUpdate();
    void ChaseEnter();
    void ChaseExit();
    void ChaseUpdate();
    void FleeEnter();
    void FleeExit();
    void FleeUpdate();
public:
    float chaseDistance = 15;
    float fleeDistance = 25;

    Enemy(Grid* layer, Player* player);
    void update(float dtime, SDL_Event* event) override;
};

