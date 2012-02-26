#include "Morphling.h"

Game::Game() :  M(100, 100), dsp(1024, 768), out("log.txt")
{
    out << "Welcome to Morphling. Walk around using the arrow keys. Press the space bar to generate a new map. Press Enter for command entry.\n";

    // currently we default to in-game
    state = GS_GAME;

    // Set up player -- SHOULD BE WRITTEN IN DATA FILE LATER INSTEAD OF HARDCODED
    P.setMaxHP(100);
    P.setHP(100);
    P.setPosition(50, 50); // Consistent with death (instead of (20,20))
    P.setSprite(Sprite(Sprite::TAR_IMP, Sprite::FACING_SOUTH));
    P.setType(Entity::PLAYER);
    P_dx = 0;
    P_dy = 0;
    P_movespeed = 100;
    P_skip = 0;
    keys_down = SDL_GetKeyState(NULL);
    entering_text = false;

    // initialize map with delicious perlin noise, regenerating when map is inadequate
    do
    {
        M.generate_perlin();
    }
    while(M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_WATER || M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_DEEPWATER || M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_MOUNTAIN || M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_LAVA);

    redraw();
}

int Game::getState()
{
    return state;
}

void Game::handle_command(std::string cmd)
{
    std::string original = cmd;
    for(int n = 0; n < cmd.length(); n++)
    {
        cmd[n] = tolower(cmd[n]);
    }
    if(cmd.compare("suicide") == 0)
    {
        P.setHP(0);
        P_turn();
    }
    else if(cmd.compare("n") == 0)
    {
        P.move(0, -1);
    }
    else if(cmd.compare("s") == 0)
    {
        P.move(0, 1);
    }
    else if(cmd.compare("e") == 0)
    {
        P.move(1, 0);
    }
    else if(cmd.compare("w") == 0)
    {
        P.move(-1, 0);
    }
    else if(cmd.compare("ne") == 0)
    {
        P.move(1, -1);
    }
    else if(cmd.compare("nw") == 0)
    {
        P.move(-1, -1);
    }
    else if(cmd.compare("se") == 0)
    {
        P.move(1, 1);
    }
    else if(cmd.compare("sw") == 0)
    {
        P.move(-1, 1);
    }
    else if(cmd.compare("blink") == 0)
    {
        P.move(rand()%7-3, rand()%7-3);
    }
    else if(cmd.compare("quit") == 0)
    {
        state = GS_QUIT;
    }
    else if(cmd.compare("help") == 0)
    {
        out << "'suicide' sets your health to 0.\n";
        out << "'blink' teleports you up to 3 blocks away.\n";
        out << "'quit' exits Morphling.\n";
        out << "'n' 'e' 'w' 's' 'ne' 'nw' 'se' 'sw' - ";
    }
    else if(cmd.compare("spawn") == 0)
    {
        out << "You call a ritual, and the deadly arrows come.\n";
        out << "You are the knee.\n";
        bool fail;
        int randx,randy;
        do // no one flies yet
        {
            fail = false;
            randx = rand()%20+1;
            randy = rand()%20+1;
            if(M.tileAt(randx,randy)->getAppearance() == Tile::IMG_LAVA || M.tileAt(randx,randy)->getAppearance() == Tile::IMG_DEEPWATER || M.tileAt(randx,randy)->getAppearance() == Tile::IMG_MOUNTAIN)
            {
                fail = true;
                continue;
            }
            for(int i = 0; i < E.size(); i++)
            {
                if(E[i].getX() == randx && E[i].getY() == randy)
                {
                    fail = true;
                    break;
                }
            }
        }
        while(fail);
        Creature e;
        e.setSprite(Sprite(Sprite::SENTIENT_ARROW,Sprite::FACING_SOUTH));
        e.setPosition(randx,randy);
        E.push_back(e);
    }
    else if(cmd.compare("smite") == 0)
    {
        out << "You call upon the power of the light, and exterminate all the arrows of the land!\n";
        E.clear();
    }
    else if(cmd.length() > 0)
    {
        out << original.append(" is an unrecognized command.\nType 'help' for a list of commands.\n"); // Quote the text plz!
    }
    return;
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
            break;
        case SDL_KEYDOWN:
            if(entering_text)
            {
                int length;
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    entering_text = false;
                    handle_command(entered_text);
                    entered_text.clear();
                    SDL_EnableUNICODE(0);
                    redraw();
                    break;
                case SDLK_BACKSPACE:
                    length = entered_text.length();
                    if(length >= 0) entered_text.erase(entered_text.length()-1);
                    redraw();
                    break;
                default:
                    char c = event.key.keysym.unicode;
                    if(isprint(c))
                    {
                        entered_text += c;
                        redraw();
                    }
                    break;
                }
            }
            else
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE: // generate a new map
                    P.setPosition(50,50); // so that when the player dies he does not appear on a "bad" tile; also for consistency
                    do
                    {
                        M.generate_perlin();
                    }
                    while(M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_WATER || M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_DEEPWATER || M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_MOUNTAIN || M.tileAt(P.getX(),P.getY())->getAppearance() == Tile::IMG_LAVA);
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
                    out << "Waiting...\n";
                    break;
                case SDLK_RETURN:
                    entering_text = true;
                    SDL_EnableUNICODE(1);
                    redraw();
                    break;
                default:
                    break;
                }
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
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
    tick_count++;
    bool mv = false;

    Tile::TileImgId t = M.tileAt(P.getX(), P.getY())->getAppearance();
    if(t == Tile::IMG_DEEPWATER)
    {
        out << "You are drowning!\n";
        P.addHP(-5);
    }

    for(int i=0; i<E.size(); i++) // since demons are retarted, no A*
    {
        // add drowning
        if(P.mDistTo(E[i]) <= 1)
        {
            out << "The demon strikes you, draining your soul!\n";
            P.addHP(-12);
        }
        else // they don't fly yet
        {
            int dx = P.getX() - E[i].getX(); // do we need these?
            int dy = P.getY() - E[i].getY();
            int cx = E[i].getX(),cy = E[i].getY();
            bool moved = false;
            bool move,nonlinear = false;
            int dirx,diry;
            if(!E[i].qIntel())
            {
                if(dx && dy)
                {
                    move = true;
                    nonlinear = true;
                    dirx = (P.getX() > cx ? 1 : -1);
                    diry = (P.getY() > cy ? 1 : -1);
                    if(!E[i].qFly() && M.tileAt(cx+dirx,cy+diry)->getAppearance() == Tile::IMG_MOUNTAIN)
                    {
                        move = false;
                    }
                    if(cx+dirx == P.getX() && cy+diry == P.getY())
                    {
                        move = false;
                    }
                    if(move)
                    {
                        for(int j = 0; j < E.size(); j++)
                        {
                            if(i == j)
                            {
                                continue;
                            }
                            if(cx+dirx == E[j].getX() && cy+diry == E[j].getY())
                            {
                                move = false;
                                break;
                            }
                        }
                    }
                    if(move)
                    {
                        E[i].move(dirx,diry);
                        moved = true;
                    }
                }
                if(!moved)
                {
                    bool move = true;
                    if(nonlinear)
                    {
                        bool movex = true;
                        if(std::sqrt((double(cx)+double(dirx)-double(P.getX()))*(double(cx)+double(dirx)-double(P.getX())) + (double(cy)-double(P.getY()))*(double(cy)-double(P.getY()))) >= std::sqrt((double(cx)-double(P.getX()))*(double(cx)-double(P.getX())) + (double(cy)+double(diry)-double(P.getY()))*(double(cy)+double(diry)-double(P.getY()))))
                        {
                            movex = false;
                        }
                        if(movex)
                        {
                            if(!E[i].qFly() && M.tileAt(cx+dirx,cy)->getAppearance() == Tile::IMG_MOUNTAIN)
                            {
                                move = false;
                            }
                            if(cx+dirx == P.getX() && cy == P.getY())
                            {
                                move = false;
                            }
                            if(move)
                            {
                                for(int j = 0; j < E.size(); j++)
                                {
                                    if(i == j)
                                    {
                                        continue;
                                    }
                                    if(cx+dirx == E[j].getX() && cy == E[j].getY())
                                    {
                                        move = false;
                                        break;
                                    }
                                }
                            }
                            if(move)
                            {
                                E[i].move(dirx,0);
                                moved = true;
                            }
                        }
                        else
                        {
                            if(M.tileAt(cx,cy+diry)->getAppearance() == Tile::IMG_MOUNTAIN)
                            {
                                move = false;
                            }
                            if(cx == P.getX() && cy+diry == P.getY())
                            {
                                move = false;
                            }
                            if(move)
                            {
                                for(int j = 0; j < E.size(); j++)
                                {
                                    if(i == j)
                                    {
                                        continue;
                                    }
                                    if(cx == E[j].getX() && cy+diry == E[j].getY())
                                    {
                                        move = false;
                                        break;
                                    }
                                }
                            }
                            if(move)
                            {
                                E[i].move(0,diry);
                                moved = true;
                            }
                        }
                    }
                    else
                    {
                        if(!dx)
                        {
                            dirx = 0;
                        }
                        else
                        {
                            dirx = (P.getX() > cx ? 1 : -1);
                        }
                        if(!dy)
                        {
                            diry = 0;
                        }
                        else
                        {
                            diry = (P.getY() > cy ? 1 : -1);
                        }
                        if(!E[i].qFly() && M.tileAt(cx+dirx,cy+diry)->getAppearance() == Tile::IMG_MOUNTAIN)
                        {
                            move = false;
                        }
                        if(cx+dirx == P.getX() && cy+diry == P.getY())
                        {
                            move = false;
                        }
                        if(move)
                        {
                            for(int j = 0; j < E.size(); j++)
                            {
                                if(i == j)
                                {
                                    continue;
                                }
                                if(cx+dirx == E[j].getX() && cy+diry == E[j].getY())
                                {
                                    move = false;
                                    break;
                                }
                            }
                        }
                        if(move)
                        {
                            E[i].move(dirx,diry);
                            moved = true;
                        }
                    }
                }
            }
        }
    }

    P.addHP(1);

    return mv;
}

