#include "_Headers/Game.h"
#include "_Headers/InputHandler.h"



Game* Game::instance = 0;

GameObject* createGameObjectType(const std::string typeName, std::string textureName, int xpos, int ypos, int width, int height) {

	if (typeName == "Player") { return new Player(xpos, ypos); }
	if (typeName == "Tile") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Wall") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Door") { return new Wall(textureName, xpos, ypos, width, height); }
	if (typeName == "Sign") { return new Wall(textureName, xpos, ypos, width, height); }

	return 0;
}

GameObject* Game::createGameObject(std::string typeName, std::string textureName, int xpos, int ypos, int width, int height) {
	GameObject* gameObject = createGameObjectType(typeName, textureName, xpos, ypos, width, height);
	gameObjects.push_back(gameObject);
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
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

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
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	TextureManager::Instance()->init();

	GameObject* player = new Player(320, 192);
	gameObjects.push_back(player);
	camera = new Camera(0, 0);
	camera->setTarget(player);

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
	if (!sortedByDepth) { sortByDepth(); }
	for (GameObject* g : gameObjects) {
		g->draw();
	}
	
	//Update screen
	SDL_RenderPresent(renderer);
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
	while (!sortedByDepth) {
		sortedByDepth = true;
		for (int i = 0; i < gameObjects.size() - 1; i++) {
			if (gameObjects[i]->drawDepth > gameObjects[i + 1]->drawDepth) {
				GameObject* temp = gameObjects[i];
				gameObjects[i] = gameObjects[i + 1];
				gameObjects[i + 1] = temp;
				sortedByDepth = false;
			}
		}
	}

}