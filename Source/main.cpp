#include "WindowManager.hpp"
#include "GameManager.hpp"
#include "FrameRateLimiter.hpp"

#define MAX_FRAME_RATE 30.0

int main( int argc, char* args[] )
{
	long elapsedTime;
	WindowManager& window = WindowManager::Instance();
	GameManager* game;
	FrameRateLimiter limiter = FrameRateLimiter(MAX_FRAME_RATE);

	//Init
	window.init();
	window.setName("Egress");
	window.open();

	game = new GameManager();

	//Check Quit
	while(!game->shouldQuit())
	{
		//Render
		window.clear();
		game->render();
		window.present();

		//Handle Events
		game->handleEvents();

		//Update
		game->update(elapsedTime);
		game->resolveCollisions();

		//Limit Frame Rate
		elapsedTime = limiter.wait();
	}

	//Cleanup
	delete game;
	window.close();

	return 0;
}