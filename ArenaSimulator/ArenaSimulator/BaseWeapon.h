#ifndef BASEWEAPON_H
#define BASEWEAPON_H

#include <string>

// Types of weapons
enum WeaponType{ SWORD, LANCE, AXE, BOW, TOME, NONE };

// Types of weapon damage
enum DamageType { PHYSICAL, MAGICAL };

// The class that all weapon classes will derive from
class BaseWeapon
{
private:
	// Name of the weapon
	std::string weaponName;
	// Weapon's attack power
	int weaponAtk;
	// Weapon's hit rate
	int weaponHit;
	// Type of the weapon
	WeaponType weaponType;
	// Weapon's damage type
	DamageType damageType;
	// Weapon type this weapon is strong against
	WeaponType strongType;
	// Weapon type this weapon is weak against
	WeaponType weakType;

public:
	// Default constructor
	BaseWeapon()
	{
		weaponName = "Weapon";
		weaponAtk = 5;
		weaponHit = 90;
		weaponType = SWORD;
		damageType = PHYSICAL;
		strongType = AXE;
		weakType = LANCE;
	}

	// Constructor with parameters
	BaseWeapon(std::string name, int atk, int hit, WeaponType wepType, DamageType dmgType, WeaponType strType, WeaponType wkType) : 
		weaponName(name), weaponAtk(atk), weaponHit(hit), weaponType(wepType), damageType(dmgType), strongType(strType), weakType(wkType)
	{}

	// Accessor for weaponName
	std::string getWeaponName() { return weaponName; }
	// Accessor for weaponAtk
	int getWeaponAtk() { return weaponAtk; }
	// Accessor for weaponHit
	int getWeaponHit() { return weaponHit; }
	// Accessor for weaponType
	WeaponType getWeaponType() { return weaponType; }
	// Accessor for damageType
	DamageType getDamageType() { return damageType; }
	// Accessor for strongType
	WeaponType getStrongType() { return strongType; }
	// Accessor for weakType
	WeaponType getWeakType() { return weakType; }

	// Mutator for weaponName
	void setWeaponName(std::string name) { weaponName = name; }
	// Mutator for weaponAtk
	void setWeaponAtk(int atk) { weaponAtk = atk; }
	// Mutator for weaponHit
	void setWeaponHit(int hit) { weaponHit = hit; }
	// Mutator for weaponType
	void setWeaponType(WeaponType wepType) { weaponType = wepType; }
	// Mutator for damageType
	void setDamageType(DamageType dmgType) { damageType = dmgType; }
	// Mutator for strongType
	void setStrongType(WeaponType strType) { strongType = strType; }
	// Mutator for weakType
	void setWeakType(WeaponType weakType) { weakType = weakType; }
	
};

#endif