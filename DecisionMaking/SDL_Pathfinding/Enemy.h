#pragma once
#include "Agent.h"
#include "EnemyPFSM.h"

class Enemy :
    public Agent
{
private:
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
    Enemy();
    void update(float dtime, SDL_Event* event) override;
};

