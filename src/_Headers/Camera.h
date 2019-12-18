#pragma once
#include "Vector.h"
#include "GameObjects/GameObject.h"

class Camera {
private:
	Vector* lastPosition;
	Vector* position;
public:
	Camera(int x, int y);
	GameObject* target;

	void setTarget(GameObject* gameObject);
	void follow();
	int getX();
	int getY();
};