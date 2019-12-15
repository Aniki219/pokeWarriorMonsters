#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall(std::string img, int xpos, int ypos, int width, int height);
};