#ifndef TRAINMA_H
#define TRAINMA_H

#include <iostream>
#include <iostream>
#include <vector>

#include "../Units/Provinces.h"
#include "../Units/Participants.h"
#include "../Units/Database.h"

#include "../Units/Misc/OF.h"
#include "../Units/Misc/Input.h"
#include "../Units/Misc/CV.h"


extern Database db;

using namespace CV;

class TrainMA
{
public:
	//constructor
	TrainMA();
	//other functions
	void TrainMAFunction();

	void TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops);

private:
	Provinces *province;
	
	Participants *participant;
};

#endif

