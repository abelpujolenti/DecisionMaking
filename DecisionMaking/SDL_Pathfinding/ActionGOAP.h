#pragma once
#include "GoalState.h"

enum class GoalState : char;

struct ActionGOAP
{
    int key;
    bool currentState;
    GoalState goalState;
};