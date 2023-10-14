#ifndef MOBILITY_H
#define MOBILITY_H

#include <iostream>
#include <vector>

#include "AttackMA.h"

#include "../Input.h"

#include "../Units/Participants.h"
#include "../Units/Provinces.h"
#include "../Units/CommanderProfile.h"

#include "../Misc/ConstValues.h"
#include "../Misc/OF.h"

using namespace CV;

class Mobility
{
public:
	Mobility(std::string commanderName, Participants *newP);
	void moveUnitOne();
	std::vector <Provinces*> moveUnitTwo ();
private:
	CommanderProfile *selectedCommander;
	Participants* participant;
	Provinces* selectedCommanderProvince;
};

#endif