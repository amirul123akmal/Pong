#include <iostream>
#include <SDL.h>

#include <box.h>
#include <pong.h>

#define FPS 30
#define DeltaMove 3

namespace pong
{
	void limitFPS(uint8_t time)
	{
		if ((1000 / FPS) > SDL_GetTicks() - time)
		{
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - time));
		}
	}
	void initialization()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			std::cout << "Main SDL initialization Error\nError Code :" << SDL_GetError() << std::endl;
		if(TTF_Init() < 0)
			std::cout << "TTF SDL Initialization Error\nError Code: " << TTF_GetError() << std::endl;
	}
	void mainLoop()
	{
		int Wwidth = MonitorWitdh * .9;
		int Wheight = MonitorHeight * .9;

		// Window Creation
		SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Wwidth, Wheight, SDL_WINDOW_FULLSCREEN_DESKTOP);

		// Limiting FPS
		uint8_t Ticks;

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

		Box player1(10, height1, 30, 200, red);
		Box player2( MonitorWitdh - 40 ,height2, 30, 200, blue);

		// Centralized the players
		GroupBox Grouping;
		Grouping.add(&player1);
		Grouping.add(&player2);

		// Ball 
		Ball smallBall(( ScreenWidth / 2 ) - 25 , ( ScreenHeight / 2 ) -25, 32, 32, red);
		smallBall.Init("res/Image.bmp");

		Grouping.add(&smallBall);

		// For the background 
		uint32_t background = SDL_MapRGB(surface->format, 255, 255, 255);
		SDL_FillRect(surface, NULL, background);

		// Mandatory to update the surface that have been modified
		SDL_UpdateWindowSurface(window);

		// Main Loop toggle variable
		bool enable_loop = true;
		SDL_ShowCursor(SDL_DISABLE);
		while (enable_loop)
		{
			Ticks = SDL_GetTicks();
			while (SDL_PollEvent(&any_event))
			{
				if (any_event.type == SDL_QUIT)
				{
					enable_loop = false;
				}
			}
			keyPressed = SDL_GetKeyboardState(NULL);

			// Process keyboard event
			if (keyPressed[SDL_SCANCODE_ESCAPE])
			{
				enable_loop = false;
			}
			if (keyPressed[SDL_SCANCODE_UP])
			{
				player2.Update(DeltaMove);
			}
			if (keyPressed[SDL_SCANCODE_DOWN])
			{
				player2.Update(-DeltaMove);
			}
			if (keyPressed[SDL_SCANCODE_W])
			{
				player1.Update(DeltaMove);
			}
			if (keyPressed[SDL_SCANCODE_S])
			{
				player1.Update(-DeltaMove);
			}

			Grouping.update(surface, background);
			smallBall.update();
			SDL_UpdateWindowSurface(window);
			limitFPS(Ticks);
		}
	}
	void quitAll()
	{
		SDL_Quit();
	}
}