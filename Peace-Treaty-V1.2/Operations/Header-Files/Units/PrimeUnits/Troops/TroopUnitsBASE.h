/*Troops base class
* Composition: inside PrimeUnits.h
*/

#ifndef TROOPUNITSBASE_H
#define TROOPUNITSBASE_H

#include <iostream>
#include "..\..\..\..\..\Support\Paths.h"

#include TROOP_HEADER
#include INF_HEADER
 
class TroopUnitsBASE { 
public:

	

	//----Constructors---------------------------------------------------------
	TroopUnitsBASE();
	TroopUnitsBASE(
		int level, 
		int baseHalth,
		int tier,
		std::array<int, 3> baseDamage, 
		TROOP::TroopTypes thisType);
	~TroopUnitsBASE(){}

	//----Getters--------------------------------------------------------------
	INF::constINT
		getLevel() const,
		getCurrentHealth() const,
		getTier() const;

	const std::array<int,3>& getCurrentDamage();
	TROOP::TroopTypes getThisType() const;
	
	//----Mutators-------------------------------------------------------------
	void updateHealth(int newHealth);
	void updateCurrentDamage();
	void increaseTier(int amount);
	void applyBoosts(int healthBoost, int damageBoost);

	//----Setters--------------------------------------------------------------
	void resetStats();
	void resetLevel();
	void setTier(int num);


private:
	int level, tier, baseHealth, currentHealth;
	std::array<int, 3> baseDamage, currentDamage;
	TROOP::TroopTypes thisType;
	
};

using oneTier = std::vector<TroopUnitsBASE>;
using tiersArray = std::array<oneTier, 5>;
using troopsArray = std::array<tiersArray, 5>;

/*
#define oneTier = std::vector<TroopUnitsBASE>;
#define tiersArray = std::array<std::vector<TroopUnitsBASE>, 5>;
using troopsArray = std::array<std::array<std::vector<TroopUnitsBASE>, 5>, 5>;
*/
#endif