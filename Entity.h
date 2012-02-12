#ifndef ENTITY_H // Guard word
#define ENTITY_H

#include <iostream>
#include <string>
#include <list>

#include "Ability.h"
#include "Item.h"
#include "Sprite.h"

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
    Sprite appearance;

    /* Position information */
    int x;
    int y;

    // abilities
    std::list<Ability> a;
public:
    Entity(); // Constructor
    virtual ~Entity(); // Destructor declared virtual so that the destructor binds late (dreaded memory leaks)

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
    Sprite &sprite();
    Sprite getSprite();
    void setSprite(Sprite a);
    std::list<Ability> getAbilities();
    std::list<Ability> setAbilities(std::list<Ability> value);

    int getX();
    int getY();
    void setPosition(int x, int y);
    void move(int x, int y);
};

class Player : public Entity
{
    std::list<Item> i; // Inventory
    int gp; // Gold pieces
    // Need to implement level-up system etc.
    int xp; // Experience
public:
    Player();
	~Player();
    std::list<Item> getItems();
	std::list<Item> setItems(std::list<Item> value);
    int getGold();
    int setGold(int value);
    int addGold(int value);
    int getXP();
    int setXP(int value);
    int addXP(int value);
    void death(); // Goto here when player dies
    void level_up(); // Goto here when player levels up
};

class Creature : public Entity
{
protected:
	std::list<Item> d; // drops
public:
	std::list<Item> getDrops();
	std::list<Item> setDrops(std::list<Item> value);    
	void death(Player P);
	Creature();
	~Creature();
};

#endif
