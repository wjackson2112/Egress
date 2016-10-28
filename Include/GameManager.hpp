#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SDL2/SDL.h>

#include "EventManager.hpp"

class GameManager : ISDLEventHandler
{
	bool quit;
	EventManager eventManager;

public:
	GameManager();
	~GameManager();

	void handleEvents();
	void handleSDLEvent(SDL_Event event);
	bool shouldQuit();
};

#endif