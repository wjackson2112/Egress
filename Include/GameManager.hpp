#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SDL2/SDL.h>

#include "EventManager.hpp"
#include "Layer.hpp"

class GameManager : ISDLEventHandler
{
	bool quit;
	EventManager eventManager;

	Layer gameLayer;

public:
	GameManager();
	~GameManager();

	void handleEvents();
	void handleSDLEvent(SDL_Event event);
	bool shouldQuit();

	void update(int frameTime);
	void render();
};

#endif