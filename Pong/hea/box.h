#include <SDL.h>

class Box
{	
	SDL_Surface* image = NULL;
	SDL_Rect rectangle;
public:
	Box(int w, int h, uint32_t color);
	void Draw(SDL_Surface* surface);
};