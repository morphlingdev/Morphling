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
    P_sprite = Display::SPRITE_TAR_IMP;
    P_spritestate = Display::SPRITE_STATE_FACING_SOUTH;
    P_dx = 0;
    P_dy = 0;
    P_movespeed = 100;
    P_skip = 0;

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
                redraw();
                break;
            case SDLK_PERIOD:
                // skip a single turn
                P_skip = 1;
                break;
            case SDLK_5:
                // skip 10 turns
                P_skip = 10;
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

bool Game::tick()
{
    num_ticks++;
    bool mv = false;
    return mv;
}

void Game::P_turn()
{
    P.move(P_dx, P_dy);
    if(P_dx > 0) P_spritestate = Display::SPRITE_STATE_FACING_EAST;
    else if(P_dx < 0) P_spritestate = Display::SPRITE_STATE_FACING_WEST;
    else if(P_dy < 0) P_spritestate = Display::SPRITE_STATE_FACING_NORTH;
    else P_spritestate = Display::SPRITE_STATE_FACING_SOUTH;
    
    if(M.tileAt(P.getX(), P.getY())->getAppearance() == Tile::IMG_DEEPWATER)
    {
        out << "You are drowning!\n";
        P.addHP(-1);
    }
    
    while(tick()); // Handle all non-player entities
}

void Game::redraw()
{
    // map
    dsp.draw_map(0, 0, &M, P.getX()-12, P.getY()-12, 25, 25);
    
    // player's sprite
    dsp.draw_sprite(12*24, 12*24, P_sprite, P_spritestate);
    
    // message log
    out.draw_to(&dsp);
    
    // health bar
    dsp.fill_rect(0, 605, 600, 20, 0, 0, 0);
    dsp.fill_rect(0, 605, P.getHP()*600/P.getMaxHP(), 20, 255, 0, 0);
    dsp.draw_rect(0, 605, 600, 20, 255, 255, 255);
    
    // finally, put everything on the screen
    dsp.update();
}

bool Game::move_req()
{
    bool mv = false;
    if(P_skip)
    {
        mv = true;
        P_skip--;
    }
    if(P_dx != 0 || P_dy != 0) mv = true;
    return mv;
}

int Game::main_loop()
{
    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    
    bool loop = true;
    int P_lastmove;
    while(loop)
    {
        while (SDL_PollEvent(&event))
        {
            handle_event(event);
            if(getState() == Game::GS_QUIT) loop = false;
        }
        
        if(SDL_GetTicks() - P_lastmove > 100 and move_req()){
            P_lastmove = SDL_GetTicks();
            P_turn();
            redraw();
        }
        SDL_Delay(1000.00/30.00); // 30 fps
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // seed random with processor ticks, pseudorandom enough
    srand(SDL_GetTicks());

    // Initialize game engine
    Game G;
    
    // Quickly delegate the program to the game engine (short main functions are fashionable)
    int result = G.main_loop();
    
    return result;
}
