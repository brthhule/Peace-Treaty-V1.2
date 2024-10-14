//Interface implemented by Participants

#ifndef MOBILITY_H
#define MOBILITY_H

#include <vector>
#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
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
	virtual PROV::provSPTRList getSurroundingProvinces(Commanders& commander_ref) = 0;
	virtual Provinces &pickProvinceToMoveTo(Commanders& commanderReference) = 0;
};
#endif