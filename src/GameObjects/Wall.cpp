#include "../_Headers/GameObjects/Wall.h"

Wall::Wall(std::string textureName, int xpos, int ypos, int width=32, int height=32)
	: GameObject(textureName, xpos, ypos, width, height) 
{
	solid = true;
	drawDepth = 1;
}
