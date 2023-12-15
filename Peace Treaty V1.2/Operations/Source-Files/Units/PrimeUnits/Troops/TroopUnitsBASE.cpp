#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include TROOPS_HEADER

Troops::Troops(int level, 
	int baseHealth,
	int tier,
	std::array<int,3> baseDamage,
	TroopTypes thisType) {
	//For debugging
	INF::debugFunction("Troops, Troops");

	//Every battle increases level. At 10 levels, increase tier and reset levels
	this->level = level;

	this->baseHealth = baseHealth + (5 * (tier - 1));

	this->thisType = thisType;

	for (int x = 0; x < 3; x++) {
		this->baseDamage.at(x) = baseDamage.at(x) + (1 * (tier - 1));
		this->currentDamage.at(x) = baseDamage.at(x) + (1 * (tier - 1));
	}
}


void Troops::applyBoosts(int healthBoost, int damageBoost) {
	this->baseHealth += healthBoost;
	for (int x : baseDamage) {
		x += damageBoost;
	}
}

int Troops::getLevel() {
	return level;
}

int Troops::getCurrentHealth() {
	return currentHealth;
}

std::array<int, 3> Troops::getCurrentDamage() {
	return currentDamage;
}

void Troops::updateHealth(int newHealth) {
	currentHealth = newHealth;
}

//Current damage is proportional to current health / base health
void Troops::updateCurrentDamage() {
	for (int x = 0; x < 3; x++) {
		currentDamage.at(x) = baseDamage.at(x) * (currentHealth / baseHealth);
	}
}

void Troops::resetStats() {
	currentHealth = baseHealth;
	for (int x = 0; x < 3; x++) {
		currentDamage.at(x) = baseDamage.at(x);
	}
}

void Troops::resetLevel() {
	level = 0;
}

void Troops::setTier(int num) {
	tier = num;
}

void Troops::increaseTier(int amount) {
	tier += amount;
}

Troops::TroopTypes Troops::getThisType() {
	return thisType;
}

int Troops::getTier() {
	return tier;
}