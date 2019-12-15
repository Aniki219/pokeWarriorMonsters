#pragma once

#include "SDL.h"
#include <vector>
#include "Vector.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler {
	InputHandler();
	~InputHandler();

	static InputHandler* instance;

	std::vector<bool> mouseButtonStates;
	Vector* mousePosition;

	const Uint8* keystates;

	void onKeyUp();
	void onKeyDown();

	void onMouseMove(SDL_Event &event);
	void onMouseButtonDown(SDL_Event &event);
	void onMouseButtonUp(SDL_Event &event);

public:
	static InputHandler* Instance() {
		if (instance == 0) {
			instance = new InputHandler();
		}
		return instance;
	}

	bool getMouseButtonState(int buttonNumber);
	Vector* getMousePosition();
	bool isKeyDown(SDL_Scancode key);

	void reset();

	void update();
	void clean();
};