#include "..\..\..\..\..\Support\Paths.h"
#include TROOP_UNITS_BASE_HEADER 

using namespace INF;
using namespace TROOP;

TroopUnitsBASE::TroopUnitsBASE() : TroopUnitsBASE(0, 0, 0, {0,0,0}, GUARDS) {

}
TroopUnitsBASE::TroopUnitsBASE(int level,
	int baseHealth,
	int tier,
	std::array<int,3> baseDamage,
	TROOP::TroopTypes thisType) {
	//For debugging
	DEBUG_FUNCTION("TroopUnitsBASE.cpp", "Troops");

	//Every battle increases level. At 10 levels, increase tier and reset levels
	this->level = level;
	this->currentHealth = 0;//Check this out???
	this->baseHealth = baseHealth + (5 * (tier - 1));
	this->tier = tier;
	this->thisType = thisType;

	for (int x = 0; x < 3; x++) {
		this->baseDamage.at(x) = baseDamage.at(x) + (1 * (tier - 1));
		this->currentDamage.at(x) = baseDamage.at(x) + (1 * (tier - 1));
	}
}


void TroopUnitsBASE::applyBoosts(int healthBoost, int damageBoost) {
	this->baseHealth += healthBoost;
	for (int x : baseDamage) {
		x += damageBoost;
	}
}

constINT TroopUnitsBASE::getLevel() const{
	return level;
}

constINT TroopUnitsBASE::getCurrentHealth() const {
	return currentHealth;
}

const std::array<int, 3>& TroopUnitsBASE::getCurrentDamage() { 
	return currentDamage;
}

void TroopUnitsBASE::updateHealth(int newHealth) {
	currentHealth = newHealth;
}

//Current damage is proportional to current health / base health
void TroopUnitsBASE::updateCurrentDamage() {
	for (int x = 0; x < 3; x++) {
		currentDamage.at(x) = baseDamage.at(x) * (currentHealth / baseHealth);
	}
}

void TroopUnitsBASE::resetStats() {
	currentHealth = baseHealth;
	for (int x = 0; x < 3; x++) {
		currentDamage.at(x) = baseDamage.at(x);
	}
}

void TroopUnitsBASE::resetLevel() {
	level = 0;
}

void TroopUnitsBASE::setTier(int num) {
	tier = num;
}

void TroopUnitsBASE::increaseTier(int amount) {
	tier += amount;
}

TROOP::TroopTypes TroopUnitsBASE::getThisType() const {
	return thisType;
}

constINT TroopUnitsBASE::getTier() const{
	return tier;
}