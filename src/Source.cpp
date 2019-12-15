/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "_Headers/Game.h"
#include "_Headers/MapManager.h"

//Adding FPS
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;

	//Start up SDL and create window
	if (Game::Instance()->init())
	{
		MapManager::Instance()->createMapObjects();
		//While application is running
		while (Game::Instance()->isRunning())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}

		Game::Instance()->close();
	}
	return 0;
}