#ifndef ENTITY_H // Guard word
#define ENTITY_H

#include <iostream>
#include <string>
#include <list>

#include "Ability.h"

class Entity
{
protected:
	std::string n; // Entity's name
	std::string t; // Type of entity
	int maxhp; //
	int hp;    //
	int maxm;  // Basic attributes
	int m;     // of the entity
	int str;   //
	int amr;   //
	int lvl;
	std::list<Ability> a; // Entity's abilities
public:
	Entity(); // Constructor
	~Entity(); // Destructor
	std::string& name();             //
	std::string& type();             //
	int& maxHitpoints();             //
	int& hitpoints();                //
	int& maxMana();                  // References to
	int& mana();                     // protected members
	int& strength();                 //
	int& armor();                    //
	int& level();                    //
	std::list<Ability>& abilities(); //
};

class Player : public Entity
{
	//std::list<Item> i; // Inventory
	int gp; // Gold pieces 
	// Need to implement level-up system etc.
	int xp; // Experience
public:
	Player(); // Constructor
	//std::list<Item>& items(); // References to
	int& gold();              // private members
	int& experience();        //
	void death(); // Goto here when player dies
	void level_up(); // Goto here when player levels up
};

#endif
