//ScoutMA.h
//Interface
//Implemented by Participants

#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"


#include "../Units/Misc/Input.h"
#include "../Units/Misc/INF.h"

class ScoutMA {
public:

	typedef std::vector<CommanderProfile*> commanderProfilePtrs;
	typedef std::vector<Provinces*> provincesPtrs;
	typedef std::pair<commanderProfilePtrs, provincesPtrs> scoutTypes;

	// Constructors
	void mainScoutMA (Participants* newParticipant, Provinces* newProvince) = 0;

	// Functions
	void playerScoutStepTwo(scoutTypes canScout) = 0;
	scoutTypes selectTarget() = 0,

	AllUnits
		*selectUnitToScout(scoutTypes canScout) = 0,
		*selectUnitToScoutTwo(scoutTypes canScout) = 0;

	scoutTypes getCanScout() = 0;

	void
		scoutLogCalculationsProvince(int accuracy) = 0,
		getCanScoutTwo(int targetX, int targetY, int a, int b, scoutTypes &canScout) = 0;

};

#endif