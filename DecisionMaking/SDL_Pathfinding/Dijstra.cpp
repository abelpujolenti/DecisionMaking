#include "Dijkstra.h"

Dijkstra::Dijkstra(WorldState s, std::vector<std::string> k, std::vector<int> rooms)
{
	initState = s;
	keys = k;
	keyRooms = rooms;
}

Dijkstra::~Dijkstra()
{
	
}

std::vector<ActionGOAP> Dijkstra::Calculate()
{
	bool reachedCoin = false;

	WorldStateNode* best = new WorldStateNode(nullptr, initState);
	best->costSF = 0;
	frontier.push_back(best);

	
	while (!reachedCoin)
	{

		int index = bestNode();
		best = frontier[index];
		frontier.erase(frontier.begin()+index);

		if(best->state.GetMapValueByKey(keys[0]) == true)
		{
			reachedCoin = true;
			break;
		}

		for (int i = 0; i < 7; i++)
		{
			if (best->state.GetMapValueByKey(keys[i]) == false)
			{
				WorldState newState = best->state;
				newState.SetMapValueByKey(keys[i], true);
				WorldStateNode* nextNode = new WorldStateNode(best, newState);
				nextNode->costSF = best->costSF + 1;
				if (ableToGetInRoom(keyRooms[i], newState) && validState(nextNode))
					frontier.push_back(nextNode);
			}
		}

		visited.push_back(best);
	}

	std::vector<ActionGOAP> finalPath;

	bool reachedFirstNode = false;

	WorldStateNode* actualNode = best;

	while (!reachedFirstNode)
	{
		ActionGOAP newAction;
		newAction.currentState = true;
		newAction.goalState = GoalState::TRUE;
		
		for (int i = 0; i < 7; i++)
		{
			if (actualNode->state.GetMapValueByKey(keys[i]) !=
				actualNode->cameFrom->state.GetMapValueByKey(keys[i]))
			{
				newAction.key = i;

			}
		}
		 
		finalPath.insert(finalPath.begin(), newAction);

		actualNode = actualNode->cameFrom;

		if (actualNode->cameFrom == nullptr)
			reachedFirstNode = true;
	}

	return finalPath;
}

bool Dijkstra::validState(WorldStateNode* w)
{
	if (!isInVisited(w->state) && !isInFrontier(w->state))
		return true;

	return false;
}

bool Dijkstra::isInVisited(WorldState w)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i]->equalState(w, keys))
			return true;
	}

	return false;
}

bool Dijkstra::isInFrontier(WorldState w)
{
	for (int i = 0; i < frontier.size(); i++)
	{
		if (frontier[i]->equalState(w, keys))
			return true;
	}

	return false;
}

bool Dijkstra::ableToGetInRoom(int r, WorldState w)
{
	if (w.GetMapValueByKey(keys[r]) || r == 0)
		return true;

	return false;
}

int Dijkstra::bestNode()
{
	int index = 0;
	int cost = frontier[0]->costSF;

	for (int i = 0; i < frontier.size(); i++)
	{
		if(frontier[i]->costSF < cost)
		{
			index = i;
			cost = frontier[i]->costSF;
		}
	}

	return index;
}
