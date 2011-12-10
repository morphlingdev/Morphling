#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

class Display{
	SDL_Surface *screen;
	public:
	void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	Display(int width, int height);
};
