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
		SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Wwidth, Wheight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		// Get Surface from window
		SDL_Surface* surface = SDL_GetWindowSurface(window);

		//  Event Tracking
		SDL_Event any_event;

		// Players
		uint32_t red = SDL_MapRGB(surface->format, 255, 0, 0);
		uint32_t blue = SDL_MapRGB(surface->format, 0, 0, 255);
		Box player1(10, 10, red);
		Box player2(400, 80, blue);

		player1.Draw(surface);
		player2.Draw(surface);

		// Mnadatory to update the surface that have been modified
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
			}
		}
	}

	void quitAll()
	{
		SDL_Quit();
	}
}