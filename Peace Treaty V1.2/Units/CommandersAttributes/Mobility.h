#ifndef MOBILITY_H
#define MOBILITY_H

#include <vector>

#include "../Provinces.h"

class Mobility {
public:
	void moveUnitOne(Commanders* commander);
	std::vector <Provinces*> moveUnitTwo(Commanders *commander);
};
#endif