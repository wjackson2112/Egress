#include "GameManager.hpp"

GameManager::GameManager() : eventManager{EventManager(0)}, quit{false}
{
	eventManager.registerSDLEventHandler(this);
}

GameManager::~GameManager()
{
	eventManager.unregisterSDLEventHandler(this);
}

void GameManager::handleEvents()
{
	eventManager.handleSDLEvents();
}

void GameManager::handleSDLEvent(SDL_Event event)
{
	if(event.type == SDL_QUIT)
	{
		quit = true;
	}
}

bool GameManager::shouldQuit()
{
	return quit;
}