#pragma once
#include "Agent.h"
class Player :
    public Agent
{
public:
    bool hasGun = false;
    Player(Grid* layer);
};