void Game::simulate(int num_ticks)
{

}

void Game::P_turn()
{
    Tile::TileImgId t; // the tile the player is about to move onto

    t = M.tileAt(P.getX()+P_dx, P.getY()+P_dy)->getAppearance();

    if(t == Tile::IMG_MOUNTAIN) // trying to move onto a mountain?
    {
        out << "You are blocked by the mountains!\n";
    }
    else if(P_dx != 0 or P_dy != 0) // okay, move success
    {
        if(P_skip > 0)
        {
            out << "Movement interrupt.\n";
            P_skip = 0;
        }
        P.move(P_dx, P_dy);
        if(P_dx > 0) P.sprite().setState(Sprite::FACING_EAST);
        else if(P_dx < 0) P.sprite().setState(Sprite::FACING_WEST);
        else if(P_dy < 0) P.sprite().setState(Sprite::FACING_NORTH);
        else P.sprite().setState(Sprite::FACING_SOUTH);
    }

    t = M.tileAt(P.getX(), P.getY())->getAppearance();

    if(P_skip > 0)
    {
        P_skip--;
        if(P_skip == 0)
        {
            out << "Done.\n";
        }
    }

    while(tick()); // Handle all non-player entities

    if(P.getHP() <= 0) // Handle death
    {
        out << "You have died.\n\nThe Great Wind carries your spirit to the middle of the world, where it reassociates with a physical body.\n\nBe more cautious in your journeys!\n";
        P_skip = 0;
        P.death();
        P.setPosition(50, 50);
    }
}

