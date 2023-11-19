#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\INF.h"

using namespace INF;

class Troops {
public:
	Troops(
		int level, 
		int baseHalth,
		int tier,
		std::array<int, 3> baseDamage, 
		INF::TroopTypes thisType);

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
	void getLevel();
	void resetLevel();
	void setTier(int num);
	void increaseTier(int amount);

	TroopTypes getThisType():


	void applyBoosts(int healthBoost, int damageBoost);
private:
	int level, tier, baseHealth, currentHealth;
	std::array<int, 3> baseDamage, currentDamage;
	INF::TroopTypes thisType;
	
};
#endif