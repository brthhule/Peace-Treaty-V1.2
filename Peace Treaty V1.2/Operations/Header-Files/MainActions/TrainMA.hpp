//TrainMA.h

#ifndef TRAINMA_H
#define TRAINMA_H

#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

class TrainMA 
{
public:
	//----Constructors---------------------------------------------------------
	TrainMA(){}
	~TrainMA(){}

	//----Methods--------------------------------------------------------------
	virtual void trainMAMain() = 0;
	virtual void trainMALoop(int troopTier, int amountOfTroops) = 0;
};

#endif

