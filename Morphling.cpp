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
    P_nextmove = 0;
    tick_count = 0;
    P_skip = 0;
    keys_down = SDL_GetKeyState(NULL);
    entering_text = false;

    // initialize map with delicious perlin noise, regenerating when map is inadequate
    do
    {
        M.generate_perlin();
    }
    while(!M.safe(P.getX(), P.getY()) || !M.passable(P.getX(), P.getY()));

    M.tileAt(P.getX(), P.getY())->occupant = &P;

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
        P_dx=0;
        P_dy=-1;
        P_turn();
    }
    else if(cmd.compare("s") == 0)
    {
        P_dx=0;
        P_dy=1;
        P_turn();
    }
    else if(cmd.compare("e") == 0)
    {
        P_dx=1;
        P_dy=0;
        P_turn();
    }
    else if(cmd.compare("w") == 0)
    {
        P_dx=-1;
        P_dy=0;
        P_turn();
    }
    else if(cmd.compare("ne") == 0)
    {
        P_dx=1;
        P_dy=-1;
        P_turn();
    }
    else if(cmd.compare("nw") == 0)
    {
        P_dx=-1;
        P_dy=-1;
        P_turn();
    }
    else if(cmd.compare("se") == 0)
    {
        P_dx=1;
        P_dy=1;
        P_turn();
    }
    else if(cmd.compare("sw") == 0)
    {
        P_dx=-1;
        P_dy=1;
        P_turn();
    }
    else if(cmd.compare("blink") == 0)
    {
        P_dx=rand()%7-3;
        P_dy=rand()%7-3;
        P_turn();
    }
    else if(cmd.compare("teleport") == 0)
    {
        P_dx=0;
        P_dy=0;
        int randx, randy;
        do
        {
            randx = rand()%100;
            randy = rand()%100;
        }
        while(!M.passable(randx,randy) || M.occupied(randx,randy));
        P.setPosition(randx,randy);
        P_turn();
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
        out << "'spawn' spawns a creature.\n";
        out << "'smite' destroys all creatures.\n";
        out << "'teleport' teleports you to a random passable and unoccupied tile.\n";
        out << "'n' 'e' 'w' 's' 'ne' 'nw' 'se' 'sw' - \n";
    }
    else if(cmd.compare(0, 5, "spawn") == 0)
    {
        out << "You call a ritual, and the deadly arrows come.\n";
        out << "You are the knee.\n";
        bool flying = false;
        if(cmd.length() > 8 and cmd.compare(6, 3, "fly") == 0) flying = true;
        int randx,randy;
        do
        {
            randx = rand()%100;
            randy = rand()%100;
        }
        while(
            ((!M.passable(randx, randy) or !M.safe(randx, randy)) and !flying)
            or M.occupied(randx, randy));
        Creature e;
        if(flying) e.setFly(true);
        e.setSprite(Sprite(Sprite::SENTIENT_ARROW,Sprite::FACING_SOUTH));
        e.setPosition(randx,randy);
        e.setMaxHP(30);
        e.setHP(30);
        E.push_back(e);
    }
    else if(cmd.compare("smite") == 0)
    {
        out << "You call upon the power of the light, and exterminate all the arrows of the land!\n";
        E.clear();
    }
    else if(cmd.length() > 0)
    {
        out << std::string("\"").append(original.append("\" is an unrecognized command.\nType 'help' for a list of commands.\n"));
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
                    while(!M.safe(P.getX(), P.getY()));
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

bool Game::simulate_tick()
{
    bool mv = false;

    Tile::TileImgId t = M.tileAt(P.getX(), P.getY())->getAppearance();
    if(t == Tile::IMG_DEEPWATER)
    {
        out << "You are drowning!\n";
        P.addHP(-5);
    }

    for(int i=0; i<E.size(); i++)
    {
        if(!E[i].qFly() && !M.safe(E[i].getX(),E[i].getY()))
        {
            E[i].addHP(-5);
        }
        if(P.mDistTo(E[i]) <= 1)
        {
            out << "The demon strikes you, draining your soul!\n";
            P.addHP(-12);
        }
        if(E[i].getHP() <= 0)
        {
            E.erase(E.begin()+i);
        }
        else if(tick_count >= E[i].whenNextMove()) // do movement
        {
            int cx = E[i].getX(), cy = E[i].getY();
            int dx = P.getX() - cx;
            int dy = P.getY() - cy;
            int min_dist = 99999;
            int best_a=0, best_b=0;
            int dirx, diry;
            if(!E[i].qIntel())
            {
                if(dx > 0) dirx = 1;
                else if(dx < 0) dirx = -1;
                else dirx = 0;

                if(dy > 0) diry = 1;
                else if(dy < 0) diry = -1;
                else diry = 0;

                for(int a=-1;a<=1;a++){
                    for(int b=-1;b<=1;b++){
                        if((a == dirx or a == 0) and (b == diry or b == 0)
                        and (E[i].qFly() or M.passable(cx+a, cy+b))
                        and !M.occupied(cx+a, cy+b)){
                            int new_dist = P.mDistTo(cx+a, cy+b);
                            if(new_dist < min_dist){
                                min_dist = new_dist;
                                best_a = a; best_b = b;
                            }
                        }
                    }
                }

                M.tileAt(E[i].getX(), E[i].getY())->occupant = NULL;
                E[i].move(best_a, best_b);
                M.tileAt(E[i].getX(), E[i].getY())->occupant = &E[i];
            }

            E[i].nextMoveAt(tick_count+2);
        }
    }

    if(P.getHP() <= 0) // Handle player death
    {
        out << "You have died.\n\nThe Great Wind carries your spirit to the middle of the world, where it reassociates with a physical body.\n\nBe more cautious in your journeys!\n";
        P_skip = 0;
        P.death();
        M.tileAt(P.getX(), P.getY())->occupant = 0;
        P.setPosition(50, 50);
        M.tileAt(P.getX(), P.getY())->occupant = &P;
    }

    P.addHP(1);

    return mv;
}

void Game::P_turn()
{
    if(!M.passable(P.getX()+P_dx, P.getY()+P_dy)) // trying to move onto a mountain?
    {
        out << "Blocked.\n";
    }
    else if(P_dx != 0 or P_dy != 0) // okay, move success
    {
        if(P_skip > 0)
        {
            out << "Movement interrupt.\n";
            P_skip = 0;
        }

        if(M.occupied(P.getX()+P_dx, P.getY()+P_dy)){
            out << "You bump into the entity.\n";
        }
        else{
            M.tileAt(P.getX(), P.getY())->occupant = NULL;
            P.move(P_dx, P_dy);
            M.tileAt(P.getX(), P.getY())->occupant = &P;

            if(P_dx > 0) P.sprite().setState(Sprite::FACING_EAST);
            else if(P_dx < 0) P.sprite().setState(Sprite::FACING_WEST);
            else if(P_dy < 0) P.sprite().setState(Sprite::FACING_NORTH);
            else P.sprite().setState(Sprite::FACING_SOUTH);
        }
    }

    if(P_skip > 0)
    {
        P_skip--;
        if(P_skip == 0)
        {
            out << "Done.\n";
        }
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
    dsp.fill_rect(0, 605, std::max(P.getHP()*600/P.getMaxHP(), 0), 20, 255, 0, 0);
    dsp.draw_rect(0, 605, 600, 20, 255, 255, 255);

    // creatures
    for(int i=0; i<E.size(); i++)
    {
        int x = 12*24+(E[i].getX()-P.getX())*24;
        int y = 12*24+(E[i].getY()-P.getY())*24;
        dsp.draw_sprite(x, y, E[i].getSprite());
        dsp.fill_rect(x, y, E[i].getHP()*24/E[i].getMaxHP(), 1, 255, 0, 0);
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
        while(tick_count < P_nextmove){
            simulate_tick();
            tick_count++;
            redraw();
            SDL_Delay(40);
            while (SDL_PollEvent(&event));
        }
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
            P_nextmove = tick_count+1;
        }
        SDL_Delay(1000.0/30.0); // 30 fps
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
