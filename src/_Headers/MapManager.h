#pragma once
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_Image.h"

class MapManager {
	MapManager();
	~MapManager();

	int mapHeight;
	int mapWidth;

	static MapManager* instance;

	SDL_Rect getSrcRect(int index);

public:
	static MapManager* Instance() {
		if (instance == 0) {
			instance = new MapManager();
		}
		return instance;
	}

	void createMapObjects();
};