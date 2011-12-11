#ifndef DISPLAY_H
#define DISPLAY_H

#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#endif

enum TileID{
  TILE_GRASS, TILE_LAVA
};

class Display{
	SDL_Surface *gScreen;
	SDL_Surface *tilesheet;
	public:
	void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	void draw_tile(int x, int y, TileID id);
	void update();
	Display(int width, int height);
};

#endif
