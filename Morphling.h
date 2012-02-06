#ifndef MORPHLING_H
#define MORPHLING_H

#include <cstdlib>

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

#define TOTALWIDTH 1024
#define TOTALHEIGHT 768

class Game
{
private:
    Map M;
    Player P; // the player's own entity
    Display::Sprite P_sprite;
    Display::SpriteState P_spritestate;
    int num_ticks;
    int P_dx;
    int P_dy;
    int P_lastmove;
    int P_movespeed;
    int P_skip;
    Display dsp;
    MessageLog out;
    int state;
    struct
    {
        bool up_arrow;
        bool down_arrow;
        bool right_arrow;
        bool left_arrow;
    } keys_down;
    bool entering_text;
    std::string entered_text;

public:
    // game states
    enum GameState
    {
        GS_QUIT, GS_MENU, GS_GAME, GS_PAUSE
    };

    // constructor and destructor
    Game();
    ~Game() {};

    // functions
    void handle_command(std::string cmd);
    void handle_event(SDL_Event &evt);
    bool tick();
    void P_turn();
    void redraw();
    int getState();
    bool move_req();
    int main_loop();
    void calc_move();
};

#endif
