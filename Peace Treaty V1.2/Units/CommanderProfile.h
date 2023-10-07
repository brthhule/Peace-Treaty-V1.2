#ifndef COMMANDERPROFILE_H
#define COMMANDERPROFILE_H

#include <vector>

#include "AllUnits.h"
#include "../Misc/ConstValues.h"

using namespace CV;


class CommanderProfile : public AllUnits {
public:
  // Constructors
  CommanderProfile();
  CommanderProfile(int commanderLevel, std::string name);
  // Destructor
  ~CommanderProfile();

  // Accessor functions

  // Stats stuff
  int getCommanderStat(int index);
  void printCommanderStats();
  void setLocation(std::array<int, 2> pCoords);

  // Scout report stuff
  void updateCommanderScoutReport(int index, int value);
  void completeCommanderScoutReport(int accuracy);
  int printCommanderScoutReport(int idex);

  // Other commander stuff
  void addLevel(){unitLevel++;} // addCommanderLevel
  std::array<int, 5> getUpgradeCosts();
  void printCosts(std::array<int, 5> costs);

  void setDelete() { deleteCommander = true; }
  bool getDelete() { return deleteCommander; }

  // Moving
  bool hasMovedQuestion(){return hasMoved;}
  void resetCommanderMoved(){hasMoved = false;}

	//Scout stuff: 
	void calculateCommanderScoutLog();


private:
	int *commanderArrays [4][5];
	int *otherCommanderStats[6];
  int commanderScoutReport[22]; /*
[0] = food the army possesses    Resources
[1]  = wood
[2] = ore
[3] = gold
[4] = mana
[5] = militia present            Troops Present
[6] = guards present
[7] = cavalry present
[8] = knights present
[9]  = paladins present
[10] = militia injured            Troops Injured
[11] = guards injured
[12] = cavalry injured
[13] = knights injured
[14] = paladins injured
[15] = total troops               Miscellaneous stats
[16] = totalCP
[17] = leaderLevel
[18] = maxTroops
[19] = food consumption
[20] = turn number of scout report
[21] = accuracy of scout report*/
  int maxTroops;                // check
  int totalMaxResources;
  bool hasMoved;

  std::string MANDescriptions[5] = {"Resources in", "Troops present in", "Troops injured in", "Troops lost in", "Other stats of"}; // check
  std::string namesOfMANOne[4][5];  
	std::string namesOfManTwo[6];
	// check
  int costToUpgrade [5] = {5, 4, 3, 2, 1};
  int commanderIndex;
  bool deleteCommander;
};

#endif