#ifndef MAPMA_H
#define MAPMA_H
#define MAP_MA

#include <iostream>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include SCOUT_MA_HEADER
#include ATTACK_MA_HEADER
#include TRAIN_MA_HEADER
#include INF_HEADER
#include INPUT_HEADER

using namespace INF;

class MapMA {
public:
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