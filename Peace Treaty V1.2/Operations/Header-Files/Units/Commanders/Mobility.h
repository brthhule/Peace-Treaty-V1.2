//Interface implemented by Participants

#ifndef MOBILITY_H
#define MOBILITY_H
#define MOBILITY

#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER
#include INPUT_HEADER
#include COMMANDERS_HEADER

class Mobility {
public:
	//----Constructors---------------------------------------------------------
	Mobility(){}
	~Mobility(){}

	//----Methods--------------------------------------------------------------
	virtual void moveUnitOne(COMM::commSPTR commander) = 0;
	virtual std::vector <PROV::provSPTR> getSurroundingProvinces(COMM::commSPTR commander) = 0;
	virtual PROV::Provinces& pickProvinceToMoveTo(COMM::Commanders& commanderReference) = 0;
};
#endif