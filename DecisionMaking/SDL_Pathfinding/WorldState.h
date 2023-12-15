#pragma once
#include <map>
#include <cvt/wstring>

class WorldState
{
private:
    std::map<std::string, bool> _states;
    
public:
    //~WorldState()
    //WorldState(WorldState&&) moveConstructor
    //WorldState& operator= (WorldState&&) moveAssignment
    //WorldState(const WorldState&) copyConstructor
    //WorldState& operator= (const WorldState&) copyAssignment
    
    void SetWorldStates(std::map<std::string, bool> states);
    bool GetMapValueByKey(std::string key);
};
