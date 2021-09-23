#pragma warning(disable :4244)
#pragma warning(disable :4091)

#include "SDL.h"
#include "SDL_ttf.h"

#include "Extension.h"

#include <time.h>
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
public:
	void add(Box *box);
	void update(SDL_Surface *surface, uint32_t color);
	std::vector<Extension> CoordY();
};
class Ball : public Box
{
	int direction = 0;
	Extension initialPosition{};
	int deltaX = 0, deltaY = 0;
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
};
class Text
{
	int left = 0;
	int right = 0;
public:

};