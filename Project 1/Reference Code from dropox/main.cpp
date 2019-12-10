#include <iostream>
#include <thread>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Client.h"

int main(int argc, char** argv) {
	Client myClient("149.153.106.153", 1111); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return -1;
	}
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


