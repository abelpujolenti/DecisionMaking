#include "AStar.h"

AStar::AStar(Grid* g, Vector2D c, Vector2D p)
{
	maze = g;
	coin = c;
	initPos = p;
}

AStar::~AStar()
{
	delete maze;
}

std::vector<Vector2D> AStar::CalculatePath()
{
	bool reachedCoin = false;

	Node* best = new Node(nullptr, initPos);
	best->costSF = 0;
	frontier.push_back(best);


	while (!reachedCoin)
	{
		int index = bestNode();
		best = frontier[bestNode()];
		frontier.erase(frontier.begin() + index);

		if (maze->pix2cell(best->pos) == coin)
		{
			reachedCoin = true;
			break;
		}

		//UP
		Node* nextNode = new Node(best, Vector2D(best->pos.x, best->pos.y - CELL_SIZE));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		//DOWN
		nextNode = new Node(best, Vector2D(best->pos.x, best->pos.y + CELL_SIZE));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		//LEFT
		nextNode = new Node(best, Vector2D(best->pos.x - CELL_SIZE, best->pos.y));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		//RIGHT
		nextNode = new Node(best, Vector2D(best->pos.x + CELL_SIZE, best->pos.y));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		visited.push_back(best);
	}

	std::vector<Vector2D> finalPath;

	bool reachedFirstNode = false;

	Node* actualNode = best;

	while (!reachedFirstNode)
	{
		finalPath.insert(finalPath.begin(), actualNode->pos);

		if (actualNode->cameFrom == nullptr)
			reachedFirstNode = true;
		else
			actualNode = actualNode->cameFrom;
	}

	return finalPath;
}

bool AStar::validPathNode(Node* n)
{
	if (!isInVisited(n->pos) && !isInFrontier(n->pos) && maze->isValidCell(maze->pix2cell(n->pos)))
		return true;

	return false;
}

bool AStar::isInVisited(Vector2D v)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i]->pos == v)
			return true;
	}

	return false;
}

bool AStar::isInFrontier(Vector2D v)
{
	for (int i = 0; i < frontier.size(); i++)
	{
		if (frontier[i]->pos == v)
			return true;
	}

	return false;
}

int AStar::bestNode()
{
	int index = 0;
	int dist = distanceToGoal(frontier[0]->pos) + frontier[0]->costSF;

	for (int i = 0; i < frontier.size(); i++)
	{
		if (distanceToGoal(frontier[i]->pos) + frontier[i]->costSF < dist)
		{
			index = i;
			dist = distanceToGoal(frontier[i]->pos) + +frontier[i]->costSF;
		}
	}

	return index;
}

int AStar::distanceToGoal(Vector2D pos)
{
	Vector2D p = maze->pix2cell(pos);

	int x = coin.x - p.x;
	int y = coin.y - p.y;

	if (x < 0)
		x = -x;

	if (y < 0)
		y = -y;

	return x + y;
}