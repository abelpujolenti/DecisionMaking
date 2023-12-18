#pragma once
#include "PFSM.h"
#include <map>
#include <iostream>

class EnemyPFSM :
    public PFSM
{
private:
    std::map<std::string, PointerState> states;
public:
    EnemyPFSM(PointerState defaultState);
    void AddState(std::string name, PointerState newState);
    void SetStateByName(std::string name);
};

