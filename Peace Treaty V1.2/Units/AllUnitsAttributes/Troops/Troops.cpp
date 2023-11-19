#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\AllUnitsAttributes\Troops\Troops.h"

Troops::Troops(int level, int baseHealth, std::array<int,3> baseDamage) {
	//For debugging
	INF::debugFunction("Troops, Troops");

	this->level = level;

	this->baseHealth = baseHealth + (5 * (level - 1));

	for (int x = 0; x < 3; x++) {
		this->baseDamage.at(x) = baseDamage.at(x) + (1 * (level - 1));
	}
}


void Troops::applyBoosts(int healthBoost, int damageBoost) {
	this->baseHealth += healthBoost;
	for (int x : baseDamage) {
		x += damageBoost;
	}
}