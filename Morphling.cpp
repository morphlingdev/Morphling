#include "Morphling.h"

int main(int argc, char *argv[])
{
    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());

    Display dsp(TOTALWIDTH, TOTALHEIGHT);
	
	// create map with perlin noise (in the map initializer)
    Map M(20, 20);
	
    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());

    // draw red pixel for the lulz
    dsp.putpixel(100, 100, 255, 0, 0);

    // draw a bunch of tiles for further lulz
	// TODO: Make these use enum values instead of hardcoded integers
    dsp.draw_tile(0, 0, 1);
    dsp.draw_tile(24, 0, 1);
    dsp.update();
	
	// draw a map for ULTIMATE lulz
    dsp.draw_map(101, 101, &M);
    dsp.update();

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
