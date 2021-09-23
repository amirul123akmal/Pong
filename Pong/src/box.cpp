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
	int temp = random();
	if (temp < 75)
	{
		direction = 1;
	}
	if ( temp >= 75 && temp < 50)
	{
		direction = 2;
	}
	if (temp >= 50 && temp < 25)
	{
		direction = 3;
	}
	if (temp >= 25)
	{
		direction = 4;
	}

}
void Ball::update(const std::vector<Extension> &temp, double &timeDelta)
{
	// Start Moving 
	if (deltaX == 0 && deltaY == 0)
	{
		if (direction == 1)
		{
			// top right
			deltaX = BallSpeed;
			deltaY = BallSpeed;
		}
		if (direction == 2)
		{
			// top left
			deltaX = -BallSpeed;
			deltaY = BallSpeed;
		}
		if (direction == 3)
		{
			// bottom left
			deltaX = -BallSpeed;
			deltaY = -BallSpeed;
		}
		if (direction == 4)
		{
			// bottom right
			deltaX = -BallSpeed;
			deltaY = BallSpeed;
		}
	}
	// the continous moving updation
	rectangle.y += (deltaY * timeDelta);
	rectangle.x += (deltaX * timeDelta);
	rectangle.w += (deltaX * timeDelta);
	rectangle.h += (deltaY * timeDelta);

	// Check for players collision
	if (rectangle.x < 57 && (rectangle.y > temp[0].y - 45 && rectangle.y < temp[0].y + 205 ))
	{
		deltaX = BallSpeed;
	}
	if (rectangle.x > ( ScreenWidth - 55 - 10 - 45 ) && (rectangle.y > temp[1].y - 45 && rectangle.y < temp[1].y + 205))
	{
		deltaX = -BallSpeed;
	}

	// Check for Screen Border
	if (rectangle.x < 5)
	{
		right++;
		reset();
	}
	if (rectangle.x > ScreenWidth - 45)
	{
		left++;
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
Extension Ball::result()
{
	Extension resultness;
	resultness.x = right;
	resultness.y = left;
	return resultness;
}

// Text
Text::Text(const char filename[])
{
	coords.x = ScreenWidth / 2 - 75;
	coords.y = 0;
	coords.w = 200;
	coords.h = 50;
 	font = TTF_OpenFont("open-sans/OpenSans-Bold.ttf", 100);
}
void Text::update(Extension result, SDL_Surface* ScreenOrigin)
{
	std::string character = std::to_string(result.y) + " : " + std::to_string(result.x);
	image = TTF_RenderText_Solid(font, character.c_str(), color);
	SDL_BlitSurface(image, NULL, ScreenOrigin, &coords);
}