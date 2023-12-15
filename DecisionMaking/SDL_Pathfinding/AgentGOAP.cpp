#include "AgentGOAP.h"
#include "ActionGOAP.h"

AgentGOAP::AgentGOAP()
{        
    _getMazeElementsPositionFunctions = std::map<int, Vector2D(AgentGOAP::*)()> {
        {GET_RED_KEY_POSITION, &AgentGOAP::GetRedKeyPosition},
        {GET_ORANGE_KEY_POSITION, &AgentGOAP::GetOrangeKeyPosition},
        {GET_YELLOW_KEY_POSITION, &AgentGOAP::GetYellowKeyPosition},
        {GET_GREEN_KEY_POSITION, &AgentGOAP::GetGreenKeyPosition},
        {GET_BLUE_KEY_POSITION, &AgentGOAP::GetBlueKeyPosition},
        {GET_PURPLE_KEY_POSITION, &AgentGOAP::GetPurpleKeyPosition},
        {GET_COIN_POSITION, &AgentGOAP::GetCoinPosition}
    };
}

void AgentGOAP::SetKeyPositions(Vector2D keyPositions[])
{
    for (int i = 0; i < 8; ++i)
    {
        _keyPositions[i] = keyPositions[i];
    }
}

void AgentGOAP::SetCoinPosition(const Vector2D& coinPosition)
{
    _coinPosition = coinPosition;
}

Vector2D AgentGOAP::GetMazeElementPositionByGivenIndex(int mazeElementIndex)
{
    return (this->*_getMazeElementsPositionFunctions[mazeElementIndex])();
}

Vector2D AgentGOAP::GetCoinPosition()
{
    return _coinPosition;
}

Vector2D AgentGOAP::GetRedKeyPosition()
{
    return _keyPositions[2];
}

Vector2D AgentGOAP::GetOrangeKeyPosition()
{
    return _keyPositions[3];
}

Vector2D AgentGOAP::GetYellowKeyPosition()
{
    return _keyPositions[4];
}

Vector2D AgentGOAP::GetGreenKeyPosition()
{
    return _keyPositions[5];
}

Vector2D AgentGOAP::GetBlueKeyPosition()
{
    return _keyPositions[6];
}

Vector2D AgentGOAP::GetPurpleKeyPosition()
{
    return _keyPositions[7];
}
