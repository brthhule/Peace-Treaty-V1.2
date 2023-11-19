#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\INF.h"

using namespace INF;

class Troops {
public:
	Troops(int level, int baseHalth, std::array<int, 3> baseDamage);

	int
		getLevel(),
		getHealth(),
		getDamage();

	/*DEFENSE,
		FIELD,
		ATTACK*/
	enum CombatTypes {
		DEFENSE = 0,
		FIELD = 1,
		ATTACK = 2
	};

	void applyBoosts(int healthBoost, int damageBoost);
private:
	int level, baseHealth, currentHealth, currentDamage;
	std::array<int, 3> baseDamage;
	
};
#endif