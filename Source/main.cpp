#include <iostream>

#include "WindowManager.hpp"
#include "GameManager.hpp"

int main( int argc, char* args[] )
{
	bool shouldQuit = false;
	GameManager gameManager = GameManager();
	WindowManager::Instance().init();
	WindowManager::Instance().setName("Egress");
	WindowManager::Instance().open();

	while(!gameManager.shouldQuit())
	{
		WindowManager::Instance().clear();
		WindowManager::Instance().present();
		gameManager.handleEvents();
	}

	WindowManager::Instance().close();

	return 0;
}