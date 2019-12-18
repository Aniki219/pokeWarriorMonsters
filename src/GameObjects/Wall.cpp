#include "../_Headers/GameObjects/Wall.h"
#include "../_Headers/Game.h"

Wall::Wall(std::string textureName, int xpos, int ypos, int width = GRIDSIZE, int height = GRIDSIZE)
	: GameObject(textureName, xpos, ypos, width, height) 
{
	solid = true;
	drawDepth = 1;
}
