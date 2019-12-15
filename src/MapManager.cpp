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

MapManager* MapManager::instance = 0;

using namespace rapidjson;
using namespace std;


void MapManager::createMapObjects() {

	// 1. Parse a JSON string into DOM.
	std::string line, text;
	std::ifstream in("assets/maps/map1.json");
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
	int tilesetsLength = tilesets.GetArray().Size();
	int firstgid = tilesets.GetArray()[tilesetsLength - 1]["firstgid"].GetInt();

	//Process layers
	Value& layers = data["layers"];
	for (int j = 0; j < layers.GetArray().Size(); j++) {

		//Handle the tile layers
		if (layers[j].HasMember("data")) {
			Value& spriteIndices = layers[j]["data"];

			for (int i = 0; i < spriteIndices.GetArray().Size(); i++) {
				int spriteIndex = spriteIndices[i].GetInt() - 1;
				if (spriteIndex == -1) { continue; }
				GameObject* tile = Game::Instance()->createGameObject("Tile", "tileset", 32 * (i%mapWidth), floor(i / mapWidth) * 32, 32, 32);
				SDL_Rect srcRect = getSrcRect(spriteIndex);
				tile->setSrcRect(srcRect);
			}
		}

		//Next we'll handle each tileObject
		if (layers[j].HasMember("objects")) {
			std::string typeName = layers[j]["name"].GetString();
			Value& objects = layers[j]["objects"];
			for (int i = 0; i < objects.GetArray().Size(); i++) {
				int gid = objects[i]["gid"].GetInt();
				int x = objects[i]["x"].GetInt();
				int y = objects[i]["y"].GetInt();
				int w = objects[i]["width"].GetInt();
				int h = objects[i]["height"].GetInt();
				std::string textureName = "tile" + std::to_string(gid - firstgid);
				GameObject* tile = Game::Instance()->createGameObject(typeName, textureName, x, y-h, w, h);
				//SDL_Rect srcRect = getSrcRect(spriteIndex);
				//tile->setSrcRect(srcRect);
			}
		}
	}

	
}

SDL_Rect MapManager::getSrcRect(int index) {
	SDL_Rect srcRect = {
		(index % 30) * Game::Instance()->gridSize,
		floor(index / 30) * Game::Instance()->gridSize,
		32,
		32
	};
	return srcRect;
}

MapManager::MapManager() {
}

MapManager::~MapManager() {

}