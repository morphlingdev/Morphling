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
    Display dsp;
    Map M;
    Player P; // the player's own entity
    MessageLog out;
    int P_x;
    int P_y;
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
    int handle_event(SDL_Event &evt);
    void redraw();
};

#endif
