#include "Display.h"

/* Changes a single pixel located at (x, y) to RGB values (r, g, b) */
void Display::putpixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if(SDL_MUSTLOCK(gScreen)) SDL_LockSurface(gScreen);
    *((Uint32*)gScreen->pixels+gScreen->w*y + x) = SDL_MapRGB(gScreen->format, r, g, b);
    if(SDL_MUSTLOCK(gScreen)) SDL_UnlockSurface(gScreen);
    return;
}

/* Initiates graphics */
Display::Display(int width, int height)
{


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


    // clear screen just in case
    SDL_FillRect(gScreen,NULL,0x000000);
}
