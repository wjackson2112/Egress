#include "GameManager.hpp"

GameManager::GameManager() : eventManager{EventManager(0)}, quit{false}
{
	camera = new Camera();

	camera->setBoundary(Size(1120,500));
	camera->zoomTo(2);

	gameLayer = Layer();
	gameLayer.add(new Floor(0xB0, 0xB0, 0xA0, Size(1020,500)));

	//Camera Test Grid
	//Verticals
	// for(int i = 0; i <= 800; i += 20)
	// {
	// 	if(i % 100 == 0)
	// 	{
	// 		walls.push_back(new Wall(0xFF, 0, 0, Rect(Point(i, 0), Size(6, 500))));
	// 	}
	// 	else
	// 	{
	// 		walls.push_back(new Wall(0, 0, 0, Rect(Point(i, 0), Size(3, 500))));
	// 	}
	// }

	// //Horizontals
	// for(int i = 0; i <= 500; i += 20)
	// {
	// 	if(i % 100 == 0)
	// 	{
	// 		walls.push_back(new Wall(0x80, 0x80, 0xFF, Rect(Point(0, i), Size(800, 6))));
	// 	}
	// 	else
	// 	{
	// 		walls.push_back(new Wall(0, 0, 0, Rect(Point(0, i), Size(800, 3))));
	// 	}
	// }

	//Top Verticals
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(0,0), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(220,0), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(440,0), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(660,0), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(880,0), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(1100,0), Size(20, 200))));

	// //Top Horizontals
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(20,0), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(240,0), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(460,0), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(680,0), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(900,0), Size(200, 20))));

	// //Bottom Verticals
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(0,300), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(220,300), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(440,300), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(660,300), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(880,300), Size(20, 200))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(1100,300), Size(20, 200))));
	//Bottom Horizontals
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(20,480), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(240,480), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(460,480), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(680,480), Size(200, 20))));
	walls.push_back(new Wall(0x10, 0x10, 0x10, Rect(Point(900,480), Size(200, 20))));

	for(auto &wall : walls)
	{
		gameLayer.add(wall);
	}

	//Player
	player = new Person(0xD0, 0x00, 0x00, Point(100,100), eventManager);
	gameLayer.add(player);

	eventManager.registerSDLEventHandler(this);
}

GameManager::~GameManager()
{
	walls.clear();
	delete(camera);
	delete(player);
	eventManager.unregisterSDLEventHandler(this);
}

void GameManager::resolveCollisions()
{
	for(auto &wall : walls)
	{
		if(intersects(*wall->collider, *player->collider))
		{
			wall->collider->resolveCollision(*player->collider);
		}
	}
}

void GameManager::handleEvents()
{
	eventManager.handleSDLEvents();
	eventManager.handleKeyboardEvents();
}

void GameManager::handleSDLEvent(SDL_Event event)
{
	if(event.type == SDL_QUIT)
	{
		quit = true;
	}
}

void GameManager::handleKeyboardEvents(const Uint8* events)
{
	// player->handleKeyboardEvents(events);
}

void GameManager::update(int frameTime)
{
	gameLayer.update(frameTime);
}

void GameManager::render()
{
	camera->moveHandleTo(player->center());
	gameLayer.render(camera);
}

bool GameManager::shouldQuit()
{
	return quit;
}