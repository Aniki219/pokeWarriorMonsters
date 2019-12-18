#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>

#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Wall.h"
#include "Camera.h"
#include "TextureManager.h"
#include "MapManager.h"

const int SCREEN_WIDTH = 32*21;
const int SCREEN_HEIGHT = 32*15;
const int GRIDSIZE = 32;
const int TILESIZE = 32;

class Game {
	SDL_Renderer* renderer;
	SDL_Window* window;

	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> toRender;

	std::map<std::pair<int, int>, GameObject*> tileObjectMap;

	void sortByDepth();

	int currentFrame;
	bool running;

	Game() { running = false; };
	~Game() {};

	static Game* instance;

public:
	static Game* Instance() {
		if (instance == 0) {
			instance = new Game();
			return instance;
		}
		return instance;
	}
	SDL_Renderer* getRenderer() {
		return renderer;
	}
	SDL_Window* getWindow() {
		return window;
	}
	Camera* camera;
	GameObject* createGameObject(std::string typeName, std::string textureName, int xpos, int ypos, int width, int height, int layer);
	bool sortedByDepth = true;
	int frame = 0;

	bool init();
	bool isRunning();

	void handleEvents();
	void update();
	void setRenderObjects();
	void render();
	void quit();

	void close();
};