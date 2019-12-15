#pragma once
#include "Vector.h"
#include "GameObjects/GameObject.h"

class Camera {
public:
	Camera(int x, int y);
	Vector* position;
	GameObject* target;

	void setTarget(GameObject* gameObject);
	void follow();
	int getX();
	int getY();
};