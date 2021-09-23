#include <box.h>

// For the Playerss  
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
	}
	if (rectangle.y <= 2)
	{
		rectangle.y = 2;
	}
}
void Box::Update(int h)
{
	rectangle.y -= h;
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
	if (random() % 2 == 0)
	{
		decision = true;
	}
	else
	{
		decision = false;
	}
}
void Ball::update(const std::vector<Extension> &temp, double &timeDelta)
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
	rectangle.y += (deltaY * timeDelta);
	rectangle.x += (deltaX * timeDelta);
	rectangle.w += (deltaX * timeDelta);
	rectangle.h += (deltaY * timeDelta);

	// Check for players collision
	if (rectangle.x < 57 && (rectangle.y > temp[0].y && rectangle.y < temp[0].y + 200 ))
	{
		deltaX = BallSpeed;
	}
	if (rectangle.x > ( ScreenWidth - 55 - 10 - 45 ) && (rectangle.y > temp[1].y && rectangle.y < temp[1].y + 200))
	{
		deltaX = -BallSpeed;
	}

	// Check for Screen Border
	if (rectangle.x < 5)
	{
		reset();
	}
	if (rectangle.x > ScreenWidth - 45)
	{
		reset();
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
void Ball::reset()
{
	rectangle.x = initialPosition.x;
	rectangle.y = initialPosition.y;
	rectangle.w = initialPosition.w;	
	rectangle.h = initialPosition.h;
	deltaX = 0;
	deltaY = 0;
	LRDecision();
}