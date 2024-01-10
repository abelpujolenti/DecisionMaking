#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Grid.h"
#include "Enemy.h"
#include "AStarAlgorithm.h"

class Agent;

class SceneFSM : public Scene
{
private:
	std::vector<Agent*> agents;
	std::vector<Agent*> enemies;
	Vector2D coinPosition;
	Grid *maze;
	bool draw_grid;
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	SDL_Texture *gun_texture;

	void drawGun();
	void drawMaze();
	void drawCoin();
	bool loadTextures(char* filename_bg, char* filename_coin, char* filename_gun);
	
public:
	SceneFSM();
	~SceneFSM();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
};
