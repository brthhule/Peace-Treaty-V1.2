//TrainMA.h
//Interface
//Implemented by Participants.h

#ifndef TRAINMA_H
#define TRAINMA_H

#include <iostream>
#include <iostream>
#include <vector>

#include "../Units/Provinces.h"
#include "../Units/Participants.h"
#include "../Units/Database.h"

#include "../Units/Misc/INF.h"
#include "../Units/Misc/Input.h"
#include "../Units/Misc/INF.h"

using namespace INF;

class TrainMA
{
public:
	virtual void 
		TrainMAFunction() = 0,
		TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops) = 0;
};

#endif

