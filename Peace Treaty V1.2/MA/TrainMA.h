#ifndef TRAINMA_H
#define TRAINMA_H

#include <iostream>
#include <iostream>
#include <vector>

#include "../Units/Provinces.h"
#include "../Units/Participants.h"

#include "../Misc/OF.h"
#include "../Misc/ConstValues.h"

#include "../Units/Database.h"

extern std::vector <std::vector <Provinces>> provincesMap;
extern std::vector <Participants> participantsList;

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

