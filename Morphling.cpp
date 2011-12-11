#include "Morphling.h"

int main(int argc, char *argv[])
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
        gScreen = SDL_SetVideoMode(TOTALWIDTH,TOTALHEIGHT, 32, SDL_SWSURFACE);
    }


    // currently is #defined width and height, a simple change (see below) and a fullscreen toggle will allow the screen to be custom sized. may cause bugs, until ready use #defs.
    //gScreen = SDL_SetVideoMode(0, 0, 32, SDL_SWSURFACE);

    // If we fail, return error.
    if (gScreen == NULL)
    {
        fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
        exit(-3);
    }

    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());

    // clear screen just in case
    SDL_FillRect(gScreen,NULL,0x000000);


    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    bool loop = true;
    while(loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    loop = false;
                default:
                    continue;
            }
        }
    }
    return 0;
}
