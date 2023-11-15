#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>

//Warning: may cause circular dependency
#include "../Units/Database.h"
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"
#include "../Units/Commanders.h"
#include "../Units/Provinces.h"
#include "../Units/AllUnits.h"

#include "../Units/Misc/Input.h"
#include "../Units/Misc/INF.h"



using namespace INF;

extern Database db;

class AttackMA
{
public:
	//constructor
	AttackMA(Provinces *defendingProvinceArg, Participants* attackingParticipantArg);
	AttackMA(Provinces* attackerProvinceArg, Provinces* defenderProvinceArg, Participants * attackingParticipantArg, CommanderProfile* commanderArg);

	void 
		findCommander (std::vector<CommanderProfile*> commandersCanAttack),
		printResourcesGained(),
		determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP),
		
		preAttack(),
		playerCommitAttack(),
		
		calculateTroopsLost(CommanderProfile* commander, int lostCombatPower, std::array<int,5> &troopsLost, int troopIndex),
		battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex),
		casualtyReport(std::array<int,5> troopsLost, std::array<int,5> injuredTroops);

	
private:
	Provinces 
		*attackingProvince, 
		*defendingProvince;

	//Player
	Participants* attackingParticipant;
	//Enemy
	Participants* defendingParticipant;


	CommanderProfile * attackingCommander;
	std::vector <CommanderProfile*> defendingCommanders;
	bool defenseCanRetreat;
	std::array<int,5> oldResources;
};

#endif