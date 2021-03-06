// Implementation file for Game class

#include "stdafx.h"
#include "Game.h"
#include "tinyxml2.h"

#include <time.h>		// Used for random hit chance
#include <iostream>

using namespace std;
using namespace tinyxml2;

// Get input for stats of player and their weapon at the start of the game
Game::Game()
{
	// Initialize random seed
	srand(time(NULL));

	GetWeaponData();

	// Player input variables to use for stats
	int hp, atk, skl, spd, def, res;

	// Input vars to use for player's weapon
	string wepName = "";
	int wepAtk, wepHit, wepType, dmgType, strType, wkType;
	wepAtk = wepType = dmgType = strType = wkType = -1;

	// Temporary weapon variable
	BaseWeapon tempWep;

	// Used to decide whether to use a weapon from the weapon list or create your own
	int choice = 0;

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

	// Ask player to choose between using weapon from weapon list or creating their own
	while (choice != 1 && choice != 2)
	{
		cout << "Would you like to:\n";
		cout << "1. Equip a weapon from the data file\n";
		cout << "2. Create your own weapon.\n";
		cin >> choice;

		if (choice != 1 && choice != 2)
			cout << "Invalid choice. Please enter 1 or 2.\n";
	}

	// Use a weapon from the array
	if (choice == 1)
	{
		// Set tempWep's name to "-1" for searching purposes
		tempWep.setWeaponName("-1");

		// Search for a weapon whose name matches wepName, validating input
		while (tempWep.getWeaponName() != wepName)
		{
			cin.ignore();
			cout << "Please enter the name of the weapon you would like to use: ";
			getline(cin, wepName);
			
			tempWep = SearchForWeapon(wepName);

			if (tempWep.getWeaponName() != wepName)
				cout << "Weapon not found. Please try again.\n";
		}
	}
	// Create a custom weapon
	else if (choice == 2)
	{
		// Get weapon name
		cin.ignore();
		cout << "Please enter the weapon's name: ";
		getline(cin, wepName);
		// Get weapon attack
		cout << "Please enter the weapon's attack: ";
		cin >> wepAtk;
		// Get weapon hit rate
		cout << "Please enter the weapon's hit rate: ";
		cin >> wepHit;

		// Set the weapon's name, attack, and hit rate
		tempWep.setWeaponName(wepName);
		tempWep.setWeaponAtk(wepAtk);
		tempWep.setWeaponHit(wepHit);

		// Get weapon type, validating input
		while (wepType < SWORD || wepType > NONE)
		{
			cout << "Please enter the type of your weapon.\n";
			cout << "0 = Sword, 1 = Axe, 2 = Lance, 3 = Bow, 4 = Tome, 5 = None\n";
			cin >> wepType;

			if (wepType < SWORD || wepType > NONE)
				cout << "Invalid weapon type. Please try again.\n";
		}

		// Set the type of the weapon
		tempWep.setWeaponType(static_cast<WeaponType>(wepType));

		// Get damage type, validating input
		while (dmgType < PHYSICAL || dmgType > MAGICAL)
		{
			cout << "Please enter the damage type of your weapon.\n";
			cout << "0 = Physical, 1 = Magical\n";
			cin >> dmgType;

			if (dmgType < PHYSICAL || dmgType > MAGICAL)
				cout << "Invalid damage type. Please try again.\n";
		}

		// Set the weapon's damage type
		tempWep.setDamageType(static_cast<DamageType>(dmgType));

		// Get weapon advantage type, validating input
		while (strType < SWORD || strType > NONE)
		{
			cout << "Please enter the weapon type your weapon is strong against.\n";
			cout << "0 = Sword, 1 = Axe, 2 = Lance, 3 = Bow, 4 = Tome, 5 = None\n";
			cin >> strType;

			if (strType < SWORD || strType > NONE)
				cout << "Invalid advantage type. Please try again.\n";
		}

		// Set the weapon's advantage type
		tempWep.setStrongType(static_cast<WeaponType>(strType));

		// Get weapon disadvantage type, validating input
		while (wkType < SWORD || wkType > NONE)
		{
			cout << "Please enter the weapon type your weapon is weak against.\n";
			cout << "0 = Sword, 1 = Axe, 2 = Lance, 3 = Bow, 4 = Tome, 5 = None\n";
			cin >> wkType;

			if (wkType < SWORD || wkType > NONE)
				cout << "Invalid disadvantage type. Please try again.\n";
		}

		// Set the weapon's disadvantage type
		tempWep.setWeakType(static_cast<WeaponType>(wkType));
	}

	// Set up the player and the enemy
	player = new BaseUnit(hp, atk, skl, spd, def, res, tempWep);
	enemy = new BaseUnit(20, 3, 6, 6, 2, 4, "Fire Tome", 5, 90, TOME, MAGICAL, NONE, NONE);

	GameLoop();
}

