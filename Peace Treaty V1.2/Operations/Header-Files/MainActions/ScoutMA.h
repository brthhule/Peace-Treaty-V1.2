
//ScoutMA.h
//Interface
//Implemented by Participants

#ifndef SCOUTMA_H
#define SCOUTMA_H
#define SCOUT_MA

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include PRIME_UNITS_HEADER
#include INF_HEADER
#include INPUT_HEADER
#include PARTICIPANTS_HEADER

class ScoutMA {
	COMPRISES_
		ALL_UNITS_
		PARTICIPANTS_
	USES_
		INF_
		INPUT_
public:
	ScoutMA(){}
	~ScoutMA(){}
	//for null value, use scoutTypes nullValue ({}, {});
	using scoutTypes = std::pair<COMM::commSPTRList, PROV::provSPTRList>;

	virtual void mainScoutMA (provSPTR provinceArg) = 0;
	virtual scoutTypes selectTarget(provSPTR targetProvince) = 0;

	// Functions
	virtual std::pair<UNIT::unitSPTR, int> playerScoutStepTwo(scoutTypes canScout, provSPTR targetProvince) = 0;
	

	virtual UNIT::unitSPTR selectUnitToScout(scoutTypes canScout) = 0;
	virtual UNIT::unitSPTR selectUnitToScoutTwo(scoutTypes canScout) = 0;

	virtual scoutTypes getCanScout(provSPTR targetProvince) = 0;

	virtual void scoutLogCalculationsProvince(int accuracy) = 0;
	virtual void getCanScoutTwo(int targetX, int targetY, int a, int b, scoutTypes & canScout) = 0;

};

#endif