#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>


#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"


#include "../Units/Participants.h"
#include "../Units/Provinces.h"
#include "../Units/Database.h"

#include "../Units/Misc/INF.h"
#include "../Units/Misc/INF.h"
#include "../Units/Misc/Input.h"


//extern std::vector<std::vector<Provinces>> provincesMap;
//extern std::vector<Participants> participantsList;

extern Database db;

using namespace INF;

class MapMA
{
public:
	//Constructors
	MapMA();

	void 
		viewPlayerMap(),
		selectUnitOriginal(Provinces *selectedProvince),
		selectPlayerProvince(Provinces *province),
		
		playerUnitAction(Provinces *province),
		playerUnitActionP(Provinces * province),
		selectEnemyAction(),
		selectEnemyProvince(Provinces * province);

  Participants *getParticipant();

private:
	Participants *participant;
	int pIndex;
	
};

#endif