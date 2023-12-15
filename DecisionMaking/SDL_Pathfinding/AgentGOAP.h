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
    
    Vector2D _keyPositions[8];
    Vector2D _coinPosition;
    
    Vector2D GetRedKeyPosition();
    Vector2D GetOrangeKeyPosition();
    Vector2D GetYellowKeyPosition();
    Vector2D GetGreenKeyPosition();
    Vector2D GetBlueKeyPosition();
    Vector2D GetPurpleKeyPosition();
    
public:
    AgentGOAP();
    ~AgentGOAP() = default;
    void SetKeyPositions(Vector2D keyPositions[]);
    void SetCoinPosition(const Vector2D& coinPosition);
    Vector2D GetMazeElementPositionByGivenIndex(int mazeElementIndex);
    Vector2D GetCoinPosition();
    
};
