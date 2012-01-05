#ifndef DISPLAY_H
#define DISPLAY_H

/* Display.h

Contains the Display class, which creates the window and handles graphical drawing.

General argument order for Display items:
target position
target size
source (describes the actual image, text, etc.)
source attributes (e.g. text font, rectangle color)
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
    SDL_Surface *spritesheet;
    TTF_Font *font[2];

public:

    // initializer, destructor
    Display(int width, int height);

    // enums
    enum FontType
    {
        FONT_SMALL,
        FONT_MEDIUM,
    };

    // methods
    // primitives
    void update();
    void putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void fill_rect(int x, int y, int w, int h, int r, int g, int b);
    // text
    void draw_text_line(SDL_Rect *dst, std::string txt, FontType type, SDL_Color col);
    void draw_text_line(int x, int y, std::string txt, FontType type, int r, int g, int b);
    void draw_text_block(int x, int y, int w, std::string txt, FontType type, int r, int g, int b);
    // tile & map
    void draw_tile(int x, int y, Tile::TileImgId id);
    void draw_map(int x, int y, Map *m);
    void draw_map(int x, int y, Map *m, int mx, int my, int mw, int mh);
};

#endif
