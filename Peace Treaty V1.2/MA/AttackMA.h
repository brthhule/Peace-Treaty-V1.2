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
	//constructor
	AttackMA(Provinces *defendingProvinceArg, Participants* attackingParticipantArg);
	AttackMA(Provinces* attackerProvinceArg, Provinces* defenderProvinceArg, Participants * attackingParticipantArg, Commanders* commanderArg);

	Commanders* pickCommanderAttack(std::vector<Commanders*> commandersCanAttack) = 0;
	void virtual
		mainAttackMA(Provinces* defendingProvince, Commanders* attackingCommander) = 0,
		
		printResourcesGained(),
		determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP),
		
		playerCommitAttack(Provinces* defendingProvince,  Commanders* attackingCommander),
		
		calculateTroopsLost(Commanders* commander, int lostCombatPower, std::array<int,5> &troopsLost, int troopIndex),
		battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex),
		casualtyReport(std::array<int,5> troopsLost, std::array<int,5> injuredTroops);

	virtual std::vector<Commanders*> getCommandersCanAttack(std::pair<int, int> defenderSystemCoords) = 0;
private:
	Provinces 
		*attackingProvince, 
		*defendingProvince;

	//Player
	Participants* attackingParticipant;
	//Enemy
	Participants* defendingParticipant;


	Commanders * attackingCommander;
	std::vector <Commanders*> defendingCommanders;
	bool defenseCanRetreat;
	std::array<int,5> oldResources;
};

#endif