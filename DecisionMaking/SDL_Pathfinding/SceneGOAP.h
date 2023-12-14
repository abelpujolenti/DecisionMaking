#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Grid.h"

class Agent;

class SceneGOAP : public Scene
{
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D keyPositions[8];
	Grid *maze;
	bool draw_grid;
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	SDL_Texture *keys_texture;
		
	void drawMaze();
	void drawCoin();
	bool loadTextures(char* filename_bg, char* filename_coin, char* filename_keys);
	
public:
	SceneGOAP();
	~SceneGOAP();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
};
