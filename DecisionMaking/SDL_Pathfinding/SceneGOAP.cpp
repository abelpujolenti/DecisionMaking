#include "SceneGOAP.h"

#include "AgentGOAP.h"
#include "PathFollowing.h"
#include "ActionGOAP.h"
#include "GoalState.h"

using namespace std;

enum Color { White=0, Black, Red, Orange, Yellow, Green, Blue, Purple};
char *color_strings[8] = {"White", "Black", "Red", "Orange", "Yellow", "Green", "Blue", "Purple"};

SceneGOAP::SceneGOAP() :
	_coinPosition(std::make_unique<Vector2D>()),
	_keyPositions(std::make_unique<Vector2D[]>(8)),
	_maze(std::make_unique<Grid>(PATH_MAZE_ROOMS_CSV))
{
	_worldState = std::make_unique<WorldState>();

	CreateWorldState();
	
	draw_grid = false;

	loadTextures("../res/maze.png", "../res/coin.png", "../res/keys.png");

	srand((unsigned int)time(NULL));

	_agentGoap = std::make_unique<AgentGOAP>();
	_agentGoap->loadSpriteTexture("../res/soldier.png", 4);
	_agentGoap->setBehavior(new PathFollowing);
	_agentGoap->setTarget(Vector2D(-20,-20));

	// set agent position coords to the center of a random cell in the Black room
	Vector2D rand_cell;
	do
	{
		rand_cell = Vector2D((float)(rand() % _maze->getNumCellX()), (float)(rand() % _maze->getNumCellY()));		
	}
	while ((!_maze->isValidCell(rand_cell)) || (_maze->getCellValue(rand_cell) != Color::Black));
	_agentGoap->setPosition(_maze->cell2pix(rand_cell));

	// set the coin in a random cell (but not in the Black room)
	do
	{		
		*_coinPosition = Vector2D((float)(rand() % _maze->getNumCellX()), (float)(rand() % _maze->getNumCellY()));
	}
	while ((!_maze->isValidCell(*_coinPosition)) || (_maze->getCellValue(*_coinPosition) == Color::Black));

	// set keys in in a random cell (but not in the room of its same color)

	bool keyOnCenter = false;
	
	for (int i=Color::Red; i<8; i++)
	{
		/*do
		{
			do
			{
				_keyPositions[i] = Vector2D((float)(rand() % _maze->getNumCellX()), (float)(rand() % _maze->getNumCellY()));	
			}
			while (i == 7 && !keyOnCenter && _maze->getCellValue(_keyPositions[i]) != Black);			
		}
		while ((!_maze->isValidCell(_keyPositions[i])) || (_maze->getCellValue(_keyPositions[i]) == i));

		if (!keyOnCenter)
		{
			keyOnCenter = _maze->getCellValue(_keyPositions[i]) == Black;
		}*/
		do
		{
			do
			{
				keyPositions[i] = Vector2D((float)(rand() % _maze->getNumCellX()), (float)(rand() % _maze->getNumCellY()));	
			}
			while (i == 7 && !keyOnCenter && _maze->getCellValue(keyPositions[i]) != Color::Black);			
		}
		while ((!_maze->isValidCell(keyPositions[i])) || (_maze->getCellValue(keyPositions[i]) == i));

		if (!keyOnCenter)
		{
			keyOnCenter = _maze->getCellValue(keyPositions[i]) == Color::Black;
		}
	}
	
	CreateActionsGOAP();
	_agentGoap->SetKeyPositions(keyPositions);
	_agentGoap->SetCoinPosition(*_coinPosition);
}


void SceneGOAP::CreateActionsGOAP()
{
	_actionsGoap.reserve(9);

	for (int i = 0; i < 9; ++i)
	{
		_actionsGoap.emplace_back(std::make_unique<ActionGOAP>());
	}

	int cellColor = _maze->getCellValue(*_coinPosition);
	_actionsGoap[8]->goalState = GoalState::TRUE;

	while (cellColor != 1)
	{		
		_actionsGoap[cellColor]->goalState = GoalState::TRUE;
		//cellColor = _maze->getCellValue(_keyPositions[cellColor]);
		cellColor = _maze->getCellValue(keyPositions[cellColor]);
	}
}

