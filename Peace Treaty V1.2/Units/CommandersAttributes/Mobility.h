#ifndef MOBILITY_H
#define MOBILITY_H

#include <vector>

#include "../Peace Treaty V1.2/Units/Provinces.h"

class Mobility {
public:
	void moveUnitOne(CommanderProfile* commander);
	std::vector <Provinces*> moveUnitTwo(CommanderProfile *commander);
};
#endif