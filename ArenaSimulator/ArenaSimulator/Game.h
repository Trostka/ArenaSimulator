#ifndef GAME_H
#define GAME_H

#include "BaseUnit.h"
#include "BaseWeapon.h"

// The class that runs the game
class Game
{
private:
	// Player character
	BaseUnit* player;
	// Enemy character
	BaseUnit* enemy;
public:
	// Default constructor
	Game();

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