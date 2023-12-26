/*Troops base class
* Composition: inside PrimeUnits.h
*/

#ifndef TROOPUNITSBASE_H
#define TROOPUNITSBASE_H

#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include TROOP_HEADER
/*	#include INF_HEADER*/

using namespace INF;
using namespace TROOP;
 
class TroopUnitsBASE { 
public:

	

	//----Constructors---------------------------------------------------------
	TroopUnitsBASE();
	TroopUnitsBASE(
		int level, 
		int baseHalth,
		int tier,
		std::array<int, 3> baseDamage, 
		TroopTypes thisType);
	~TroopUnitsBASE(){}

	//----Getters--------------------------------------------------------------
	constINT
		getLevel() const,
		getCurrentHealth() const,
		getTier() const;

	const std::array<int,3>& getCurrentDamage();
	TroopTypes getThisType() const;
	
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
	TroopTypes thisType;
	
};

/*using oneTier = std::vector<TroopUnitsBASE>;
using tiersArray = Array5(oneTier);
using troopsArray = Array5(tiersArray);*/

#define oneTier = std::vector<TroopUnitsBASE>;
#define tiersArray = std::array<std::vector<TroopUnitsBASE>, 5>;
using troopsArray = std::array<std::array<std::vector<TroopUnitsBASE>, 5>, 5>;

#endif