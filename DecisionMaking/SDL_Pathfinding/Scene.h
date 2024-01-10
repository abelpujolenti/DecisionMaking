#pragma once
#include <iostream>
#include <SDL.h>

#include "WorldState.h"


class Scene
{
protected:
	std::unique_ptr<WorldState> _worldState;
	
public:
	Scene() = default;
	virtual ~Scene() = default;
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };
};




