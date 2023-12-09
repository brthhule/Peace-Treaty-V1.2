//Interface implemented by Participants

#ifndef MOBILITY_H
#define MOBILITY_H
#define MOBILITY

#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include PROVINCES_HEADER

class Mobility {
public:
	void moveUnitOne(Commanders* commander) = 0;
	std::vector <Provinces*> moveUnitTwo(Commanders *commander) = 0;
};
#endif