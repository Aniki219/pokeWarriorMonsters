#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include<vector>

#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Wall.h"
#include "Camera.h"
#include "TextureManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Game {
	SDL_Renderer* renderer;
	SDL_Window* window;

	std::vector<GameObject*> gameObjects;
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
	GameObject* createGameObject(std::string typeName, std::string textureName, int xpos, int ypos, int width, int height);
	bool sortedByDepth = true;
	const int gridSize = 32;
	int frame = 0;

	bool init();
	bool isRunning();

	void handleEvents();
	void update();
	void render();
	void quit();

	void close();
};