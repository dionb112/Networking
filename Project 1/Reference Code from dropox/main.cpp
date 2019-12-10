#include <iostream>
#include <thread>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

int main(int argc, char** argv) {
	DEBUG_MSG("Game Object Created");
	Game* game = new Game();
	//Adjust screen positions as needed
	DEBUG_MSG("Game Initialising");
	game->Initialize("SDL StarterKit",300,100,800,600, SDL_WINDOW_INPUT_FOCUS);
	
	DEBUG_MSG("Loading Content");
	game->LoadContent();


	DEBUG_MSG("Game Loop Starting......");
	// std::string userinput; //holds the user's chat message
	while(game->IsRunning())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
		// std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
	}

	DEBUG_MSG("Calling Cleanup");
	game->CleanUp();
	game->UnloadContent();
	
	std::cin.get();
	return 0;
}


