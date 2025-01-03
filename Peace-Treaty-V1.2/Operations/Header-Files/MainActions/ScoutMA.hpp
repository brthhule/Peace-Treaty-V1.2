
//ScoutMA.h
//Interface
//Implemented by Participants

#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>
#include <memory>

#include "..\..\..\Support\Paths.h"

#include PROVINCES_HEADER	
#include PRIME_UNITS_HEADER

class ScoutMA {
public:
	ScoutMA() {}
	~ScoutMA() {}

	virtual void mainScoutMA(PROV::provSPTR provinceArg) = 0;
	virtual PROV::scoutTypes selectTarget(PROV::provSPTR targetProvince) = 0;

	// Functions
	virtual std::pair<UNIT::unitSPTR, int> playerScoutStepTwo(PROV::scoutTypes canScout, PROV::provSPTR targetProvince) = 0;


	virtual UNIT::unitSPTR selectUnitToScout(PROV::scoutTypes canScout) = 0;
	virtual UNIT::unitSPTR selectUnitToScoutTwo(PROV::scoutTypes canScout) = 0;

	virtual  PROV::scoutTypes getCanScout(PROV::provSPTR targetProvince) = 0;

	virtual void scoutLogCalculationsProvince(int accuracy) = 0;
	virtual void getCanScoutTwo(int targetX, int targetY, int a, int b, PROV::scoutTypes& canScout) = 0;

};
#endif