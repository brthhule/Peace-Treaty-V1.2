/*Troops base class
* Composition: inside PrimeUnits.h
*/

#ifndef TROOPUNITSBASE_H
#define TROOPUNITSBASE_H

#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER
#include TROOP_HEADER

using namespace INF;
using namespace TROOP;
 
class TroopUnitsBASE { 
public:

	

	//----Constructors---------------------------------------------------------
	TroopUnitsBASE(){}
	TroopUnitsBASE(
		int level, 
		int baseHalth,
		int tier,
		std::array<int, 3> baseDamage, 
		TroopTypes thisType);
	~TroopUnitsBASE(){}

	//----Getters--------------------------------------------------------------
	constINT
		getLevel(),
		getCurrentHealth(),
		getTier();

	const std::array<int,3>& getCurrentDamage();
	TroopTypes getThisType();
	
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

using oneTier = std::vector<TroopUnitsBASE>;
using tiersArray = Array5<oneTier>;
using troopsArray = Array5 <tiersArray>;

#endif