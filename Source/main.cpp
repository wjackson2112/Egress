#include "WindowManager.hpp"
#include "GameManager.hpp"
#include "FrameRateLimiter.hpp"

#define MAX_FRAME_RATE 30.0

int main( int argc, char* args[] )
{
	long elapsedTime;

	WindowManager& window = WindowManager::Instance();
	GameManager game = GameManager();
	FrameRateLimiter limiter = FrameRateLimiter(MAX_FRAME_RATE);

	//Init
	window.init();
	window.setName("Egress");
	window.open();

	//Check Quit
	while(!game.shouldQuit())
	{
		//Handle Events
		game.handleEvents();

		//Update
		game.update(elapsedTime);

		//Render
		window.clear();
		game.render();
		window.present();

		//Limit Frame Rate
		elapsedTime = limiter.wait();
	}

	//Cleanup
	window.close();

	return 0;
}