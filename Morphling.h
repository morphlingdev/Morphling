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
    Display dsp;
    MessageLog out;
    Display::Sprite P_sprite;
    Display::SpriteState P_spritestate;
    int state;

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
    void handle_event(SDL_Event &evt);
    void redraw();
    int getState();
};

#endif
