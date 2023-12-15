#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include ATTACK_MA_HEADER
#include INF_HEADER
#include INPUT_HEADER
#include SCOUT_MA_HEADER
#include TRAIN_MA_HEADER

using namespace INF;

class MapMA {
	COMPRISES_
		SCOUT_MA_
		ATTACK_MA_
		TRAIN_MA_
	USES_
		INF_
		INPUT_
public:
	MapMA(){}
	~MapMA(){}

	virtual void 
		viewPlayerMap() = 0,
		selectUnitOriginal(provSPTR selectedProvince) = 0,
		selectPlayerProvince(provSPTR province) = 0,
		
		playerUnitAction(provSPTR province) = 0,
		playerUnitActionP(provSPTR  province) = 0,
		selectEnemyAction() = 0,
		selectEnemyProvince(provSPTR  province) = 0;
};

#endif