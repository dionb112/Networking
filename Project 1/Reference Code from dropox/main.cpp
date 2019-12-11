#include <iostream>
#include <thread>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

int main(int argc, char** argv) {
	DEBUG_MSG("Game Object Created");
	Game* game = new Game();

	DEBUG_MSG("Game Initialising");
	game->Initialize("SDL StarterKit",300,100,800,600, SDL_WINDOW_INPUT_FOCUS);
	
	DEBUG_MSG("Game Loop Starting......");
	while(game->IsRunning())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	DEBUG_MSG("Calling Cleanup");
	game->CleanUp();
	
	std::cin.get();
	return 0;
}


