#pragma once
#include <vector>
#include "Node.h"
#include "Grid.h"
#include "SDL_SimpleApp.h"


class AStar
{
public:
	Vector2D coin;
	Vector2D initPos;

	Grid* maze;

	AStar(Grid* g, Vector2D c, Vector2D p);
	~AStar();

	std::vector<Vector2D> CalculatePath();


	std::vector<Vector2D> enemies;

private:
	std::vector<Node*> frontier;
	std::vector<Node*> visited;


	bool validPathNode(Node* n);
	bool isInVisited(Vector2D v);
	bool isInFrontier(Vector2D v);

	int bestNode();

	int distanceToGoal(Vector2D pos);
};