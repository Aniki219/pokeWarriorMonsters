#include "_Headers/Camera.h"
#include "_Headers/Game.h"

Camera::Camera(int x, int y) {
	position = new Vector((float)x, (float)y);
}

void Camera::setTarget(GameObject* gameObject) {
	target = gameObject;
}

void Camera::follow() {
	if (target != nullptr) {
		position->x = target->getX() - SCREEN_WIDTH / 2;
		position->y = target->getY() - SCREEN_HEIGHT / 2 + target->getCameraOffset();
	}
}

int Camera::getX() {
	return position->x;
}

int Camera::getY() {
	return position->y;
}