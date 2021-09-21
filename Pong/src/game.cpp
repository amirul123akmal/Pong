#include <iostream>
#include <SDL.h>

#include <box.h>
#include <pong.h>

namespace pong
{
	void initialization()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			std::cout << SDL_GetError() << std::endl;
	}

	void mainLoop()
	{
		int Wwidth = MonitorWitdh * .9;
		int Wheight = MonitorHeight * .9;

		// Window Creation
		SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Wwidth, Wheight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

		// Get Surface from window
		SDL_Surface* surface = SDL_GetWindowSurface(window);

		//  Event Tracking
		SDL_Event any_event;
		const uint8_t* keyPressed;

		// Height coord
		int height1 = (MonitorHeight / 2) - 100;
		int height2 = (MonitorHeight / 2) - 100;

		// Players
		uint32_t red = SDL_MapRGB(surface->format, 255, 0, 0);
		uint32_t blue = SDL_MapRGB(surface->format, 0, 0, 255);

		Box player1(10                 , height1, red);
		Box player2(MonitorWitdh - 90  , height2, blue);

		// Centralized the players
		GroupBox Grouping;
		Grouping.add(&player1);
		Grouping.add(&player2);

		// For the background 
		uint32_t background = SDL_MapRGB(surface->format, 255, 255, 255);
		SDL_FillRect(surface, NULL, background);

		// Mandatory to update the surface that have been modified
		SDL_UpdateWindowSurface(window);

		// Main Loop toggle variable
		bool enable_loop = true;

		while (enable_loop)
		{
			while (SDL_PollEvent(&any_event))
			{
				if (any_event.type == SDL_QUIT)
				{
					enable_loop = false;
				}
				keyPressed = SDL_GetKeyboardState(NULL);

				if (keyPressed[SDL_SCANCODE_SPACE])
				{
					enable_loop = false;
				}
				if (keyPressed[SDL_SCANCODE_UP] )
				{
					player2.Update(20);
				}
				if (keyPressed[SDL_SCANCODE_DOWN])
				{
					player2.Update(-20);
				}
				if (keyPressed[SDL_SCANCODE_W])
				{
					player1.Update(20);
				}
				if (keyPressed[SDL_SCANCODE_S])
				{
					player1.Update(-20);
				}
			}
			Grouping.update(surface, background);
			SDL_UpdateWindowSurface(window);
		}
	}

	void quitAll()
	{
		SDL_Quit();
	}
}