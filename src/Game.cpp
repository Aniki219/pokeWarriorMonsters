#include "_Headers/Game.h"
#include "_Headers/InputHandler.h"

Game* Game::instance = 0;

GameObject* createGameObjectType(const std::string typeName, std::string textureName, int xpos, int ypos, int width, int height) {

	if (typeName == "Player") { return new Player(xpos, ypos); }
	if (typeName == "Tile") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Wall") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Tree") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Door") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Sign") { return new Wall(textureName, xpos, ypos, width, height); }

	return new Wall(textureName, xpos, ypos, width, height);
}

GameObject* Game::createGameObject(std::string typeName, std::string textureName, int xpos, int ypos, int width, int height, int layer = 0) {
	GameObject* gameObject = createGameObjectType(typeName, textureName, xpos, ypos, width, height);
	if (typeName == "Player") {
		gameObjects.push_back(gameObject);
	}
	else {
		const int index = MapManager::getIndex(xpos, ypos);
		tileObjectMap[{ index, layer }] = gameObject;
	}

	sortedByDepth = false;
	return gameObject;
}

bool Game::init(){
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{

		//Create window
		window = SDL_CreateWindow("PokeWarriorMonsters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}

			else
			{
				running = true;
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				const int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	TextureManager::Instance()->init();

	return success;
}

bool Game::isRunning() {
	return running;
}

void Game::handleEvents() {
	//Event handler
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit();
		}
	}

	InputHandler::Instance()->update();
}

void Game::update() {
	frame++;
	for (GameObject* g : gameObjects) {
		g->update();
	}
	if (camera != nullptr) {
		camera->follow();
	}
}

void Game::render() {

	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
	SDL_RenderClear(renderer);

	//Render texture to screen
	sortByDepth();

	for (GameObject* g : toRender) {
		g->draw();
	}

	//Update screen
	SDL_RenderPresent(renderer);
}

void Game::setRenderObjects() {
	toRender.clear();

	const int renderMargin = 3;
	const int screenRows = SCREEN_HEIGHT / GRIDSIZE;
	const int screenCols = SCREEN_WIDTH / GRIDSIZE;
	const int numCols = MapManager::Instance()->getMapWidth();
	const int numRows = MapManager::Instance()->getMapHeight();
	const int startCol = std::fmax(0,(camera->getX() - renderMargin*GRIDSIZE) / GRIDSIZE);
	const int startRow = std::fmax(0,(camera->getY() - renderMargin*GRIDSIZE) / GRIDSIZE);
	
	for (int k = 0; k < MapManager::Instance()->getNumLayers(); k++) {
		for (int j = startRow; j < startRow + screenRows + renderMargin*2 && j < numRows; j++) {
			for (int i = startCol; i < startCol + screenCols + renderMargin*2 && i < numCols; i++) {
				const int index = MapManager::getIndex(i * GRIDSIZE, j * GRIDSIZE);

				if (tileObjectMap.count({ index, k }) > 0) {
					toRender.push_back(tileObjectMap[{index, k}]);
				}
			}
		}
	}
	for (GameObject* g : gameObjects) {
		if (g->getX() >= camera->getX() - g->getWidth() &&
			g->getY() >= camera->getY() - g->getHeight() &&
			g->getX() <= camera->getX() + SCREEN_WIDTH + g->getWidth() &&
			g->getY() <= camera->getY() + SCREEN_HEIGHT + g->getHeight()) {
			toRender.push_back(g);
		}
	}
	sortedByDepth = false; 
}

void Game::quit() {
	running = false;
}

void Game::close() {
	InputHandler::Instance()->clean();

	//Unload Sprites

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::sortByDepth() {

	while (!sortedByDepth && toRender.size() >= 2) {
		sortedByDepth = true;
		for (int i = 0; i < toRender.size() - 1; i++) {
			if (toRender[i]->drawDepth > toRender[i + 1]->drawDepth) {
				GameObject* temp = toRender[i];
				toRender[i] = toRender[i + 1];
				toRender[i + 1] = temp;
				sortedByDepth = false;
			}
		}
	}
}