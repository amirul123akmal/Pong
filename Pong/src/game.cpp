#include <box.h>
#include <pong.h>

#include <iostream>

#include <SDL.h>

#define FPS 120
#define DeltaMove 1

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
		// Screen
		int Wwidth = MonitorWitdh * .9;
		int Wheight = MonitorHeight * .9;

		// Window Creation
		SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Wwidth, Wheight, SDL_WINDOW_FULLSCREEN_DESKTOP);

		// Get Surface from window
		SDL_Surface* surface = SDL_GetWindowSurface(window);

		// Height coord
		int height1 = (MonitorHeight / 2) - 100;
		int height2 = (MonitorHeight / 2) - 100;

		// Players
		uint32_t red = SDL_MapRGB(surface->format, 255, 0, 0);
		uint32_t blue = SDL_MapRGB(surface->format, 0, 0, 255);

		Box player1(25, height1, 30, 200, red);
		Box player2( MonitorWitdh - 55 ,height2, 30, 200, blue);

		// Centralized the players
		GroupBox Grouping;
		Grouping.add(&player1);
		Grouping.add(&player2);

		// Ball 
		Ball smallBall(( ScreenWidth / 2 ) - 25 , ( ScreenHeight / 2 ) -25, 32, 32, red);
		smallBall.Init("res/move/ball.bmp");
		Grouping.add(&smallBall);

		// For the background 
		uint32_t background = SDL_MapRGB(surface->format, 255, 255, 255);
		SDL_FillRect(surface, NULL, background);

		// Mandatory to update the surface that have been modified
		SDL_UpdateWindowSurface(window);

		// START OF THE MAIN LOOP SETTING
		//  Event Tracking
		SDL_Event any_event;
		const uint8_t* keyPressed;

		// Limiting FPS
		uint64_t Ticks = SDL_GetPerformanceCounter();
		uint64_t last;
		uint8_t time;
		double timeDelta = 0;

		// Text for marks
		Text marks("open-sans/OpenSans-Bold.ttf", ScreenWidth / 2 - 75, 0, 200, 50, 100);

		// Main Loop toggle variable
		bool enable_loop = true;
		SDL_ShowCursor(SDL_DISABLE);

		// Main menu setup
		bool enable_to_play = false;
		mainMenu start("res/mainMenu/escape.bmp", "res/mainMenu/space.bmp");

		Grouping.update(surface, background);
		smallBall.update(Grouping.CoordY(), timeDelta);
		marks.update(smallBall.result(), surface);
		start.update(surface);

		SDL_UpdateWindowSurface(window);

		// The main loop
		while (enable_loop)
		{
			last = Ticks;
			time = SDL_GetTicks();
			Ticks = SDL_GetPerformanceCounter();
			timeDelta = (double)((Ticks - last) * 1000 / SDL_GetPerformanceFrequency());

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
				player2.Update(DeltaMove * timeDelta);
			}
			if (keyPressed[SDL_SCANCODE_DOWN])
			{
				player2.Update(-DeltaMove * timeDelta);
			}
			if (keyPressed[SDL_SCANCODE_W])
			{
				player1.Update(DeltaMove * timeDelta);
			}
			if (keyPressed[SDL_SCANCODE_S])
			{
				player1.Update(-DeltaMove * timeDelta);
			}
			if (keyPressed[SDL_SCANCODE_SPACE])
			{
				enable_to_play = true;
			}
			if (enable_to_play)
			{
				Grouping.update(surface, background);
				smallBall.update(Grouping.CoordY(), timeDelta);
				marks.update(smallBall.result(), surface);
				SDL_UpdateWindowSurface(window);
			}
			
			limitFPS(time);
		}
	}
	void quitAll()
	{
		SDL_Quit();
	}
}