// Read weapon data into the game from an xml file
void Game::GetWeaponData()
{
	string damageName,		// Name of the damage type
		   wepTypeName,		// Name of the weapon type
		   wepName;			// Name of the weapon

	DamageType dmgType;			// Weapon's damage type, based on damageName
	WeaponType wepType,			// Type of the weapon, based on wepTypeName
			   wepAdv,			// Weapon advantage type
			   wepDisadv;		// Weapon disadvantage type

	int wepAtk, wepHit;		// Weapon attack and hit rate

	// Open the weapon data document for reading
	XMLDocument doc;
	doc.LoadFile("Content/Data/WeaponData.xml");
	//cout << doc.ErrorIDToName(doc.ErrorID()) << endl;

	// Get the root node of the document
	XMLElement* rootNode = doc.FirstChildElement("weapons");

	// Get the first damage type node
	XMLElement* damageNode = rootNode->FirstChildElement("damage");

	// While damageNode exists...
	while (damageNode != NULL)
	{
		// Get the name of the damage type
		damageName = damageNode->Attribute("type");

		// Get the first weapon type in the current damage category
		XMLElement* wepTypeNode = damageNode->FirstChildElement("weapon");

		// While wepTypeNode exists...
		while (wepTypeNode != NULL)
		{
			// Get the current weapon type
			wepTypeName = wepTypeNode->Attribute("type");
			
			// Get the first weapon of the current type
			XMLElement* weaponNode = wepTypeNode->FirstChildElement("weapon");

			// while weaponNode exists...
			while (weaponNode != NULL)
			{
				// Get the weapon's attributes
				wepName = weaponNode->Attribute("name");
				weaponNode->QueryIntAttribute("attack", &wepAtk);
				weaponNode->QueryIntAttribute("hitrate", &wepHit);
				wepType = FindWeaponType(wepTypeName);
				dmgType = FindDamageType(damageName);
				wepAdv = FindWeaponType(weaponNode->Attribute("advantage"));
				wepDisadv = FindWeaponType(weaponNode->Attribute("disadvantage"));
					
				// Create a temp weapon using the current attributes and add it to weaponList
				BaseWeapon tempWep(wepName, wepAtk, wepHit, wepType, dmgType, wepAdv, wepDisadv);
				weaponList.push_back(tempWep);

				weaponNode = weaponNode->NextSiblingElement("weapon");
			}

			wepTypeNode = wepTypeNode->NextSiblingElement("weapon");
		}

		damageNode = damageNode->NextSiblingElement("damage");
	}
}

// Search for a weapon within the weapon list
BaseWeapon Game::SearchForWeapon(string name)
{
	// Perform a linear search for a weapon with a matching name
	vector<BaseWeapon>::iterator iter;
	for (iter = weaponList.begin(); iter < weaponList.end(); iter++)
	{
		if (iter->getWeaponName() == name)
		{
			return *iter;
			break;
		}
	}

	// If the weapon is not found, return the last element of weaponList
	return *iter;
}

// Get the weapon type by passing a string
WeaponType Game::FindWeaponType(string name)
{
	if (name == "SWORD")
		return SWORD;
	else if (name == "LANCE")
		return LANCE;
	else if (name == "AXE")
		return AXE;
	else if (name == "BOW")
		return BOW;
	else if (name == "TOME")
		return TOME;
	else
		return NONE;
}

// Get the damage type by passing a string
DamageType Game::FindDamageType(string name)
{
	if (name == "PHYSICAL")
		return PHYSICAL;
	else if (name == "MAGICAL")
		return MAGICAL;
	else
		return PHYSICAL;
}

// While both player and enemy don't have 0 hp, keep running this
void Game::GameLoop()
{
	// Used to decide if the player wants to surrender
	int choice;

	while (true)
	{
		// Set choice so the menu always pops up after each round of combat
		choice = -1;

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
	// Variable for dodge chance used by both sides
	int dodgeChance;

	// Variable to hold damage
	int calculatedDmg;

	// Hold attacker and target weapons
	BaseWeapon* atkWep = attacker->getEquippedWeapon(); 
	BaseWeapon* tarWep = target->getEquippedWeapon();

	// Calculate dodgeChance, using the target's speed
	dodgeChance = target->getSpeed() * 5;

	// If a random number rolls lower than dodgeChance, target dodges the attack
	if ((rand() % 100 + 1) <= dodgeChance)
	{
		cout << "... but the attack missed!\n";
		return;
	}

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