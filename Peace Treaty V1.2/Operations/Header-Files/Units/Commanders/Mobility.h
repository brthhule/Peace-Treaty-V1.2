//Interface implemented by Participants

#ifndef MOBILITY_H
#define MOBILITY_H
#define MOBILITY

#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER
#incldue INPUT_HEADER

using namespace PROV;
using namespace COMM;
using namespace Input;

class Mobility {
public:
	//----Constructors---------------------------------------------------------
	Mobility(){}
	~Mobility(){}

	//----Methods--------------------------------------------------------------
	virtual void moveUnitOne(commSPTR commander) = 0;
	virtual std::vector <provSPTR> getSurroundingProvinces(commSPTR commander) = 0;
	virtual Provinces& pickProvinceToMoveTo(Commanders& commanderReference) = 0;
};
#endif