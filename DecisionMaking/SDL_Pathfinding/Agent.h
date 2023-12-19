#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "utils.h"
#include "Vector2D.h"
#include "Grid.h"
#include "PathFindingAlgorithm.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
protected:
	PathFindingAlgorithm* pathfinding;
	SteeringBehavior* steeringBehaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	// Pathfinding
	Path* path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	bool draw_path;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	Grid* layer;

public:
	Agent(Grid* layer);
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setPathfinding(PathFindingAlgorithm *p);
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int LoadPath(Vector2D start, Vector2D end, const Grid& layer) const;
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	virtual void update(float dtime, SDL_Event *event);
	virtual void draw();
	bool loadSpriteTexture(char* filename, int num_frames=1);
	
};
