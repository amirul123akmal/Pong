#include <box.h>

Box::Box(int x, int y, uint32_t color)
{
	image = SDL_CreateRGBSurface(0, 50, 200, 32, 0, 0, 0, 0);
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = x + 50;
	rectangle.h = y + 200;
	SDL_FillRect(image, NULL, color);
}

void Box::Draw(SDL_Surface* surface)
{
	SDL_BlitSurface(image, NULL, surface, &rectangle);
}