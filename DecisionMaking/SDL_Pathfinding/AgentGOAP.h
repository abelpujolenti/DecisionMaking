#pragma once
#include <functional>
#include <map>

#include "Agent.h"

struct ActionGOAP;

#define GET_RED_KEY_POSITION 2
#define GET_ORANGE_KEY_POSITION 3
#define GET_YELLOW_KEY_POSITION 4
#define GET_GREEN_KEY_POSITION 5
#define GET_BLUE_KEY_POSITION 6
#define GET_PURPLE_KEY_POSITION 7
#define GET_COIN_POSITION 8

class AgentGOAP : public Agent
{
private:
    std::map<int, Vector2D(AgentGOAP::*)()> _getMazeElementsPositionFunctions;
    
    
public:
    AgentGOAP();
    ~AgentGOAP() = default;
    Vector2D GetMazeElementPositionByGivenIndex(int mazeElementIndex);
    
};
