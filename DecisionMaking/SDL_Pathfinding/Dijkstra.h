#pragma once
#include <vector>
#include "WorldStateNode.h"
#include "Grid.h"
#include "SDL_SimpleApp.h"
#include "ActionGOAP.h"


class Dijkstra
{
public:
	WorldState initState;

	std::vector<std::string> keys;
	std::vector<int> keyRooms;

	Dijkstra(WorldState s, std::vector<std::string> k, std::vector<int> rooms);
	~Dijkstra();

	std::vector<ActionGOAP> Calculate();

private:
	std::vector<WorldStateNode*> frontier;
	std::vector<WorldStateNode*> visited;

	bool validState(WorldStateNode* w);
	bool isInVisited(WorldState w);
	bool isInFrontier(WorldState w);
	bool ableToGetInRoom(int r, WorldState w);

	int bestNode();
};
