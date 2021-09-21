#include <SDL.h>

#include <vector>

class Box
{	
	SDL_Surface* image = NULL;
	SDL_Rect rectangle;
public:

	Box(int w, int h, uint32_t color);
	void Draw(SDL_Surface* surface);
	void Update(int h);
};

class GroupBox
{
	std::vector<Box*> groups;
public:

	void add(Box *box);
	void update(SDL_Surface *surface, uint32_t color);
};