#ifndef DISPLAY_H
#define DISPLAY_H

/* Display.h

Contains the Display class, which creates the window and handles graphical drawing.

General argument order for Display items:
target position
target size
source (image, text, etc.)
source attributes (e.g. for text):
    size
    color

source position (for cropping)
source size (for cropping)
*/

#include <string>

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
#include "Tile.h"

class Display
{
    SDL_Surface *gScreen;
    SDL_Surface *tilesheet;

public:

    // initializer, destructor
    Display(){};
    Display(int width, int height);

    // accssors
    SDL_Surface* get_screen() {return gScreen;};

    // methods
    void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void draw_tile(int x, int y, Tile::TileImgId id);
    void draw_map(int x, int y, Map *m);
    void draw_map(int x, int y, Map *m, int mx, int my, int mw, int mh);
    // Moved this functionality into MessageLog class
    // void draw_text(int x, int y, std::string txt, int r, int g, int b);
    void update();
};

#endif
