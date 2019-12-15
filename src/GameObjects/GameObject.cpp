#include "../_Headers/GameObjects/GameObject.h"
#include "../_Headers/Sprite.h"

GameObject::GameObject(std::string textureName, int xpos = 0, int ypos = 0, int width = 32, int height = 32) {
	position = new Vector((float)xpos, (float)ypos);
	velocity = new Vector(0, 0);
	size = new Vector((float)width, (float)height);

	if (textureName.c_str() != NULL) {
		sprite = new Sprite();
		sprite->setTexture(textureName);
	}
}

GameObject::~GameObject() {
	sprite->free();
}

void GameObject::draw() {
	SDL_Rect* clip = new SDL_Rect();
	clip->w = (int)size->x;
	clip->h = (int)size->y;

	sprite->render((int)position->x, (int)position->y, clip);
}

void GameObject::move() {
	*position += *velocity;
}

void GameObject::update() {
	move();
}

void GameObject::setSrcRect(SDL_Rect& srcRect) {
	SDL_Rect* newRect = new SDL_Rect();
	newRect->x = srcRect.x;
	newRect->y = srcRect.y;
	newRect->w = srcRect.w;
	newRect->h = srcRect.h;
	sprite->srcRect = newRect;
}

void GameObject::printPos() {
	std::cout << position->x << ", " << position->y << std::endl;
}

int GameObject::getX() {
	return position->x;
}

int GameObject::getY() {
	return position->y;
}

int GameObject::getCameraOffset() {
	return size->y - sprite->imageOffset->y;
}