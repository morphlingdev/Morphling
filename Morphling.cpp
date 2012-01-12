#include "Morphling.h"

Game::Game() :  M(100, 100), dsp(1024, 768), out("log.txt")
{
    out << "Welcome to Morphling. Walk around using the arrow keys. Press the space bar to generate a new map.\n";

    // currently we default to in-game
    state = GS_GAME;

    // Set up player -- SHOULD BE WRITTEN IN DATA FILE LATER INSTEAD OF HARDCODED
    P.setMaxHP(100);
    P.setHP(100);
    P.setPosition(20, 20);
    P_sprite = Display::SPRITE_PLAYERARROW;
    P_spritestate = Display::SPRITE_STATE_FACING_SOUTH;
    P_dx = 0;
    P_dy = 0;
    P_movespeed = 100;

    // initialize map with delicious perlin noise
    M.generate_perlin();

    redraw();
}

int Game::getState()
{
    return state;
}

void Game::handle_event(SDL_Event &event)
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
                P_dy = -1;
                break;
            case SDLK_RIGHT:
                P_dx = 1;
                break;
            case SDLK_DOWN:
                P_dy = 1;
                break;
            case SDLK_LEFT:
                P_dx = -1;
                break;
            case SDLK_SPACE:
                // generate a new map
                M.generate_perlin();
                out << "New map generated.\n";
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                P_dy = 0;
                break;
            case SDLK_RIGHT:
                P_dx = 0;
                break;
            case SDLK_DOWN:
                P_dy = 0;
                break;
            case SDLK_LEFT:
                P_dx = 0;
                break;
            default:
                break;
            }
        default:
            return;
        }
        break;
    case GS_QUIT:
        return;
    default:
        exit(9001);
    }
    return;
}

void Game::handle_logic()
{
    if((P_dx != 0 or P_dy != 0) and SDL_GetTicks() - P_lastmove > P_movespeed){
        P.move(P_dx, P_dy);
        P_lastmove = SDL_GetTicks();
        if(P_dx > 0) P_spritestate = Display::SPRITE_STATE_FACING_EAST;
        else if(P_dx < 0) P_spritestate = Display::SPRITE_STATE_FACING_WEST;
        else if(P_dy < 0) P_spritestate = Display::SPRITE_STATE_FACING_NORTH;
        else P_spritestate = Display::SPRITE_STATE_FACING_SOUTH;
        
    }
    
    if(SDL_GetTicks() - LastTick > 1000) // One check every second
    {
        LastTick = SDL_GetTicks();
        if(M.tileAt(P.getX(), P.getY())->getAppearance() == Tile::IMG_WATER)
        {
            out << "You are drowning!\n";
        }
    }
}

void Game::redraw()
{
    dsp.draw_map(0, 0, &M, P.getX()-12, P.getY()-12, 25, 25);
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
            G.handle_event(event);
            if(G.getState() == Game::GS_QUIT) loop = false;
        }
        G.handle_logic();
        G.redraw();
        SDL_Delay(1000.00/30.00); // 30 fps, both graphics and game
    }
    return 0;
}
