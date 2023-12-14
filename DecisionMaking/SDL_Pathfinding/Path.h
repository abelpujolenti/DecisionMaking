#pragma once
#include <vector>

struct Vector2D;

struct Path
{
	std::vector<Vector2D> points;
	static const int ARRIVAL_DISTANCE = 35;
};
