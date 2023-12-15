#include "WorldState.h"

void WorldState::SetWorldStates(std::map<std::string, bool> states)
{    
    _states = states;
}

bool WorldState::GetMapValueByKey(std::string key)
{
    return _states[key];
}
