#include <string>

#ifndef ABILITY_H
#define ABILITY_H

//Constants
const int TARGET_LINE = 1;
const int TARGET_SMITE = 2;
const int STAT_STR = 1;
const int STAT_INT = 2;
const int STAT_BOB = 3; //these are examples
const int COST_MANA = 1;
const int COST_HEALTH = 2;
const int COST_GOLD = 3;

class Ability
{
private:
std::string name;
std::string desc;
int target_type;
int range;
int aoe_size;
int channel_time;
int cooldown;
int passive[];
int costs[];

public:

Ability(std::string);
};

#endif
