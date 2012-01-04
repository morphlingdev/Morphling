#include "Display.h"

/* Changes a single pixel located at (x, y) to RGB values (r, g, b) */
void Display::putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if(SDL_MUSTLOCK(gScreen)) SDL_LockSurface(gScreen);
    *((Uint32*)gScreen->pixels+gScreen->w*y + x) = SDL_MapRGB(gScreen->format, r, g, b);
    if(SDL_MUSTLOCK(gScreen)) SDL_UnlockSurface(gScreen);
    return;
}

/* Make graphical changes visible */
void Display::update()
{
    SDL_Flip(gScreen);
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

/* Draw tile such that its upper-left pixel is at (x, y) */
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

void Display::draw_map(int x, int y, Map *m)
{
    draw_map(x, y, m, 0, 0, m->getWidth(), m->getHeight());
    return;
}

void Display::draw_map(int x, int y, Map *m, int mx, int my, int mw, int mh)
{
    for(int i=0; i<mw; i++)
    {
        for(int j=0; j<mh; j++)
        {
            draw_tile(y+i*24, y+j*24, m->tileAt(mx+i, my+j)->getAppearance());
        }
    }
    return;
}

/* Text drawing */
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

/* draw a text block, top-left corner at (x, y) with width w, with REALLY basic character wrapping */
void Display::draw_text_block(int x, int y, int w, std::string txt, FontType type, int r, int g, int b)
{
    int char_width, line_height, chars_per_line, num_lines;
    TTF_SizeText(font[type], "a", &char_width, NULL);
    line_height = TTF_FontLineSkip(font[type]);
    chars_per_line = w/char_width;
    num_lines = txt.length()/chars_per_line + 1;
    for(int i=0; i<num_lines; i++)
    {
        draw_text_line(x, y+(i*line_height), txt.substr(i*chars_per_line, chars_per_line), type, r, g, b);
    }
}

/* Initialize graphics */
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
    font[FONT_SMALL] = TTF_OpenFont("DejaVuSansMono.ttf", 12);
    font[FONT_MEDIUM] = TTF_OpenFont("DejaVuSansMono.ttf", 18);
}
