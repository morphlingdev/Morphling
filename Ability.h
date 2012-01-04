#ifndef ABILITY_H
#define ABILITY_H

#include <string>

//Constants
const int TARGET_LINE = 0;
const int TARGET_SMITE = 1;
const int SHAPE_SQUARE = 0;
const int SHAPE_CIRCLE = 1;
const int STAT_STR = 0;
const int STAT_INT = 1;
const int STAT_BOB = 2; //these are examples
const int COST_MANA = 0;
const int COST_HEALTH = 1;
const int COST_GOLD = 2;

const int STAT_NUMBER = 3; //how many types of stats there are
const int COST_NUMBER = 3; //how many types of costs there are

class Ability
{
private:
    std::string name;
    std::string desc;
    int target_type;
    int range;
    int aoe_size;
    int aoe_shape;
    int channel_time;
    int cooldown;
    int passive[STAT_NUMBER];
    int costs[COST_NUMBER];

public:

    Ability(std::string);
};

#endif
