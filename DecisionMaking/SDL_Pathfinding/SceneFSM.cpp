#include "SceneFSM.h"
#include "PathFollowing.h"

using namespace std;

#define ENEMY_AMOUNT 5

SceneFSM::SceneFSM()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png", "../res/gun.png");

	srand((unsigned int)time(NULL));

	Player *agent = new Player(maze);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20,-20));
	agent->setPathfinding(new AStarAlgorithm);
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D intialPlayerPosition(-1,-1);
	while (!maze->isValidCell(intialPlayerPosition))
		intialPlayerPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(intialPlayerPosition));

	Player* gun = new Player(maze);
	gun->setBehavior(new PathFollowing);
	gun->setTarget(Vector2D(-20, -20));
	gun->setPathfinding(new AStarAlgorithm);
	agents.push_back(gun);

	// set gun position coords to the center of a random cell
	Vector2D gunPosition(-1, -1);
	while (!maze->isValidCell(gunPosition))
		gunPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[1]->setPosition(maze->cell2pix(gunPosition));
	

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, intialPlayerPosition)<3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	for (int i = 0; i < ENEMY_AMOUNT; i++) {
		Enemy* enemy = new Enemy(maze, (Player*)agents[0]);
		enemy->loadSpriteTexture("../res/zombie1.png", 8);
		enemy->setBehavior(new PathFollowing);
		enemy->setPathfinding(new AStarAlgorithm);

		Vector2D enemyPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(enemyPosition)) || (Vector2D::Distance(enemyPosition, intialPlayerPosition) < 3))
			enemyPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		enemy->setPosition(maze->cell2pix(enemyPosition));

		enemies.push_back(enemy);
	}
}

SceneFSM::~SceneFSM()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);
	if (gun_texture)
		SDL_DestroyTexture(gun_texture);

	for (int i = 0; i < agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
}

void SceneFSM::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		if (event->key.keysym.scancode == SDL_SCANCODE_G) {
			Vector2D gunPosition(-1, -1);
			while (!maze->isValidCell(gunPosition))
				gunPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			agents[1]->setPosition(maze->cell2pix(gunPosition));
			((Player*)agents[0])->hasGun = false;
		}
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				agents[0]->clearPath();
				agents[0]->LoadPath(agents[0]->getPosition(), maze->cell2pix(cell), *maze);
			}
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}

	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition()))<3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}

	if ((agents[0]->getCurrentTargetIndex() == -1) && Vector2D::Distance(maze->pix2cell(agents[0]->getPosition()), maze->pix2cell(agents[1]->getPosition())) < 1)
	{
		((Player*)agents[0])->hasGun = true;
		agents[1]->setPosition(maze->cell2pix(Vector2D(-1,-1)));
	}
	
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(dtime, event);
	}
}

void SceneFSM::draw()
{
	drawMaze();
	drawCoin();
	drawGun();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}


	agents[0]->draw();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw();
	}
}

const char* SceneFSM::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SceneFSM::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{		
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			} else {
				// Do not draw if it is not necessary (bg is already black)
			}
					
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneFSM::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneFSM::drawGun()
{
	Vector2D gun_coords = agents[1]->getPosition();
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)gun_coords.x - offset, (int)gun_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), gun_texture, NULL, &dstrect);
}


bool SceneFSM::loadTextures(char* filename_bg, char* filename_coin, char* filename_gun)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_gun);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	gun_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}
