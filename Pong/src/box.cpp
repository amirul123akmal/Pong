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
void GroupBox::update(SDL_Surface* surface)
{
	bgUpdate(surface, defaultBG);
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
void GroupBox::chooseSetting()
{
	if (choose == 1) {
		background = SDL_MapRGB(bgTemp->format, 255, 255, 255);
	}
	if (choose  == 2)
	{
		screen = SDL_LoadBMP(filePath.c_str());
	}
}
void GroupBox::getBGSetting(int choosing, SDL_Surface* surface, const char filename[])
{
	filePath = filename;
	choose = choosing;
	bgTemp = surface;
	defaultBG = SDL_MapRGB(bgTemp->format, 255, 255, 255);
	chooseSetting();
}
void GroupBox::bgUpdate(SDL_Surface* surface, uint32_t color)
{
	if (choose == 1)
	{
		SDL_FillRect(surface, NULL, color);
	}
	if (choose == 2)
	{
		SDL_BlitSurface(screen, NULL, surface, NULL);
	}

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
	if (temp > 75)
	{
		direction = 1;
	}
	if ( temp <= 75 && temp > 50)
	{
		direction = 2;
	}
	if (temp <= 50 && temp > 25)
	{
		direction = 3;
	}
	if (temp <= 25)
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
Text::Text(const char filename[], int x, int y, int w = 0, int h = 0, int size = 100)
{
	coords.x = x;
	coords.y = y;
	coords.w = w;
	coords.h = h;
 	font = TTF_OpenFont(filename, size);
}
void Text::update(Extension result, SDL_Surface* ScreenOrigin)
{
	std::string character = std::to_string(result.y) + " : " + std::to_string(result.x);
	image = TTF_RenderText_Solid(font, character.c_str(), color);
	SDL_BlitSurface(image, NULL, ScreenOrigin, &coords);
}
void Text::normal(std::string sentence, SDL_Surface * surface)
{
	image = TTF_RenderText_Solid(font, sentence.c_str(), color);
	SDL_BlitSurface(image, NULL, surface, &coords);
}
 
// Main menu
mainMenu::mainMenu(const char escapefilename[], const char spacefilename[])
{
	
	spc.x = esc.x = x;
	esc.y = ye;
	spc.y = ys;
	escape = SDL_LoadBMP(escapefilename);
	spaces = SDL_LoadBMP(spacefilename);
}
void mainMenu::update(SDL_Surface* surface)
{
	Text ESCText("open-sans/OpenSans-Bold.ttf", x + 320, ye + 25, 0, 0, 65);
	Text SPCText("open-sans/OpenSans-Bold.ttf", x + 320, ys , 0, 0, 65);
	Text PauseText("open-sans/OpenSans-Bold.ttf", x + 750, ye +700, 0, 0, 65);
	SDL_BlitSurface(escape, NULL, surface, &esc);
	SDL_BlitSurface(spaces, NULL, surface, &spc);
	ESCText.normal("For Exit", surface);
	SPCText.normal("For Start", surface);
	PauseText.normal("P For Pause", surface);
}