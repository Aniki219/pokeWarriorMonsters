#pragma once
#include <string>
#include <map>
#include "../Vector.h"
#include "../Animation.h"

#include "SDL.h"

class Sprite;

class GameObject {
protected:
	Vector* position;
	Vector* velocity;
	Vector* size;
	Sprite* sprite;
	int moveSpeed = 2;
	bool solid = false;

	public:
		GameObject(std::string textureName, int xpos, int ypos, int width, int height);
		~GameObject();
		virtual void update();
		virtual void draw();
		virtual void move();
		void setSrcRect(SDL_Rect& srcRect);
		int getX();
		int getY();
		int getCameraOffset();
		void printPos();
		int drawDepth = 0;
};