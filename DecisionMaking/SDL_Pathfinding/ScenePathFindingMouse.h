#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Grid.h"

class Agent;

class ScenePathFindingMouse : public Scene
{
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Grid *maze;
	bool draw_grid;
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;

		
	void drawMaze();
	void drawCoin();
	bool loadTextures(char* filename_bg, char* filename_coin);
	
public:
	ScenePathFindingMouse();
	~ScenePathFindingMouse();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
};
