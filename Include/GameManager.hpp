#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SDL2/SDL.h>

#include "EventManager.hpp"
#include "Layer.hpp"
#include "Floor.hpp"
#include "Wall.hpp"
#include "Person.hpp"
#include "Camera.hpp"

class GameManager : ISDLEventHandler, IKeyboardEventHandler
{
	bool quit;
	EventManager eventManager;

	Layer gameLayer;
	std::vector<Wall*> walls;
	Person* player;
	Camera* camera;

public:
	GameManager();
	~GameManager();

	void resolveCollisions();
	void handleEvents();
	void handleSDLEvent(SDL_Event event);
	void handleKeyboardEvents(const Uint8*);
	bool shouldQuit();

	void update(int frameTime);
	void render();
};

#endif