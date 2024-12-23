#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "..\..\..\Support\Paths.h"

#include PROVINCES_HEADER	
#include COMMANDERS_HEADER
#include INF_HEADER

using COMM::commSPTR; 

class AttackMA {
public:
	AttackMA(){}
	~AttackMA(){}

	virtual commSPTR pickCommanderAttack(COMM::commSPTRList commandersCanAttack) = 0;

	virtual void mainAttackMA(PROV::provSPTR, commSPTR attackingCommander) = 0;

	//First is attackerLostCP, second is defender
	virtual INF::ipair determineLostCP(int attackerCP, int defendingCP) = 0;

	virtual void playerCommitAttack(PROV::provSPTR defendingProvince, commSPTR attackingCommander) = 0;

	virtual void calculateTroopsLost(commSPTR commander, int lostCombatPower, INF::constArrayRef troopsLost, int troopIndex) = 0;
	virtual void battleCalculationsTwo(INF::constINT lostCombatPower, INF::i5array troopsLost, int troopIndex, commSPTR attackingCommander) = 0;
	virtual void casualtyReport(INF::constArrayRef troopsLost, INF::constArrayRef injuredTroops) = 0; 

	virtual COMM::commSPTRList getCommandersCanAttack(PROV::provSPTR defendingProvince) = 0;
};

#endif