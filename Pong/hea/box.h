#pragma warning(disable :4244)
#pragma warning(disable :4091)

#include "SDL.h"
#include "SDL_ttf.h"

#include "Extension.h"

#include <time.h>
#include <string>
#include <vector>

#define ScreenWidth 1920
#define ScreenHeight 1080
constexpr int BallSpeed = 1;

class Box
{	
protected:
	SDL_Surface* image = NULL;
	SDL_Rect rectangle;
	void check();
public:

	Box(int x, int y,int w, int h,  uint32_t color);
	void Draw(SDL_Surface* surface);
	void Update(int h);
	Extension give();
};
class GroupBox
{
	std::vector<Box*> groups;
	SDL_Surface* bgTemp = NULL;
	SDL_Surface* screen = NULL;
	uint32_t background;
	int choose = 0;
	uint32_t defaultBG;
	std::string filePath;
	void chooseSetting();
public:
	void add(Box *box);
	void update(SDL_Surface*);
	std::vector<Extension> CoordY();
	void getBGSetting(int, SDL_Surface*, const char filename[]);
	void bgUpdate(SDL_Surface*, uint32_t);
};
class Ball : public Box
{
	int direction = 0;
	int oldDirection = 0;
	Extension initialPosition{};
	int deltaX = 0, deltaY = 0;
	int left = 0;
	int right = 0;
	void LRDecision();
	int random();
	void reset();
public:
	Ball(int x, int y, int w, int h, uint32_t color) : Box(x, y, w, h, color){
		initialPosition.x = x;
		initialPosition.y = y;
		initialPosition.w = w;
		initialPosition.h = h;
	};
	void Init(const char filename[]);
	void update(const std::vector<Extension>& temp, double &timeDelta);
	Extension result();
};
class Text
{
	SDL_Surface* image = NULL;
	SDL_Rect coords;
	TTF_Font *font = NULL;
	SDL_Color color = { 0, 0, 0 };
public:
	Text(const char filename[], int x, int y, int w, int h, int size);
	void update(Extension result, SDL_Surface* ScreenOrigin);
	void normal(std::string sentence, SDL_Surface* surface);
};
class mainMenu
{
	int x = ScreenWidth / 2 - 300;
	int ye = ScreenHeight / 2 - 250;
	int ys = ScreenHeight / 2 + 100;
	SDL_Surface* escape = NULL;
	SDL_Surface* spaces = NULL;
	SDL_Rect esc;
	SDL_Rect spc;
public:
	mainMenu(const char escapefilename[], const char spacefilename[]);
	void update(SDL_Surface* surface);
};