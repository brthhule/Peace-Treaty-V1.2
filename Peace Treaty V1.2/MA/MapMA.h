#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>


#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"
#include "Mobility.h"

#include "../Units/Participants.h"
#include "../Units/Provinces.h"

#include "../Misc/ConstValues.h"
#include "../Misc/OF.h"
#include "../Units/Database.h"
#include "../Input.h"


//extern std::vector<std::vector<Provinces>> provincesMap;
//extern std::vector<Participants> participantsList;

extern Database db;

using namespace CV;

class MapMA
{
public:
	//Constructors
	MapMA();

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
	
};

#endif