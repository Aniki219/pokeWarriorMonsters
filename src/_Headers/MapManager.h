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
	int mapLayers;

	static MapManager* instance;

	SDL_Rect getSrcRect(int index, std::string tilesetName);

public:
	static MapManager* Instance() {
		if (instance == 0) {
			instance = new MapManager();
		}
		return instance;
	}

	void createMapObjects();
	int getMapWidth();
	int getMapHeight();
	int getNumLayers();
	static int getIndex(int x, int y);
};