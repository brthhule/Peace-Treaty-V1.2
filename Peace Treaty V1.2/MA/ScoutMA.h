#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>

#include "../Units/Participants.h"
#include "../Units/Provinces.h"
#include "../Input.h"


#include "../Misc/OF.h"

class ScoutMA {
public:
	// Constructors
	ScoutMA(Participants* newParticipant, Provinces* newProvince);

	// Functions
	void
		selectTarget(),
		playerScoutStepTwo();

	int
		selectUnitToScout(std::string& unitName, bool& isProvince, std::pair<int, int>& coordinates),
		selectUnitToScoutTwo(std::string unitName, bool isProvince, std::pair<int, int> coordinates);

	void
		scoutLogCalculationsProvince(int accuracy),
		getCanScout(),
		getCanScoutTwo(int targetX, int targetY, int a, int b);

	bool checkHasUnit(std::string unitName);

private:
	std::vector<CommanderProfile*> commandersCanScout;
	std::vector<Provinces*> provincesCanScout;
	std::vector<int> unitLevels;

	int targetInformation[2]; //[0] is for whether it is a province (1) or
	//commander (2); [1] is the index of the unit in its
	//Participants object

	int enemyLevel;
	Participants
		*participant,
		*targetParticipant;

	Provinces
		*yourProvince,
		*targetProvince;

};

#endif