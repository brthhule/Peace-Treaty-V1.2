#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>

#include "../Units/Participants.h"
#include "../Units/Provinces.h"
#include "../Input.h"


#include "../Misc/OF.h"

class ScoutMA {
public:
  // Constructors
  ScoutMA(Participants *newParticipant, Provinces *newProvince);

  // Functions
  void selectTarget();
  void playerScoutStepTwo();
  int selectUnitToScout(std::string &unitName, bool &isProvince, std::array<int, 2> &coordinates);
  int selectUnitToScoutTwo(std::string &unitName, bool &isProvince, std::array<int, 2> &coordinates);
  void scoutLogCalculationsProvince(int accuracy);
	void getCanScout();
  void getCanScoutTwo(int targetX, int targetY, int a, int b);
	bool checkHasUnit (std::string unitName);

private:
  std::vector<CommanderProfile*> commandersCanScout;
  std::vector<Provinces *> provincesCanScout;
  std::vector<int> unitLevels;

  int targetInformation[2]; //[0] is for whether it is a province (1) or
                            //commander (2); [1] is the index of the unit in its
                            //Participants object
  int enemyLevel;
  Participants *participant;
	Participants* targetParticipant;

  Provinces *yourProvince;
	Provinces* targetProvince;
	
};

#endif