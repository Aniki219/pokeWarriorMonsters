#include "../_Headers/GameObjects/Player.h"
#include "../_Headers/InputHandler.h"
#include "../_Headers/Game.h"
#include "../_Headers/Animation.h"
#include "../_Headers/Sprite.h"

Player::Player(float xpos = 0, float ypos = 0) : GameObject("trainer", xpos, ypos, 32, 40) {
	sprite->createAnimation("up", 0, 4);
	sprite->createAnimation("down", 1, 4);
	sprite->createAnimation("right", 2, 4);
	sprite->createAnimation("left", 3, 4);
	sprite->setAnimation("down");
	sprite->imageOffset = new Vector(0, -8);

	drawDepth = 10;
}

void Player::move() {

	if ((int)position->x % Game::Instance()->gridSize == 0 && (int)position->y % Game::Instance()->gridSize == 0) {
		velocity->x = 0;
		velocity->y = 0;

		if ((InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) ||
			(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) ||
			(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) ||
			(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))) {
			stepTimer++;
		} else {
			stepTimer = 0;
		}

		if (stepTimer > 6) {
			moveSpeed = 2;
		}
		else {
			moveSpeed = 0;
		}

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
			velocity->x += moveSpeed;
			sprite->setAnimation("right");
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
			velocity->x -= moveSpeed;
			sprite->setAnimation("left");
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
			velocity->y -= moveSpeed;
			sprite->setAnimation("up");
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
			velocity->y += moveSpeed;
			sprite->setAnimation("down");
		}
		

		if (velocity->y != 0) { velocity->x = 0; }
		if (velocity->magnitude() > 0) {
			sprite->animSpeed = 10;
		}
		else {
			sprite->animSpeed = 0;
			sprite->animFrame += sprite->animFrame % 2;
		}
		
	}
	GameObject::move();
}