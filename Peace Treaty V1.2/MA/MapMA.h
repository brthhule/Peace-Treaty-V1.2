#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>


#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"


#include "../Units/Participants.h"
#include "../Units/Provinces.h"

#include "../Misc/ConstValues.h"
#include "../Misc/OF.h"
#include "../Units/Database.h"
#include "../Input.h"


//extern std::vector<std::vector<Provinces>> provincesMap;
//extern std::vector<Participants> participantsList;

extern Database db;

using namespace CV;

class MapMA
{
public:
	//Constructors
	MapMA();

	void 
		viewPlayerMap(),
		selectUnitOriginal(Provinces *selectedProvince),
		selectPlayerProvince(),
		
		playerUnitAction(Provinces *newP),
		playerUnitActionP(Provinces *newP),
		selectEnemyAction(),
		electEnemyProvince(Provinces *newP);

  Participants *getParticipant();

private:
	Participants *participant;
	int pIndex;
	Provinces *prov;
	
};

#endif