//Interface implemented by Participants

#ifndef MOBILITY_H
#define MOBILITY_H
#define MOBILITY

#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Misc\Main_FilePaths.h"
#include PROVINCES_HEADER

class Mobility {
public:
	using commSPTR = Commanders::commSPTR;
	using provSPTR = Provinces::provSPTR;

	virtual void moveUnitOne(commSPTR commander) = 0;
	virtual std::vector <provSPTR> moveUnitTwo(commSPTR commander) = 0;
};
#endif