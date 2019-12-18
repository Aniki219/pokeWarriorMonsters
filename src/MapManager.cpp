#include "_Headers/MapManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "_Headers/Game.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "SDL.h"
#include "SDL_Image.h"

MapManager* MapManager::instance = 0;

using namespace rapidjson;
using namespace std;


void MapManager::createMapObjects() {

	// 1. Parse a JSON string into DOM.
	std::string line, text;
	std::ifstream in("assets/maps/snowyMountains.json");
	while (std::getline(in, line))
	{
		text += line + "\n";
	}
	const char* json = text.c_str();

	Document data;
	data.Parse(json);

	mapHeight = data["height"].GetInt();
	mapWidth = data["width"].GetInt();
	Value& tilesets = data["tilesets"];
	const int tilesetsLength = tilesets.GetArray().Size();
	const int firstgid = tilesets.GetArray()[tilesetsLength - 1]["firstgid"].GetInt();

	//Process layers
	Value& layers = data["layers"];
	mapLayers = layers.Size();
	for (int j = 0; j < layers.GetArray().Size(); j++) {

		//Handle the tile layers
		if (layers[j].HasMember("data")) {
			Value& spriteIndices = layers[j]["data"];

			for (int i = 0; i < spriteIndices.GetArray().Size(); i++) {
				const int spriteIndex = spriteIndices[i].GetInt() - 1;
				if (spriteIndex == -1) { continue; }
				GameObject* tile = Game::Instance()->createGameObject("Tile", "tileset", GRIDSIZE * (i%mapWidth), floor(i / mapWidth) * GRIDSIZE, GRIDSIZE, GRIDSIZE, j);
				SDL_Rect srcRect = getSrcRect(spriteIndex, "tileset");
				tile->setSrcRect(srcRect);
			}
		}

		//Next we'll handle each tileObject
		if (layers[j].HasMember("objects")) {
			std::string typeName = layers[j]["name"].GetString();
			Value& objects = layers[j]["objects"];
			for (int i = 0; i < objects.GetArray().Size(); i++) {
				const int gid = objects[i]["gid"].GetInt();
				const int x = objects[i]["x"].GetInt();
				const int y = objects[i]["y"].GetInt();
				const int w = objects[i]["width"].GetInt();
				const int h = objects[i]["height"].GetInt();
				std::string textureName = "tile" + std::to_string(gid - firstgid);

				GameObject* tile = Game::Instance()->createGameObject(typeName, textureName, x, y-h, w, h, j);
				tile->drawDepth = y;
			}
		}
	}

	GameObject* player = Game::Instance()->createGameObject("Player", "trainer", 1600, 3712, GRIDSIZE, GRIDSIZE*1.25, layers.Size()-1);
	player->drawDepth = 10;
	
	Game::Instance()->camera = new Camera(0, 0);
	Game::Instance()->camera->setTarget(player);
}

SDL_Rect MapManager::getSrcRect(int index, std::string tilesetName) {
	int w;
	SDL_QueryTexture(TextureManager::Instance()->getTexture(tilesetName), NULL, NULL, &w, NULL);

	SDL_Rect srcRect = {
		(index % (w/32)) * 32,
		floor(index / (w/32)) * 32,
		32,
		32
	};

	return srcRect;
}

int MapManager::getMapHeight() {
	return mapHeight;
}

int MapManager::getMapWidth() {
	return mapWidth;
}

int MapManager::getNumLayers() {
	return mapLayers;
}

int MapManager::getIndex(int x, int y) {
	const int column = floor(x / GRIDSIZE);
	const int row = floor(y / GRIDSIZE);

	return row * Instance()->mapWidth + column;
}

MapManager::MapManager() {
}

MapManager::~MapManager() {

}