#include "Entity.h"

Entity::Entity() // Constructor for any entity
{

}

Player::Player() // Constructor specifically for player
{

}

void Player::death() // Goto here when player dies
{
  
}

std::string& Entity::name() {return n;}             //
std::string& Entity::type() {return t;}             //
int& Entity::maxHitpoints() {return maxhp;}         //
int& Entity::hitpoints() {return hp;}               //
int& Entity::maxMana() {return maxm;}               //
int& Entity::mana() {return m;}                     // Class functions defined
int& Entity::strength() {return str;}               // to access private/protected
int& Entity::armor() {return amr;}                  // members
std::list<Ability>& Entity::abilities() {return a;} //
//std::list<Item>& Player::items() {return i;}        //
int& Player::gold() {return gp;}                    //

