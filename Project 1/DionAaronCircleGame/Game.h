#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include "Dot.h"
#include <SDL.h>
#include "Client.h"
#include "NumFromString.cpp"

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
private:
	bool m_isSendCoords;

	Client* m_client;
	Dot* m_player;
	Dot* m_otherPlayer;

	Uint32 m_totalTicks;
	Uint32 m_gameTicks;

	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
};
#endif
