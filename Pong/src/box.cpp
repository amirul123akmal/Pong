#include <box.h>

// For the Players
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

void Box::Update(int h)
{
	rectangle.y -= h;
	rectangle.h -= h;
}

// Players grouping
void GroupBox::add(Box *box)
{
	groups.push_back(box);
}
void GroupBox::update(SDL_Surface* surface, uint32_t color)
{
	SDL_FillRect(surface, NULL, color);
	for (int i = 0 ; i < groups.size() ; i++)
	{
		groups[i]->Draw(surface);
	}
}