#pragma once
#include "Game.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	void free();
	void render(int x, int y, SDL_Rect* clip = NULL);
	void createAnimation(std::string animName, int rowNumber, int numberOfFrames, int startFrame = 0);
	void setAnimation(std::string animName);
	void setTexture(std::string name);
	int getWidth();
	int getHeight();
	std::string getCurrentAnimation();

	int animSpeed = 0;
	int animFrame = 0;
	Vector* imageOffset = new Vector(0, 0);
	SDL_Rect* srcRect;

private:
	SDL_Texture* mTexture;

	std::map<std::string, Animation*> animations;
	Animation* currentAnimation;

	int mWidth;
	int mHeight;
};
