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


    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());


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
