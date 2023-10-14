#ifndef TRAINMA_H
#define TRAINMA_H

#include <iostream>
#include <iostream>
#include <vector>

#include "../Units/Provinces.h"
#include "../Units/Participants.h"

#include "../Misc/OF.h"
#include "../Input.h"

#include "../Misc/ConstValues.h"

#include "../Units/Database.h"

extern Database db;

using namespace CV;

class TrainMA
{
public:
	//constructor
	TrainMA();
	//other functions
	void TrainMAFunction();
private:
	Provinces *province;
	
	Participants *participant;
};

#endif

