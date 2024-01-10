#pragma once
#include "Vector2D.h"

class Node
{
public:
	Node* cameFrom;
	Vector2D pos;
	int heuristic;
	int costSF;

	Node();

	Node(Node* c, Vector2D p)
	{
		cameFrom = c;
		pos = p;
	}
};