#ifndef DISPLAY_H
#define DISPLAY_H


/*#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif*/
#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif

class Display{
	SDL_Surface *screen;
	public:
	void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	Display(int width, int height);
};

#endif
