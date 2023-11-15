#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>


#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"

#include "../Units/Misc/INF.h"
#include "../Units/Misc/INF.h"
#include "../Units/Misc/Input.h"


//extern std::vector<std::vector<Provinces>> provincesMap;
//extern std::vector<Participants> participantsList;

using namespace INF;

class MapMA
{
public:
	void virtual
		viewPlayerMap() = 0,
		selectUnitOriginal(Provinces *selectedProvince) = 0,
		selectPlayerProvince(Provinces *province) = 0,
		
		playerUnitAction(Provinces *province) = 0,
		playerUnitActionP(Provinces * province) = 0,
		selectEnemyAction() = 0,
		selectEnemyProvince(Provinces * province) = 0;
};

#endif