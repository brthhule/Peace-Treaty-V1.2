#ifndef BUILDMA_H
#define BUILDMA_H

#include <iostream>
#include <vector>
#include <string>

#include "../Units/Provinces.h"
#include "../Units/Participants.h"
#include "../Units/AllUnits.h"

#include "../Misc/OtherFunctions.h"
#include "../Misc/ConstValues.h"

extern std::vector<Participants> participantsList;
extern int continentSize;
using namespace CV;

class BuildMA
{
public:
	//Constructors
	BuildMA();
	BuildMA(Provinces *newProvince, Participants *newParticipant);

	//Accessors/Functions?
	Provinces* findProvince();
	void playerBuildFunction();
	void upgradeBuildings();

	void printInformation (int buildingNumber, std::array<int, 5> requiredResources);
private:
	Provinces *province;
	Participants* participant;
	double requiredResourcesBuildings[6][5] = { {1, 0.5, 0.25, 0.125, 0.0625}, {2, 1, 0.5, 0.25, 0.125}, {3, 2, 1, 0.5, 0.25}, {4, 3, 2, 1, 0.5}, {5, 4, 3, 2, 1}, {1, 1, 1, 1, 0.2} }; /*double requiredResourcesFarm [5] = {1, 0.5, 0.25, 0.125, 0.0625};
	double requiredResourcesLumberMill [5] = {2, 1, 0.5, 0.25, 0.125};
	double requiredResourcesQuarry [5] = {3, 2, 1, 0.5, 0.25};
	double requiredResourcesMine [5] = {4, 3, 2, 1, 0.5};
	double requiredResourcesChurch [5] = {5, 4, 3, 2, 1};
	double requiredResourcesBarracks [5] = {1, 1, 1, 1, 0.2};*/
	OtherFunctions OF;
};

#endif