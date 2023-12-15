#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Grid.h"

#define PATH_MAZE_ROOMS_CSV "../res/maze_rooms.csv"
#define HAS_COIN "Has Coin"
#define HAS_RED_KEY "Has Red Key"
#define HAS_ORANGE_KEY "Has Orange Key"
#define HAS_YELLOW_KEY "Has Yellow Key"
#define HAS_GREEN_KEY "Has Green Key"
#define HAS_BLUE_KEY "Has Blue Key"
#define HAS_PURPLE_KEY "Has Purple Key"


struct ActionGOAP;
class AgentGOAP;

class SceneGOAP : public Scene
{
private:
	std::unique_ptr<AgentGOAP> _agentGoap;

	std::vector<std::unique_ptr<ActionGOAP>> _actionsGoap;
	
	std::unique_ptr<Vector2D> _coinPosition;
	std::unique_ptr<Vector2D[]> _keyPositions;
	Vector2D keyPositions[8];

	std::unique_ptr<Grid> _maze;

	bool draw_grid;

	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	SDL_Texture *keys_texture;
		
	void drawMaze();
	void drawCoin();
	bool loadTextures(char* filename_bg, char* filename_coin, char* filename_keys);
	void CreateActionsGOAP();
	void CreateWorldState() const;
	
public:
	SceneGOAP();
	~SceneGOAP();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
};
