#ifndef ATTACKMA_H
#define ATTACKMA_H
#define ATTACK_MA

#include <iostream>
#include <string>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include COMMANDERS_HEADER
#include PROVINCES_HEADER
#include ALL_UNITS_HEADER
#include INPUT_HEADER
#include INF_HEADER

using namespace INF;

class AttackMA
{
public:
	using commSPTR = Commanders::commSPTR;
	using provSPTR = Provinces::provSPTR;
	virtual Commanders::commSPTR pickCommanderAttack(std::vector<commSPTR> commandersCanAttack) = 0;

	virtual void mainAttackMA(Provinces::provSPTR, commSPTR attackingCommander) = 0;

	virtual void printResourcesGained() = 0;
	virtual void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP) = 0;

	virtual void playerCommitAttack(provSPTR defendingProvince, commSPTR attackingCommander) = 0;

	virtual void calculateTroopsLost(commSPTR commander, int lostCombatPower, i5array &troopsLost, int troopIndex) = 0;
	virtual void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex) = 0;
	virtual void casualtyReport(i5array troopsLost, i5array injuredTroops) = 0;

	virtual std::vector<commSPTR> getCommandersCanAttack(Provinces::provSPTR defendingProvince) = 0;
};

#endif