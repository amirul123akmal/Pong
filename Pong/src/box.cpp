#include <box.h>

// For the Players
Box::Box(int x, int y, int w, int h, uint32_t color)
{
	image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	SDL_FillRect(image, NULL, color);
}
void Box::Draw(SDL_Surface* surface)
{
	try
	{
		SDL_BlitSurface(image, NULL, surface, &rectangle);
	}
	catch (const std::exception&)
	{
		SDL_Quit();
	}
}
void Box::check()
{
	if (rectangle.y >= ScreenHeight - 210)
	{
		rectangle.y = ScreenHeight - 210;
		rectangle.h = ScreenHeight - 210;
	}
	if (rectangle.y <= 2)
	{
		rectangle.y = 2;
		rectangle.h = 2;
	}
}
void Box::Update(int h)
{
	rectangle.y -= h;
	rectangle.h -= h;
	check();
}
Extension Box::give() {
	Extension temp;
	temp.y = rectangle.y;
	temp.h = rectangle.h;
	return temp;
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
std::vector<Extension> GroupBox::CoordY() {
	std::vector<Extension> temp;
	temp.push_back(groups[0]->give());
	temp.push_back(groups[1]->give());
	return temp;
}


// Ball 
int Ball::random()
{
	srand(time(0));
	return (rand() % 100);;
}
void Ball::Init(const char filename[])
{
	moving = random();
	image = SDL_LoadBMP(filename);
	if (image != NULL)
	{
		LRDecision();
		printf("Image loaded successfully\n");
	}
	else
	{
		printf("Image failed to load to the memory\n");
	}
}
void Ball::LRDecision()
{
	if (moving % 2 == 0)
	{
		decision = true;
	}
}
void Ball::update(const std::vector<Extension> &temp)
{
	// Start Moving 
	if (deltaX == 0 && deltaY == 0)
	{
		if (decision)
		{
			deltaX = BallSpeed;
			deltaY = BallSpeed;
		}
		else
		{
			deltaX = -BallSpeed;
			deltaY = -BallSpeed;
		}
	}

	// the continous moving updation
	rectangle.x += deltaX;
	rectangle.y += deltaY;
	rectangle.w += deltaX;
	rectangle.h += deltaY;

	// Check for players collision
	if (rectangle.x < 32 && (rectangle.y > temp[0].y && rectangle.h < temp[0].h))
	{
		deltaX = BallSpeed;
	}
	if (rectangle.x > ScreenWidth - 40 - 50 && (rectangle.y > temp[1].y && rectangle.h < temp[1].h))
	{
		deltaX = -BallSpeed;
	}

	// Check for Screen Border
	if (rectangle.x < 5)
	{
		deltaX = BallSpeed;
	}
	if (rectangle.x > ScreenWidth - 45)
	{
		deltaX = -BallSpeed;
	}
	if (rectangle.y < 5)
	{
		deltaY = BallSpeed;
	}
	if (rectangle.y > ScreenHeight - 45)
	{
		deltaY = -BallSpeed;
	}
}