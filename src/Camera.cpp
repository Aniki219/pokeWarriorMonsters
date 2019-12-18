#include "_Headers/Camera.h"
#include "_Headers/Game.h"

Camera::Camera(int x, int y) {
	position = new Vector((float)x, (float)y);
	lastPosition = new Vector((float)x - 1, (float)y);
}

void Camera::setTarget(GameObject* gameObject) {
	target = gameObject;
}

void Camera::follow() {
	if (target != nullptr) {
		position->x = target->getX() - (SCREEN_WIDTH - GRIDSIZE) / 2;
		position->y = target->getY() - (SCREEN_HEIGHT - GRIDSIZE) / 2;// +target->getCameraOffset()->y;

		//We update the objects that need to be rendered only when the camera moves to a new row or column
		if ((int)position->x % GRIDSIZE == 0 && (int)position->y % GRIDSIZE == 0 &&
			(position->x != lastPosition->x || position->y != lastPosition->y)) {
			lastPosition->x = getX();
			lastPosition->y = getY();
			Game::Instance()->setRenderObjects();
		}
	}
}

int Camera::getX() {
	return position->x;
}

int Camera::getY() {
	return position->y;
}