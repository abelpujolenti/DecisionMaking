#include "AgentGOAP.h"
#include "ActionGOAP.h"

AgentGOAP::AgentGOAP()
{        
}

Vector2D AgentGOAP::GetMazeElementPositionByGivenIndex(int mazeElementIndex)
{
    return (this->*_getMazeElementsPositionFunctions[mazeElementIndex])();
}