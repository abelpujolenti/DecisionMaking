#pragma once

enum class GoalState : char;

struct ActionGOAP
{
    bool currentState;
    GoalState goalState;
};