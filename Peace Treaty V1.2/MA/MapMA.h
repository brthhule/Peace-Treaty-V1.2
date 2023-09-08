#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>

#include "BuildMA.h"
#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"
#include "Mobility.h"

#include "../Units/Participants.h"
#include "../Units/Provinces.h"

#include "../Misc/ConstValues.h"
#include "../Misc/OtherFunctions.h"

extern std::vector<std::vector<Provinces>> provincesMap;
extern std::vector<Participants> participantsList;
using namespace CV;

class MapMA
{
public:
	//Constructors
	MapMA(Participants *newParticipant);

	void viewPlayerMap();

	void selectUnitOriginal(Provinces *selectedProvince);
	void selectPlayerProvince();
	void playerUnitAction(Provinces *newP);
	void playerUnitActionP(Provinces *newP);
	void selectEnemyAction();
	void selectEnemyProvince(Provinces *newP);

	void scoutLogFunction(Provinces* enemyProvince);
	void provinceReportLog(char whatReportChar, Provinces* enemyProvince);


  Participants *getParticipant();

private:
	Participants *participant;
	int pIndex;
	Provinces *prov;
	OtherFunctions OF;
};

#endif