#include "GameManager.hpp"

GameManager::GameManager() : eventManager{EventManager(0)}, quit{false}
{
	gameLayer = Layer();
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

void GameManager::update(int frameTime)
{
	gameLayer.update(frameTime);
}

void GameManager::render()
{
	gameLayer.render(NULL);
}

bool GameManager::shouldQuit()
{
	return quit;
}