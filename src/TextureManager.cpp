#include "_Headers/TextureManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "rapidjson/document.h"

using namespace rapidjson;

TextureManager* TextureManager::instance = 0;

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
	for (auto const& t : textureList) {
		SDL_DestroyTexture(t.second);
	}

}

bool TextureManager::newTexture(std::string name, std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error loading surface %s! SDL_Error: %s", path.c_str(), SDL_GetError());
	}

	newTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), loadedSurface);

	SDL_FreeSurface(loadedSurface);

	textureList[name] = newTexture;

	return newTexture != NULL;
}

SDL_Texture* TextureManager::getTexture(std::string name) {
	return textureList[name];
}

void TextureManager::init() {
	newTexture("tileset", "assets/tileset.png");
	newTexture("trainer", "assets/trainer.png");

	// 1. Parse a JSON string into DOM.
	std::string line, text;
	std::ifstream in("assets/objectTiles/objectTiles.json");
	while (std::getline(in, line))
	{
		text += line + "\n";
	}
	const char* json = text.c_str();

	Document data;
	data.Parse(json);

	//For each type of tile in the tiles array
	//we want to create a texture using its image path
	//and we'll make the textureName tile+id
	//This way we can use the id in the map.json file
	//to get the name of the texture
	Value& tiles = data["tiles"];
	for (int i = 0; i < tiles.GetArray().Size(); i++) {
		Value& tile = tiles[i];
		int id = tile["id"].GetInt();
		std::string fakePathName = tile["image"].GetString();
		std::string pathName = "assets" + fakePathName.substr(2);
		newTexture("tile" + std::to_string(id), pathName);
	}
}
