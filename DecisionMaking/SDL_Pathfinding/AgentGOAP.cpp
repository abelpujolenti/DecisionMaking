#include "AgentGOAP.h"
#include "ActionGOAP.h"

AgentGOAP::AgentGOAP(Grid* layer) : Agent(layer)
{        
}

Vector2D AgentGOAP::GetMazeElementPositionByGivenIndex(int mazeElementIndex)
{
    return (this->*_getMazeElementsPositionFunctions[mazeElementIndex])();
}