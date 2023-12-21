#ifndef ATTACKMA_H
#define ATTACKMA_H
#define ATTACK_MA

#include <iostream>
#include <string>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include PRIME_UNITS_HEADER				//Composition
#include COMMANDERS_HEADER				//Composition
#include INF_HEADER						//Utility
#include INPUT_HEADER					//Utility
#include PROVINCES_HEADER				//Composition
#include TROOPS_INT_HEADER				//Composition
 
using namespace INF;
using namespace PROV;
using namespace COMM;
using namespace TROOP;

class AttackMA {
public:
	AttackMA(){}
	~AttackMA(){}

	virtual commSPTR pickCommanderAttack(std::vector<commSPTR> commandersCanAttack) = 0;

	virtual void mainAttackMA(provSPTR, commSPTR attackingCommander) = 0;

	virtual void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP) = 0;

	virtual void playerCommitAttack(provSPTR defendingProvince, commSPTR attackingCommander) = 0;

	virtual void calculateTroopsLost(commSPTR commander, int lostCombatPower, i5array &troopsLost, int troopIndex) = 0;
	virtual void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex, commSPTR attackingCommander) = 0;
	virtual void casualtyReport(i5array troopsLost, i5array injuredTroops) = 0;

	virtual std::vector<commSPTR> getCommandersCanAttack(provSPTR defendingProvince) = 0;
};

#endif