#ifndef MOBILITY_H
#define MOBILITY_H

#include <vector>

#include "../Provinces.h"

class Mobility {
public:
	void moveUnitOne(CommanderProfile* commander);
	std::vector <Provinces*> moveUnitTwo(CommanderProfile *commander);
};
#endif