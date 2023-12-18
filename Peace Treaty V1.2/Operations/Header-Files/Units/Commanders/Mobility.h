//Interface implemented by Participants

#ifndef MOBILITY_H
#define MOBILITY_H
#define MOBILITY

#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER

using namespace PROV;
using namespace COMM;

class Mobility {
public:
	//----Constructors---------------------------------------------------------
	Mobility(){}
	~Mobility(){}

	//----Methods--------------------------------------------------------------
	virtual void moveUnitOne(commSPTR commander) = 0;
	virtual std::vector <provSPTR> moveUnitTwo(commSPTR commander) = 0;
};
#endif