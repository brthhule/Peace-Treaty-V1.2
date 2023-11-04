#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>

#include "../Units/Participants.h"
#include "../Units/Provinces.h"
#include "../Units/AllUnits.h"
#include "../Input.h"


#include "../Misc/OF.h"

class ScoutMA {
public:

	typedef std::vector<CommanderProfile*> commanderProfilePtrs;
	typedef std::vector<Provinces*> provincesPtrs;
	typedef std::pair<commanderProfilePtrs, provincesPtrs> scoutTypes;

	// Constructors
	ScoutMA(Participants* newParticipant, Provinces* newProvince);

	// Functions
	void
		selectTarget(),
		playerScoutStepTwo(scoutTypes canScout);

	AllUnits
		*selectUnitToScout(scoutTypes canScout),
		*selectUnitToScoutTwo(scoutTypes canScout);

	

	scoutTypes getCanScout();

	void
		scoutLogCalculationsProvince(int accuracy),
		getCanScoutTwo(int targetX, int targetY, int a, int b, scoutTypes &canScout);


private:
	std::vector<int> unitLevels;

	enum TargetTypes {PROVINCE, COMMANDER};

	/* [0] is for whether it is a province(1) or
	commander (2); [1] is the index of the unit in its
	Participants object*/
	std::pair<std::pair<TargetTypes, TargetTypes>, int> targetInformation;

	int enemyLevel;
	Participants
		*participant,
		*targetParticipant;

	Provinces
		*yourProvince,
		*targetProvince;

};

#endif