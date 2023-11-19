#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>

#include "../Units/Commanders.h"
#include "../Units/Provinces.h"
#include "../Units/AllUnits.h"

#include "../Units/Misc/Input.h"
#include "../Units/Misc/INF.h"

using namespace INF;

class AttackMA
{
public:
	virtual Commanders* pickCommanderAttack(std::vector<Commanders*> commandersCanAttack) = 0;

	virtual void mainAttackMA(Provinces* defendingProvince, Commanders* attackingCommander) = 0;

	virtual void printResourcesGained() = 0;
	virtual void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP) = 0;

	virtual void playerCommitAttack(Provinces * defendingProvince, Commanders * attackingCommander) = 0;

	virtual void calculateTroopsLost(Commanders * commander, int lostCombatPower, std::array<int, 5> &troopsLost, int troopIndex) = 0;
	virtual void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex) = 0;
	virtual void casualtyReport(std::array<int, 5> troopsLost, std::array<int, 5> injuredTroops) = 0;

	virtual std::vector<Commanders*> getCommandersCanAttack(std::pair<int, int> defenderSystemCoords) = 0;
};

#endif