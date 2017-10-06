// Implementation file for Game class

#include "stdafx.h"
#include "Game.h"

#include <iostream>
using namespace std;

// Get input for stats of player and their weapon at the start of the game
Game::Game()
{
	// Player input variables to use for stats
	int hp, atk, skl, spd, def, res;

	// Input vars to use for player's weapon
	string wepName;
	int wepAtk, wepType, dmgType, strType, wkType;
	wepAtk = wepType = dmgType = strType = wkType = -1;

	// Get player hit points
	cout << "Please enter the player's max HP: ";
	cin >> hp;
	// Get player attack
	cout << "Please enter the player's attack: ";
	cin >> atk;
	// Get player skill
	cout << "Please enter the player's skill: ";
	cin >> skl;
	// Get player speed
	cout << "Please enter the player's speed: ";
	cin >> spd;
	// Get player defense
	cout << "Please enter the player's physical defense: ";
	cin >> def;
	// Get player resistance
	cout << "Please enter the player's magical resistance: ";
	cin >> res;

	// Get weapon name
	cin.ignore();
	cout << "Please enter the weapon's name: ";
	getline(cin, wepName);
	// Get weapon attack
	cout << "Please enter the weapon's attack: ";
	cin >> wepAtk;

	// Get weapon type, validating input
	while (wepType < SWORD || wepType > NONE)
	{
		cout << "Please enter the type of your weapon.\n";
		cout << "0 = Sword, 1 = Axe, 2 = Lance, 3 = Bow, 4 = Tome, 5 = None\n";
		cin >> wepType;

		if (wepType < SWORD || wepType > NONE)
			cout << "Invalid weapon type. Please try again.\n";
	}

	// Get damage type, validating input
	while (dmgType < PHYSICAL || dmgType > MAGICAL)
	{
		cout << "Please enter the damage type of your weapon.\n";
		cout << "0 = Physical, 1 = Magical\n";
		cin >> dmgType;

		if (dmgType < PHYSICAL || dmgType > MAGICAL)
			cout << "Invalid damage type. Please try again.\n";
	}

	// Get weapon advantage type, validating input
	while (strType < SWORD || strType > NONE)
	{
		cout << "Please enter the weapon type your weapon is strong against.\n";
		cout << "0 = Sword, 1 = Axe, 2 = Lance, 3 = Bow, 4 = Tome, 5 = None\n";
		cin >> strType;

		if (strType < SWORD || strType > NONE)
			cout << "Invalid advantage type. Please try again.\n";
	}

	// Get weapon disadvantage type, validating input
	while (wkType < SWORD || wkType > NONE)
	{
		cout << "Please enter the weapon type your weapon is weak against.\n";
		cout << "0 = Sword, 1 = Axe, 2 = Lance, 3 = Bow, 4 = Tome, 5 = None\n";
		cin >> wkType;

		if (wkType < SWORD || wkType > NONE)
			cout << "Invalid disadvantage type. Please try again.\n";
	}

	// Set up the player and the enemy
	player = new BaseUnit(hp, atk, skl, spd, def, res, wepName, wepAtk, 
		static_cast<WeaponType>(wepType), static_cast<DamageType>(dmgType), 
		static_cast<WeaponType>(strType), static_cast<WeaponType>(wkType));
	enemy = new BaseUnit(20, 3, 6, 6, 2, 4, "fire tome", 5, TOME, MAGICAL, NONE, NONE);

	GameLoop();
}

// While both player and enemy don't have 0 hp, keep running this
void Game::GameLoop()
{
	// Used to decide if the player wants to surrender
	int choice = -1;

	while (true)
	{
		// Player attacks
		cout << "Player attacks Enemy with the " << player->getWeaponName();
		Combat(player, enemy);

		// Display enemy health
		cout << "Enemy is at " << enemy->getCurrentHp() << " hit points!\n";
		
		// Check if enemy is still conscious
		if (enemy->getCurrentHp() <= 0)
		{
			cout << "Enemy is down!\n";
			break;
		}

		// Enemy attacks
		cout << "Enemy attacks Player with the " << enemy->getWeaponName();
		Combat(enemy, player);

		// Display player health
		cout << "Player is at " << player->getCurrentHp() << " hit points!\n";

		// Check if player is still conscious
		if (player->getCurrentHp() <= 0)
		{
			cout << "Player is down!\n";
			break;
		}

		// Ask the player to make choose their next move, validating input
		while (choice != 0 && choice != 1)
		{ 
			cout << "What would you like to do? (0 = Attack, 1 = Give Up) ";
			cin >> choice;

			if (choice != 0 && choice != 1)
				cout << "Invalid action. Please try again.\n";
		}

		// If player surrenders, end the game
		if (choice == 1)
		{
			cout << "Player has given up!\n";
			break;
		}
	}
}

// Attacker deals damage to target after accounting for defenses
void Game::Combat(BaseUnit* attacker, BaseUnit* target)
{
	// Variable to hold damage
	int calculatedDmg;
	// Hold attacker and target weapons
	BaseWeapon* atkWep = attacker->getEquippedWeapon(); 
	BaseWeapon* tarWep = target->getEquippedWeapon();

	// Decide how target takes damage based on attacker's weapon type
	switch (atkWep->getDamageType())
	{
	case PHYSICAL:
		calculatedDmg = attacker->getTotalAtk() - target->getDefense();
		break;
	case MAGICAL:
		calculatedDmg = attacker->getTotalAtk() - target->getResistance();
		break;
	}

	// Determine whether the attacker has weapon advantage or disadvantage
	if (tarWep->getWeaponType() == atkWep->getStrongType())
	{
		calculatedDmg += 3;
	}
	else if (tarWep->getWeaponType() == atkWep->getWeakType())
	{
		calculatedDmg -= 3;
	}

	// Deal the calculated damage...
	target->takeDamage(calculatedDmg);
	// ...then display it
	cout << " for " << calculatedDmg << " damage!\n";
}