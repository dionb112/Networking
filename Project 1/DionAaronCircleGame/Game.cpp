#include "Game.h"
#include <iostream>
#include <thread>
using namespace std;
Game::Game() : 
	m_running(false)
{
	m_player = new Dot(false);
	m_otherPlayer = new Dot(true);
	m_client = new Client("149.153.106.153", 1111, m_player); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
}
Game::~Game()
{
}
bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (!m_client->Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return -1;
	}
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
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
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
void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);
	m_player->render(m_p_Renderer);
	m_otherPlayer->render(m_p_Renderer);
	SDL_RenderPresent(m_p_Renderer);
}
void Game::Update()

{
	int x = numFromString(m_client->getOtherPos()).at(0);
	int y = numFromString(m_client->getOtherPos()).at(1);

	m_otherPlayer->SetPosition(x, y);
	if (m_player->Checkcollision(m_otherPlayer->GetCenterX(), m_otherPlayer->GetCenterY()))
	{
		m_totalTicks =  SDL_GetTicks();
		m_totalTicks -= m_gameTicks;
		if (m_player->getChaser())
		{
			std::cout << "Dion wins, Aaron survival time: " + std::to_string(m_totalTicks / 60 / 10) + " seconds" << std::endl;
			m_player->setChaser(false);
			m_otherPlayer->setChaser(true);
		}
		else
		{
			std::cout << "Aaron wins, Dion survival time: " + std::to_string(m_totalTicks / 60 / 10) + " seconds" << std::endl;
			m_player->setChaser(true);
			m_otherPlayer->setChaser(false);
		}
		m_player->Init(m_p_Renderer);
		m_otherPlayer->Init(m_p_Renderer);
		m_gameTicks = SDL_GetTicks();
	}
}
void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	m_player->handleEvent(event);
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_running = false;
		}
		else
		{
			m_player->move(600, 800);
			m_client->SendString(m_player->GetPosAsString());
		}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}
