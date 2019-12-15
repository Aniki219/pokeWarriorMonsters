#pragma once
#include<map>
#include "Game.h"


class TextureManager {
	TextureManager();
	~TextureManager();

	static TextureManager* instance;

	std::map<std::string, SDL_Texture*> textureList;

public:
	static TextureManager* Instance() {
		if (instance == 0) {
			instance = new TextureManager();
		}
		return instance;
	}

	bool newTexture(std::string name, std::string path);
	SDL_Texture* getTexture(std::string name);
	void init();
};