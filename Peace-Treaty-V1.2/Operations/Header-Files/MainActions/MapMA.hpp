#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>

#include "C:\Users\Darren Zheng\source\repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
#include <memory>

#include PROVINCES_HEADER

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