void SceneGOAP::CreateWorldState() const
{	
	std::map<std::string, bool> states;

	states.emplace(HAS_COIN, false);
	states.emplace(HAS_RED_KEY, false);
	states.emplace(HAS_ORANGE_KEY, false);
	states.emplace(HAS_YELLOW_KEY, false);
	states.emplace(HAS_GREEN_KEY, false);
	states.emplace(HAS_BLUE_KEY, false);
	states.emplace(HAS_PURPLE_KEY, false);

	_worldState->SetWorldStates(states);
}

SceneGOAP::~SceneGOAP()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);
}

void SceneGOAP::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = _maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (_maze->isValidCell(cell)) {
				_agentGoap->addPathPoint(_maze->cell2pix(cell));
			}
		}
		break;
	default:
		break;
	}

	_agentGoap->update(dtime, event);

	// check if the agent has reached 
	if (_agentGoap->getCurrentTargetIndex() == -1)
	{
		// the agent has arrived to the coin we are done!
		if (_maze->pix2cell(_agentGoap->getPosition()) == *_coinPosition)
		{
			cout << "The Agent achieved its GOAL!." << endl;
			// nothing to do here but clear the coin position (set coinPosition to -1,-1)
			*_coinPosition = Vector2D(-1,-1);
		}
		for (int i=Color::Red; i<8; i++)
		{
			if (_maze->pix2cell(_agentGoap->getPosition()) == keyPositions[i])
			{
				cout << "Now the Agent has the " << color_strings[i] << " Key." << endl;
				// clear the key texture (set key position to -1,-1)
				keyPositions[i] = Vector2D(-1,-1);
			}
		}
	}
	
}

void SceneGOAP::draw()
{
	drawMaze();
	drawCoin();

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

	_agentGoap->draw();
}

const char* SceneGOAP::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SceneGOAP::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < _maze->getNumCellY(); j++)
	{
		for (int i = 0; i < _maze->getNumCellX(); i++)
		{		
			if (!_maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 255);
				coords = _maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			} else {
				int cell_color = _maze->getCellValue(Vector2D((float)i, (float)j));
				if (cell_color == Color::Black)
					continue; // Do not draw if it is not necessary (bg is already black)
				switch (cell_color)
				{
					case Color::Red:
						SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 23, 23, 89);
						break;
					case Color::Orange:
						SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 182, 20, 129);
						break;
					case Color::Yellow:
						SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 20, 129);
						break;
					case Color::Green:
						SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 82, 252, 20, 89);
						break;
					case Color::Blue:
						SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 20, 144, 252, 89);
						break;
					case Color::Purple:
						SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 214, 20, 252, 89);
						break;
				}
				coords = _maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_SetRenderDrawBlendMode(TheApp::Instance()->getRenderer(), SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
				SDL_SetRenderDrawBlendMode(TheApp::Instance()->getRenderer(), SDL_BLENDMODE_NONE);
				
			}
					
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneGOAP::drawCoin()
{
	int offset = CELL_SIZE / 2;

	if (_maze->isValidCell(*_coinPosition))
	{
		Vector2D coin_coords = _maze->cell2pix(*_coinPosition);
		SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}

	for (int i=Color::Red; i<8; i++)
	{
		if (!_maze->isValidCell(keyPositions[i])) continue;
		Vector2D key_coords = _maze->cell2pix(keyPositions[i]);
		SDL_Rect dstrect = {(int)key_coords.x-offset, (int)key_coords.y - offset, CELL_SIZE, CELL_SIZE};
		SDL_Rect srcrect = {i * 32, 0, 32, 32};
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), keys_texture, &srcrect, &dstrect);
	}
}


bool SceneGOAP::loadTextures(char* filename_bg, char* filename_coin, char* filename_keys)
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

	image = IMG_Load(filename_keys);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	keys_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);
	
	if (image)
		SDL_FreeSurface(image);


	return true;
}
