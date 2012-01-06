#ifndef ENTITY_H // Guard word
#define ENTITY_H

#include <iostream>
#include <string>
#include <list>

#include "Ability.h"

class Entity
{
protected:
    std::string name;
    std::string type;
    
    /* Basic attributes */
    int maxhp; // health
    int hp;
    int maxmp; // mana/magic points
    int mp;
    int str; // strength
    int armor; // armor level
    int lvl; // experience level
    
    /* Position information */
    int x;
    int y;
    
    // abilities
    std::list<Ability> a;
public:
    Entity(); // Constructor
    ~Entity(); // Destructor
    
    // Accessors and mutators
    std::string getName();
    std::string setName(std::string value);
    std::string getType();
    std::string setType(std::string value);
    int getMaxHP();
    int setMaxHP(int value);
    int addMaxHP(int value);
    int getHP();
    int setHP(int value);
    int addHP(int value);
    int getMaxMP();
    int setMaxMP(int value);
    int addMaxMP(int value);
    int getMP();
    int setMP(int value);
    int addMP(int value);
    int getStrength();
    int setStrength(int value);
    int addStrength(int value);
    int getArmor();
    int setArmor(int value);
    int addArmor(int value);
    int getLevel();
    int setLevel(int value);
    int addLevel(int value);
    std::list<Ability> getAbilities();
    std::list<Ability> setAbilities(std::list<Ability> value);
    
    int getX();
    int getY();
    int setPosition(int x, int y);
    int move(int x, int y);
};

class Player : public Entity
{
    //std::list<Item> i; // Inventory
    int gp; // Gold pieces
    // Need to implement level-up system etc.
    int xp; // Experience
public:
    Player(); 
    //std::list<Item>& items();
    int getGold();
    int setGold(int value);
    int addGold(int value);
    int getXP();
    int setXP(int value);
    int addXP(int value);
    void death(); // Goto here when player dies
    void level_up(); // Goto here when player levels up
};

#endif
