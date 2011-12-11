#ifndef DISPLAY_H
#define DISPLAY_H

#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif

class Display{
	SDL_Surface *gScreen;
	public:
	void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void update();
	Display(int width, int height);
};

#endif
