#ifndef BASEUNIT_H
#define BASEUNIT_H

#include "BaseWeapon.h"

// The class that all unit classes will derive from
class BaseUnit
{
private:
	// Current and maximum hitpoints
	int currentHp, maxHp;
	// Unit stats
	int attack, skill, speed, defense, resistance;
	// Unit's attack stat + equipped weapon; twice unit's skill stat + weapon hit rate
	int totalAtk, totalHit;
	// Unit's equipped weapon
	BaseWeapon* equippedWeapon;
public:
	// Default constructor
	BaseUnit()
	{
		currentHp = maxHp = 20;
		attack = skill = speed = defense = resistance = 5;
		equippedWeapon = new BaseWeapon();
	}

	// Constructor with parameters
	BaseUnit(int hp, int ak, int sk, int sp, int df, int rs, std::string wepName, int wepAtk, int wepHit, WeaponType wepType, DamageType dmgType,
		WeaponType strType, WeaponType wkType) :
		maxHp(hp), attack(ak), skill(sk), speed(sp), defense(df), resistance(rs)
	{
		// Set currentHp to maxHp
		currentHp = maxHp;

		// Equip a weapon
		equippedWeapon = new BaseWeapon(wepName, wepAtk, wepHit, wepType, dmgType, strType, wkType);

		// Get totalAtk by adding weapon attack to unit's attack stat
		totalAtk = attack + equippedWeapon->getWeaponAtk();
		// Get totalHit by adding weapon hit to twice unit's skill stat
		totalHit = (skill * 2) + equippedWeapon->getWeaponHit();
	}

	// Take damage dealt by the enemy
	void takeDamage(int amt) { currentHp -= amt; }

	// Accessor for currentHp
	int getCurrentHp() { return currentHp; }
	// Accessor for totalAtk
	int getTotalAtk() { return totalAtk; }
	// Accessor for speed
	int getSpeed() { return speed; }
	// Accessor for defense
	int getDefense() { return defense; }
	// Accessor for resistance
	int getResistance() { return resistance; }

	// Accessor for weapon
	BaseWeapon* getEquippedWeapon() { return equippedWeapon; }
	// Accessor for weapon name
	std::string getWeaponName() { return equippedWeapon->getWeaponName(); }
	// Accessor for weapon attack
	int getWeaponAttack() { return equippedWeapon->getWeaponAtk(); }

	// Destructor
	~BaseUnit()
	{
		delete equippedWeapon;
	}
};

#endif