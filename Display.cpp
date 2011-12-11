#include "Display.h"

/* Changes a single pixel located at (x, y) to RGB values (r, g, b) */
void Display::putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if(SDL_MUSTLOCK(gScreen)) SDL_LockSurface(gScreen);
    *((Uint32*)gScreen->pixels+gScreen->w*y + x) = SDL_MapRGB(gScreen->format, r, g, b);
    if(SDL_MUSTLOCK(gScreen)) SDL_UnlockSurface(gScreen);
    return;
}

/* Updates graphical changes */
void Display::update()
{
    SDL_Flip(gScreen);
    return;
}

/* Draw tile such that its upper-left pixel is at (x, y) */
void Display::draw_tile(int x, int y, TileID id)
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

/* Initialize graphics */
Display::Display(int width, int height)
{
    // Initialize SDL's subsystems... This code will eventually be moved to display
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    //SDL_WM_SetIcon(SDL_LoadBMP(LOCATION OF THE ICON BITMAP), NULL);
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


    // load tiles.png
    tilesheet = IMG_Load("tiles.png");
}
