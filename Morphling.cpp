#include "Morphling.h"

void Game::init()
{
    dsp.setup(1024, 768);
	// create 20x20 map
    M.setup(20, 20);
    
    // initialize it with a delicious generated map
    M.generate_perlin();
	
	// draw a map for ULTIMATE lulz
    dsp.draw_map(0, 0, &M);
    
    // update the stuff shown on screen
    dsp.update();
}

int Game::handle_event(SDL_Event &event){
    switch (event.type)
    {
      case SDL_QUIT:
        return 1;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_SPACE:
            M.setup(30, 30);
            M.generate_perlin();
            dsp.draw_map(0, 0, &M);
            dsp.update();
            break;
        }
        break;
      default:
        return 0;
    }
}

int main(int argc, char *argv[])
{
    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());
    
    // Initialize game engine
    Game G;
    G.init();

    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    bool loop = true;
    while(loop)
    {
        while (SDL_PollEvent(&event))
        {
            int status = G.handle_event(event);
            if(status == 1) loop = false;
        }
        SDL_Delay(1000/30);
    }
    return 0;
}
