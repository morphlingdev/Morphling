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

#include "Map.h"

class Display
{
    SDL_Surface *gScreen;
    SDL_Surface *tilesheet;
public:
    enum TileImgId
    {
        TILE_GRASS, TILE_LAVA, TILE_WATER, TILE_SAND, TILE_MOUNTAIN
    };

    // initializer, destructor
    Display(){};
    Display(int width, int height);

    // methods
    void setup(int width, int height);
    void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void draw_tile(int x, int y, int id);
    void draw_map(int x, int y, Map *m);
    void update();
};

#endif