void Game::redraw()
{
    // map
    dsp.draw_map(0, 0, &M, P.getX()-12, P.getY()-12, 25, 25);

    // player's sprite
    dsp.draw_sprite(12*24, 12*24, P.getSprite());

    // message log
    out.draw_to(&dsp);

    // entry bar
    if(entering_text)
    {
        dsp.fill_rect(610, 410, 300, 15, 48, 48, 32);
        dsp.draw_text_line(610, 410, entered_text, Display::FONT_SMALL, 255, 255, 255);
    }
    else
    {
        dsp.fill_rect(610, 410, 300, 15, 32, 32, 32);
    }

    // health bar
    dsp.fill_rect(0, 605, 600, 20, 0, 0, 0);
    dsp.fill_rect(0, 605, P.getHP()*600/P.getMaxHP(), 20, 255, 0, 0);
    dsp.draw_rect(0, 605, 600, 20, 255, 255, 255);

    // creatures
    for(int i=0; i<E.size(); i++)
    {
        dsp.draw_sprite(12*24+(E[i].getX()-P.getX())*24, 12*24+(E[i].getY()-P.getY())*24, E[i].getSprite());
    }

    // finally, put everything on the screen
    dsp.update();
}

void Game::calc_move()
{
    P_dx = int(keys_down[SDLK_RIGHT]) - int(keys_down[SDLK_LEFT]);
    P_dy = int(keys_down[SDLK_DOWN]) - int(keys_down[SDLK_UP]);
    return;
}

bool Game::move_req()
{
    bool mv = false;
    if(P_skip > 0)
    {
        mv = true;
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
            if(getState() == GS_QUIT) loop = false;
        }

        calc_move();

        if(SDL_GetTicks() - P_lastmove > 100 and move_req())
        {
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
    srand(time(NULL));

    // Initialize game engine
    Game G;

    // Quickly delegate the program to the game engine (short main functions are fashionable)
    int result = G.main_loop();

    return result;
}




