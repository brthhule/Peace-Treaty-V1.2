#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include SCOUT_MA_HEADER
#include ATTACK_MA_HEADER
#include TRAIN_MA_HEADER
#include INF_HEADER
#include INPUT_HEADER


//extern std::vector<std::vector<Provinces>> provincesMap;
//extern std::vector<Participants> participantsList;

using namespace INF;

class MapMA
{
public:
	virtual void
		viewPlayerMap() = 0,
		selectUnitOriginal(Provinces *selectedProvince) = 0,
		selectPlayerProvince(Provinces *province) = 0,
		
		playerUnitAction(Provinces *province) = 0,
		playerUnitActionP(Provinces * province) = 0,
		selectEnemyAction() = 0,
		selectEnemyProvince(Provinces * province) = 0;
};

#endif