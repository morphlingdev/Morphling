#include "Morphling.h"

Game::Game() : dsp(1024, 768),out("log.txt")
{
    out << "Welcome to Morphling.\n";
    
    // currently we default to in-game
    state = GS_GAME;

    // Set up player -- SHOULD BE WRITTEN IN DATA FILE LATER INSTEAD OF HARDCODED
    //               -- SHOULD ALSO BE PUT INTO 
    P.maxHitpoints() = 100;
    P.hitpoints() = 100;
    P_x = 20;
    P_y = 20;
    P_sprite = Display::SPRITE_PLAYERARROW;
    P_spritestate = Display::SPRITE_STATE_FACING_SOUTH;

	// create 100x100 map
    M.setup(100, 100);
    // initialize it with a delicious generated map
    M.generate_perlin();

    redraw();
}

int Game::handle_event(SDL_Event &event)
{
    switch (state)
    {
        case GS_GAME:
            switch (event.type)
            {
              case SDL_QUIT:
                state = GS_QUIT;
              case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                  case SDLK_UP:
                    P_y -= 1;
                    P_spritestate = Display::SPRITE_STATE_FACING_NORTH;
                    break;
                  case SDLK_RIGHT:
                    P_x += 1;
                    P_spritestate = Display::SPRITE_STATE_FACING_EAST;
                    break;
                  case SDLK_DOWN:
                    P_y += 1;
                    P_spritestate = Display::SPRITE_STATE_FACING_SOUTH;
                    break;
                  case SDLK_LEFT:
                    P_x -= 1;
                    P_spritestate = Display::SPRITE_STATE_FACING_WEST;
                    break;
                  case SDLK_SPACE:
                    // regenerate map
                    M.setup(100, 100);
                    M.generate_perlin();
                    out << "Talking talk\n";
                    break;
                }
                redraw();
                break;
              default:
                return 0;
            }
            break;
        case GS_QUIT:
            SDL_Quit();
            exit(0);
        default:
            exit(9001);
    }
}

void Game::redraw()
{
    dsp.draw_map(0, 0, &M, P_x-12, P_y-12, 25, 25);
    dsp.draw_sprite(12*24, 12*24, P_sprite, P_spritestate);
    out.draw_to(&dsp);
    dsp.update();
}

int main(int argc, char *argv[])
{
    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());

    // Initialize game engine
    Game G;

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
