
//ScoutMA.h
//Interface
//Implemented by Participants

#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"

#include PARTICIPANTS_HEADER
#include ALL_UNITS_HEADER
#include INPUT_HEADER
#include INF_HEADER

class ScoutMA {
public:

	typedef std::vector<Commanders*> commandersPtrsList;
	typedef std::vector<Provinces*> provincesPtrsList;
	//for null value, use scoutTypes nullValue ({}, {});
	typedef std::pair<commandersPtrsList, provincesPtrsList> scoutTypes;

	virtual void mainScoutMA (Provinces* provinceArg) = 0;
	virtual scoutTypes selectTarget(Provinces* targetProvince) = 0;

	// Functions
	virtual std::pair<AllUnits*, int> playerScoutStepTwo(scoutTypes canScout, Provinces* targetProvince) = 0;
	

	virtual AllUnits* selectUnitToScout(scoutTypes canScout) = 0;
	virtual AllUnits* selectUnitToScoutTwo(scoutTypes canScout) = 0;

	virtual scoutTypes getCanScout(Provinces* targetProvince) = 0;

	virtual void scoutLogCalculationsProvince(int accuracy) = 0;
	virtual void getCanScoutTwo(int targetX, int targetY, int a, int b, scoutTypes & canScout) = 0;

};

#endif