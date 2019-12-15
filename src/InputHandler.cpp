#include "_Headers/InputHandler.h"
#include "_Headers/Game.h"
#include <iostream>

InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler() {
	for (int i = 0; i < 3; i++) {
		mouseButtonStates.push_back(false);
	}
	mousePosition = new Vector(0, 0);
	keystates = SDL_GetKeyboardState(NULL);
}

InputHandler::~InputHandler() {
	delete mousePosition;
	delete keystates;

	mouseButtonStates.clear();
}

bool InputHandler::getMouseButtonState(int buttonNumber) {
	return mouseButtonStates[buttonNumber];
}

Vector* InputHandler::getMousePosition() {
	return mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
	if (keystates != 0) {
		if (keystates[key] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		keystates = SDL_GetKeyboardState(0);

		switch (event.type)
		{
		case SDL_QUIT:
			Game::Instance()->quit();
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}
	}
}

void InputHandler::onKeyDown() {
	keystates = SDL_GetKeyboardState(NULL);
}

void InputHandler::onKeyUp() {
	keystates = SDL_GetKeyboardState(NULL);
}

void InputHandler::onMouseMove(SDL_Event &event) {
	mousePosition->x = (float)event.motion.x;
	mousePosition->y = (float)event.motion.y;
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::clean()
{

}

void InputHandler::reset()
{
	mouseButtonStates[LEFT] = false;
	mouseButtonStates[MIDDLE] = false;
	mouseButtonStates[RIGHT] = false;
}