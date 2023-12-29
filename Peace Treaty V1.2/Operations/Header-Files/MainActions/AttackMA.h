#ifndef ATTACKMA_H
#define ATTACKMA_H
#define ATTACK_MA

#include <iostream>
#include <string>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include PROVINCES_HEADER			
#include PRIME_UNITS_HEADER
#include COMMANDERS_HEADER
#include TROOPS_INT_HEADER
#include INPUT_HEADER
#include INF_HEADER

class AttackMA {
public:
	AttackMA(){}
	~AttackMA(){}

	virtual COMM::commSPTR pickCommanderAttack(COMM::commSPTRList commandersCanAttack) = 0;

	virtual void mainAttackMA(PROV::provSPTR, COMM::commSPTR attackingCommander) = 0;

	virtual void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP) = 0;

	virtual void playerCommitAttack(PROV::provSPTR defendingProvince, COMM::commSPTR attackingCommander) = 0;

	virtual void calculateTroopsLost(COMM::commSPTR commander, int lostCombatPower, constArrayReference troopsLost, int troopIndex) = 0;
	virtual void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex, COMM::commSPTR attackingCommander) = 0;
	virtual void casualtyReport(i5array troopsLost, i5array injuredTroops) = 0;

	virtual COMM::commSPTRList getCommandersCanAttack(PROV::provSPTR defendingProvince) = 0;
};

#endif