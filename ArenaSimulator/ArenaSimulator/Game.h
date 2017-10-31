#ifndef GAME_H
#define GAME_H

#include "BaseUnit.h"
#include "BaseWeapon.h"

#include <vector>

// The class that runs the game
class Game
{
private:
	// Player character
	BaseUnit* player;
	// Enemy character
	BaseUnit* enemy;

	// List of weapons provided by weapons data file
	std::vector<BaseWeapon> weaponList;
public:
	// Default constructor
	Game();

	// Load the xml file for weapons data and copy its contents into weaponList
	void GetWeaponData();

	// Search for a weapon whose name matches the string parameter
	BaseWeapon SearchForWeapon(std::string name);

	// Find weapon type based on the string parameter
	WeaponType FindWeaponType(std::string name);
	// Find damage type based on the string parameter
	DamageType FindDamageType(std::string name);

	// Game loop
	void GameLoop();

	// Combat handler
	void Combat(BaseUnit* attacker, BaseUnit* target);

	// Destructor
	~Game()
	{
		delete player, enemy;
	}
};

#endif