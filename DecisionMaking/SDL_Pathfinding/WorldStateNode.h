#pragma once
#include "WorldState.h"

class WorldStateNode
{
public:
	WorldStateNode* cameFrom;
	WorldState state;
	int costSF;

	WorldStateNode();

	WorldStateNode(WorldStateNode* c, WorldState s)
	{
		cameFrom = c;
		state = s;
		costSF = 0;
	}

	bool equalState(WorldState w, std::vector<std::string> k)
	{
		for (int i = 0; i < 6; i++)
		{
			if (w.GetMapValueByKey(k[i]) != state.GetMapValueByKey(k[i]))
			{
				return false;
			}
		}
		return true;
	}
};