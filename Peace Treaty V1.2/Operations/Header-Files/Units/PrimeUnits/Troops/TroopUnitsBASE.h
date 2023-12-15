/*Troops base class
* Composition: inside AllUnits.h
*/

#ifndef TROOPUNITSBASE_H
#define TROOPUNITSBASE_H

#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INF_HEADER

using namespace INF;

class TroopUnitsBASE {
public:

	/*	GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY*/
	enum TroopTypes {
		GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY
	};

	/*Constructor*/
	Troops(
		int level, 
		int baseHalth,
		int tier,
		std::array<int, 3> baseDamage, 
		TroopTypes thisType);

	int
		getLevel(),
		getCurrentHealth(),
		getTier();

	

	std::array<int,3> getCurrentDamage();

	/*DEFENSE,
		FIELD,
		ATTACK*/
	enum CombatTypes {
		DEFENSE = 0,
		FIELD = 1,
		ATTACK = 2
	};

	void updateHealth(int newHealth);
	void updateCurrentDamage();
	void resetStats();
	void resetLevel();
	void setTier(int num);
	void increaseTier(int amount);

	TroopTypes getThisType();


	void applyBoosts(int healthBoost, int damageBoost);

private:
	int level, tier, baseHealth, currentHealth;
	std::array<int, 3> baseDamage, currentDamage;
	TroopTypes thisType;
	
};
#endif