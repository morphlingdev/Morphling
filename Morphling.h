#ifndef MORPHLING_H
#define MORPHLING_H

#include <cstdlib>
#include <cctype>
#include <time.h>

#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#endif

#include "Display.h"
#include "Ability.h"
#include "Entity.h"
#include "MessageLog.h"
#include "Sprite.h"
#include <cmath>

#define TOTALWIDTH 1024
#define TOTALHEIGHT 768

class Game
{
private:
    Map M;
    Player P; // the player's own entity
    std::vector<Creature> E;
    int tick_count;
    int P_dx;
    int P_dy;
    int P_nextmove; // tick at which player will next move
    int P_movespeed;
    int P_skip;
    Display dsp;
    MessageLog out;
    int state;
    Uint8 *keys_down;
    bool entering_text;
    std::string entered_text;

    int map_w;
    int map_h;

public:
    // game states
    enum GameState
    {
        GS_QUIT, GS_MENU, GS_GAME, GS_PAUSE
    };

    // constructor and destructor
    Game();
    ~Game() {}

    // functions
    void handle_command(std::string cmd);
    void handle_event(SDL_Event &evt);
    bool simulate_tick();
    void P_turn();
    void redraw();
    int getState();
    bool move_req();
    int main_loop();
    void calc_move();
};

#endif
