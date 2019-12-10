#include "Game.h"
#include <iostream>
#include <thread>
using namespace std;
Game::Game() : 
	m_running(false),
	m_spriteY{ 0 },
	m_spriteX{ 32 },
	m_pressed{ 4 }
{
	m_player = new Dot(false);
	m_otherPlayer = new Dot(true);
}
Game::~Game()
{
}
bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(m_p_Renderer, 0, 255, 255, 255);
			}
			else
			{
				DEBUG_MSG("Renderer init fail");
				return false;
			}
			m_player->Init(m_p_Renderer);
			m_otherPlayer->Init(m_p_Renderer);
		}
		else
		{
			DEBUG_MSG("Window init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	m_running = true;

	return true;
}
void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");
	m_p_Surface = SDL_LoadBMP("assets/sprite.bmp");
	m_p_Texture = SDL_CreateTextureFromSurface(m_p_Renderer, m_p_Surface);
	SDL_FreeSurface(m_p_Surface);

	if(SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Source.w, &m_Destination.h)==0)
	{
		m_Destination.x = m_Source.x = 0;
		m_Destination.y = m_Source.y = 0;
		m_Destination.w = m_Source.w;
		m_Destination.h = m_Source.h;
	}
	else
	{
		DEBUG_MSG("Texture Query Failed");
		m_running = false;
	}
}
void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);

	if(m_p_Renderer != nullptr && m_p_Texture != nullptr)
		SDL_RenderCopy(m_p_Renderer, m_p_Texture, &m_srcrect, &m_dstrect);
	m_player->render(m_p_Renderer);
	m_otherPlayer->render(m_p_Renderer);
	SDL_RenderPresent(m_p_Renderer);
}
void Game::Update()
{
	m_ticks = SDL_GetTicks();
	m_sprite = (m_ticks / 100) % 3;
	m_player->move(600, 800);
	m_srcrect = { m_sprite * m_spriteX, m_spriteY, SPRITE_SIZE, SPRITE_SIZE };
	m_dstrect = { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	switch (m_pressed)
	{
	case 0:
		m_spriteY = SPRITE_SIZE;
		m_spriteX = SPRITE_SIZE;
		break;
	case 1:
		m_spriteY = SPRITE_SIZE * 2;
		m_spriteX = SPRITE_SIZE;
		break;
	case 2:
		m_spriteY = SPRITE_SIZE * 3;
		m_spriteX = SPRITE_SIZE;
		break;
	case 3:
		m_spriteY = 0;
		m_spriteX = SPRITE_SIZE;
		break;
	case 4:
		m_spriteX = 0;
		break;
	default:
		break;
	}
}
void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	m_player->handleEvent(event);
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{
	DEBUG_MSG("Unloading Content");
	// delete(m_p_Texture);
	// m_p_Texture = NULL;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}
