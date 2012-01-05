#include "Entity.h"

// The following functions will perform basic actions for an entity
Entity::Entity() // Constructor for any entity
{
    // Randomly generate creature type
    //hp = maxhp = ;
    //m = maxm = ;
    //
    // idk if we need this
}
Entity::~Entity() // Destructor for mobs
{
    // Drop loot
    // Player gains xp
}
Player::Player() // Constructor specifically for player
{
    // idk if we need this
}
void Player::death() // Goto here when player dies
{
    hp = maxhp/2; // Attributes when
    m = maxm;     // respawning
    gp /= 2;      //
    // Need spawning mechanism (location)
    return;
}
void Player::level_up()
{
    maxhp *= 1.2; // Assuming 20% increase per level
    hp = maxhp; // Health regeneration
    maxm *= 1.2;
    m = maxm;
    // experience stuff
    lvl++;
    // random trait, etc.
    return;
}

// The following functions are defined to access private/protected members
std::string& Entity::name()
{
    return n;
}
std::string& Entity::type()
{
    return t;
}
int& Entity::maxHitpoints()
{
    return maxhp;
}
int& Entity::hitpoints()
{
    return hp;
}
int& Entity::maxMana()
{
    return maxm;
}
int& Entity::mana()
{
    return m;
}
int& Entity::strength()
{
    return str;
}
int& Entity::armor()
{
    return amr;
}
int& Entity::level()
{
    return lvl;
}
std::list<Ability>& Entity::abilities()
{
    return a;
}
//std::list<Item>& Player::items()
//{
//  return i;
//}
int& Player::gold()
{
    return gp;
}
int& Player::experience()
{
    return xp;
}
