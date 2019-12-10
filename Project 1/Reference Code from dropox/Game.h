#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include "Dot.h"
#include <SDL.h>
static const int SPRITE_SIZE = 32;
class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void LoadContent();
	void UnloadContent();
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
private:
	Dot* m_player;
	Dot* m_otherPlayer;

	int m_spriteX;
	int m_spriteY;
	int m_pressed;
	Uint32 m_ticks;
	int m_sprite;
	SDL_Rect m_srcrect;
	SDL_Rect m_dstrect;
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Texture* m_p_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;
};
#endif
