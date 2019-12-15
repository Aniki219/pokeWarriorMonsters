#pragma once
#include "GameObject.h"

class Player : public GameObject {
	int stepTimer = 0;
public:
	Player(float xpos, float ypos);
	void move();
};