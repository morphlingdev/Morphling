#include "Display.h"

/** The wondrous Display class.
  *
  * It handles /everything/ graphical.
  * You want to draw something onto the screen?
  * Call one of Display's methods and it handles everything. Fun!
**/

/*
 * Geometrical primitives and technical functions
 */

/* Makes any changes visible */
void Display::update()
{
    SDL_Flip(gScreen);
    return;
}

/* Changes a single pixel, located at (x, y), to (r, g, b) */
inline void Display::putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    *((Uint32*)gScreen->pixels+gScreen->w*y + x) = SDL_MapRGB(gScreen->format, r, g, b);
    return;
}

/* Draws a line from (x1,y1) to (x2,y2) using Bresenham's line algorithm */
void Display::draw_line(int x1, int y1, int x2, int y2, int r, int g, int b)
{
    int dx, dy, sx, sy, err;
    dx = std::abs(x2-x1);
    dy = std::abs(y2-y1);
    if(x1 < x2) sx = 1;
    else sx = -1;
    if(y1 < y2) sy = 1;
    else sy = -1;
    err = dx-dy;
    
    if(SDL_MUSTLOCK(gScreen)) SDL_LockSurface(gScreen);
    
    while(x1 != x2 or y1 != y2)
    {
        putpixel(x1, y1, r, g, b);
        int e2 = 2*err;
        if(e2 > -dy)
        {
            err = err - dy;
            x1 = x1 + sx;
        }
        if(e2 < dx)
        {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
    putpixel(x2, y2, r, g, b);
    
    if(SDL_MUSTLOCK(gScreen)) SDL_UnlockSurface(gScreen);
    
    return;
}

/* Fills a rectangle, top-left corner at (x, y), dimensions (w, h), colored (r, g, b) */
void Display::fill_rect(int x, int y, int w, int h, int r, int g, int b)
{
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;
    SDL_FillRect(gScreen, &dstrect, SDL_MapRGB(gScreen->format, r, g, b));
    return;
}

/* Draws, but not fills, the specified rectangle. */
void Display::draw_rect(int x, int y, int w, int h, int r, int g, int b)
{
    draw_line(x, y, x+w, y, r, g, b); // top
    draw_line(x, y+1, x, y+h, r, g, b); // left
    draw_line(x+w, y+1, x+w, y+h, r, g, b); // right
    draw_line(x+1, y+h, x+w-1, y+h, r, g, b); // bottom
    return;
}

/*
 * Text
 */

/* Draws a string on a single line */
void Display::draw_text_line(SDL_Rect *dst, std::string txt, FontType type, SDL_Color col)
{
    SDL_Surface *render = TTF_RenderText_Solid(font[type], txt.c_str(), col);
    SDL_BlitSurface(render, NULL, gScreen, dst);
    SDL_FreeSurface(render);
    return;
}
void Display::draw_text_line(int x, int y, std::string txt, FontType type, int r, int g, int b)
{
    SDL_Color col;
    SDL_Rect dst;

    col.r = r;
    col.g = g;
    col.b = b;
    dst.x = x;
    dst.y = y;

    draw_text_line(&dst, txt, type, col);
}

/* Draws text to fit inside a rectangle of width w and infinite height, with basic character wrapping */
int Display::draw_text_block(int x, int y, int w, std::string txt, FontType type, int r, int g, int b)
{
    int char_width, char_height, line_height, chars_per_line, pos, line_num, line_count;
    TTF_SizeText(font[type], "a", &char_width, NULL);
    line_height = TTF_FontLineSkip(font[type]);
    chars_per_line = w/char_width;
    
    line_count = 0;
    pos = 0;
    line_num = 0;
    while(pos < txt.length())
    {
        int find = txt.find('\n', pos)-pos;
        int width = std::min(find, chars_per_line);
        line_count++;
        pos += width;
        if(find < chars_per_line) pos++;
    }
    pos = 0;
    while(pos < txt.length())
    {
        int find = txt.find('\n', pos)-pos;
        int width = std::min(find, chars_per_line);
        draw_text_line(x, y-(line_count*line_height)+(line_num*line_height), txt.substr(pos, width), type, r, g, b);
        line_num++;
        pos += width;
        if(find < chars_per_line) pos++;
    }
    return line_num*line_height;
}

/*
 * Sprites
 */

/* Draw a sprite, top left corner of pixel location at (x, y) */
void Display::draw_sprite(int x, int y, Sprite s)
{
    SDL_Rect srcrect, dstrect;
    dstrect.x = x;
    dstrect.y = y;
    srcrect.x = s.state*24;
    srcrect.y = s.image*24;
    srcrect.w = 24;
    srcrect.h = 24;
    SDL_BlitSurface(spritesheet, &srcrect, gScreen, &dstrect);
}

/*
 * Tiles and Maps
 */

/* Draw a tile such that its upper-left pixel is at (x, y) */
void Display::draw_tile(int x, int y, Tile::TileImgId id)
{
    SDL_Rect srcrect, dstrect;
    dstrect.x = x;
    dstrect.y = y;
    srcrect.x = (id%10)*24;
    srcrect.y = id/10;
    srcrect.w = 24;
    srcrect.h = 24;
    SDL_BlitSurface(tilesheet, &srcrect, gScreen, &dstrect);
    return;
}

/* Draws a rectangle of tiles from a map */
void Display::draw_map(int x, int y, Map *m, int mx, int my, int mw, int mh)
{
    fill_rect(x, y, mw*24, mh*24, 0, 0, 0);
    for(int i=0; i<mw; i++)
    {
        if(mx+i < 0 or mx+i >= m->getWidth()) continue;
        for(int j=0; j<mh; j++)
        {
            if(my+j < 0 or my+j >= m->getHeight()) continue;
            draw_tile(x+i*24, y+j*24, m->tileAt(mx+i, my+j)->getAppearance());
        }
    }
    return;
}

/* Draws an entire map */
void Display::draw_map(int x, int y, Map *m)
{
    draw_map(x, y, m, 0, 0, m->getWidth(), m->getHeight());
    return;
}

/*
 * Initializer:
 * Initializes SDL and friends
 * Creates window
 * Loads images from files
 */
Display::Display(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
    SDL_WM_SetCaption("Morphling","Morphling");
    if (TTF_Init() == -1)
    {
        printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
        exit(2);
    }

    /* Get available fullscreen/hardware modes */
    SDL_Rect ** modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    /* Check is there are any modes available */
    if(modes == (SDL_Rect **)0)
    {
        exit(-1);
    }
    /* Check if or resolution is restricted */
    if(modes == (SDL_Rect **)-1)
    {
        exit(-2);
    }
    else
    {
        /* Do first mode */
        gScreen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
        //gScreen = SDL_SetVideoMode(0, 0, 32, SDL_SWSURFACE); //this sets fullscreen
    }


    // If we fail, return error.
    if (gScreen == NULL)
    {
        fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
        exit(-3);
    }

    // load resources
    tilesheet = IMG_Load("tiles.png");
    spritesheet = IMG_Load("sprites.png");
    font[FONT_SMALL] = TTF_OpenFont("DejaVuSansMono.ttf", 12);
    font[FONT_MEDIUM] = TTF_OpenFont("DejaVuSansMono.ttf", 18);
}
