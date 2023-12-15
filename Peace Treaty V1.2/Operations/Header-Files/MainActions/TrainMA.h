//TrainMA.h

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#ifndef TRAINMA_H
#define TRAINMA_H

INTERFACE 
IMPLEMENTED_ BY_  
	PARTICIPANTS_ 
class TrainMA 
{
public:
	TrainMA(){}
	~TrainMA(){}

	virtual void TrainMAFunction() = 0;
	virtual void TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops) = 0;
};

#endif

