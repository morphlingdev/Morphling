#include "Entity.h"

Entity::Entity() // Constructor for any entity
{

}

Player::Player() // Constructor specifically for player
{

}

std::string& Entity::name() {return n;}             //
std::string& Entity::type() {return t;}             //
int& Entity::maxHitpoints() {return maxhp;}         //
int& Entity::hitpoints() {return hp;}               //
int& Entity::maxMana() {return maxm;}               //
int& Entity::mana() {return m;}                     // Class functions defined to access private/protected members
int& Entity::strength() {return str;}               //
int& Entity::armor() {return amr;}                  //
std::list<Ability>& Entity::abilities() {return a;} //
std::list<Item>& Player::items() {return i;}        //
int& Player::gold() {return gp;}                    //

int main() // Main function
{
	return 0;
}
