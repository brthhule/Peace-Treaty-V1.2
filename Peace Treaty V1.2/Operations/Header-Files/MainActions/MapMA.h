#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include ATTACK_MA_HEADER
#include SCOUT_MA_HEADER
#include PROVINCES_HEADER
#include INPUT_HEADER
#include INF_HEADER
#include TRAIN_MA_HEADER

class MapMA {
public:
	MapMA(){}
	~MapMA(){}

	virtual void 
		viewPlayerMap() = 0,
		selectUnitOriginal(PROV::provSPTR selectedProvince) = 0,
		selectPlayerProvince(PROV::provSPTR province) = 0,
		
		playerUnitAction(PROV::provSPTR province) = 0,
		playerUnitActionP(PROV::provSPTR  province) = 0,
		selectEnemyAction() = 0,
		selectEnemyProvince(PROV::provSPTR  province) = 0;
};

#endif