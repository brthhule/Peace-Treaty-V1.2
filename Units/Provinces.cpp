#include "Provinces.h"
//constructors
Provinces::Provinces()
{
	OF.debugFunction("Provinces, Provinces (1)");
	participantIndex = -1;
	basicStats();
}
Provinces::Provinces(int sendXCoordinate, int sendYCoordinate, int pIndex)
{
	OF.debugFunction("Provinces, Provinces (3)");
	//Initialize building levels
	for (int &x: resourceBuildingsLevels)
		x = 1;
	for (int &x: otherBuildingsLevels)
		x = 1;
	resourcesPresent = CV.INITIAL_VALUES;
	xCoord = sendXCoordinate;
	yCoord = sendYCoordinate;
	participantIndex = pIndex;
	basicStats();
}

Provinces::Provinces (int LLNumArg)
{
	OF.debugFunction("Provinces, Provinces (1)");
	linkedListNumber = LLNumArg;
	basicStats();
}

void Provinces::basicStats()
{
	OF.debugFunction("Provinces, basicStats");
	OF.modifyArray(resourcesPresent, CV.INITIAL_VALUES, true);
	
	scoutReportTurn = -1;
	scoutReportLogLevel = -1;
	
	unitLevel = 1;
	maxGarrison = getMaxGarrison();
	maxInfirmaryCapacity = getMaxInfirmaryCapacity();
	
  troopsTrainedThisTurn = 0;
  deleteProvince = false;
}


//Province stats

int Provinces::getMaxGarrison()
{
	OF.debugFunction("Provinces, getMaxGarrison");
	//Wall
	return *wallLevel * 10;
}
int Provinces::getMaxInfirmaryCapacity()
{
	OF.debugFunction("Provinces, getMaxInfirmaryCapacity");
	return *infirmaryLevel * 10;
}

int Provinces::findProvinceLevel()
{
	OF.debugFunction("Provinces, findProvinceLevel");
	unitLevel = 0;
	for (int x: resourceBuildingsLevels)
		unitLevel += resourceBuildingsLevels[x];
	for (int x: otherBuildingsLevels)
		unitLevel += x;
	
	unitLevel /= resourceBuildingsLevels.size() + otherBuildingsLevels.size();
	return unitLevel;
}

//Province stuff
void Provinces::updateProvinceResources()
{
	OF.debugFunction("Provinces, updateProvinceResources");
	for (int x = 0; x < resourceBuildingsLevels.size(); x++)
		resourcesPresent[x] += resourceBuildingsProduction[x];
}

//Other
void Provinces::setCoordinates(int xCoordinate, int yCoordinate)
{
	OF.debugFunction("Provinces, setCoordinates");
	xCoord = xCoordinate;
	yCoord = yCoordinate;
}
void Provinces::initializeCapital()
{
	OF.debugFunction("Provinces, initializeCapital");
	isACapital = true;
}
void Provinces::resetTroopsTrainedThisTurn()
{
	OF.debugFunction("Provinces, resetTroopsTrainedThisTurn");
	troopsTrainedThisTurn = 0;
}

//Building Stuff
void Provinces::increaseBuildingLevel(int index, int amount)
{
	OF.debugFunction("Provinces, increaseBuildingLevel");
	resourcesPresent[index] += amount;
}
void Provinces::printBuildingStats()
{
	OF.debugFunction("Provinces, printBuildingStats");
	for (int x = 0; x < 5; x++)
	{
		resourceBuildingsProduction[x] = resourceBuildingsLevels[x] * CV.INITIAL_VALUES[x];
	}
    std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << CV.RESOURCE_BUILDING_NAMES[x] << " (" << CV.RESOURCE_BUILDING_NAMES[x].at(0) << ") " << std::endl;
		std::cout << "    Level: " << resourceBuildingsLevels[x] << std::endl;
		std::cout << "    " << CV.RESOURCE_NAMES[x] << " production rate : " << resourceBuildingsProduction[x] << std::endl;
	}
	//Add implementation
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << otherBuildingsLevels[0] << std::endl;
	std::cout << "    Max training capacity: " << barracksCapacity << "\n\n\033[;0m";


}
//Fix this-- add distintion between resource buildings and other types
int Provinces::getBuildingLevel(int index)
{
	OF.debugFunction("Provinces, getBuildingLevel");
	return resourceBuildingsLevels[index];
}
void Provinces::updateBuildingsProduction()
{
	OF.debugFunction("Provinces, updateBuildingsProduction");
	for (int x = 0; x < 5; x++)
	{
		resourceBuildingsProduction[x] = resourceBuildingsLevels[x] * CV.RESOURCE_PRODUCTION[x];
	}
}

//Commander Stuff
void Provinces::removeCommander(CommanderProfile *newCommander)
{
	OF.debugFunction("Provinces, removeCommander");
	commanders.erase(newCommander->getUnitName());
}

void Provinces::addCommander(CommanderProfile* newCommander)
{
	OF.debugFunction("Provinces, addCommander");
  commanders[newCommander->getUnitName()] = newCommander;
}



void Provinces::addTroopsTrainedThisTurn(int amount)
{
	OF.debugFunction("Provinces, addTroopsTrainedThisTurn");
    troopsTrainedThisTurn += amount;
}

int Provinces::getCoordinate (char identifier)
{
	OF.debugFunction("Provinces, getCoordinate");
  switch (identifier)
  {
    case 'X':
      return xCoord;
    case 'Y':
      return yCoord;
    default:
      return -1;//in case something bad happen
  }
}



bool Provinces::deleteStatus()
{
	OF.debugFunction("Provinces, deleteStatus");
  return deleteProvince;
}

int Provinces::getTotalCP()
{
	OF.debugFunction("Provinces, getTotalCP");
	int totalCP = 0;
	totalCP += getCP();
	for (it = commanders.begin(); it != commanders.end(); it++)
		totalCP += it->second->getCP();
	return totalCP;
}

std::array<int,5> Provinces::getTotalResources()
{
	OF.debugFunction("Provinces, getTotalResources");
	std::array<int,5> totalResources = resourcesPresent;
  std::unordered_map<std::string, CommanderProfile*>::iterator it;
	for (it = commanders.begin(); it != commanders.end(); it++)
		for (int y = 0; y < 5; y++)
			totalResources[y] += it->second->getResource(y);
	
	return totalResources;
}

//Convert unordered_map to vector for easy understanding
std::vector <CommanderProfile*> Provinces::getAllCommanders()
{
	OF.debugFunction("Provinces, getAllCommanders");
		std::vector<CommanderProfile*> commandersList;
		std::unordered_map<std::string, CommanderProfile*>::iterator it;
		for (it = commanders.begin(); it != commanders.end(); it++)
			commandersList.push_back(it->second);
		return commandersList;
}

CommanderProfile* Provinces::getCommander(std::string name)
{
	OF.debugFunction("Provinces, getCommander");	
		return commanders[name];
}

bool Provinces::subtractCheckResources(std::array<int, 5> resourcesArray)
{
	OF.debugFunction("Provinces, subtractCheckResources");
	//returns false if resources dip into negatives
	modifyResources(resourcesArray, false);
	for (int x: resourcesPresent)
		if (x < 0)
			return false;
	return true;
}


void Provinces::completeProvinceScoutReport(int accuracy, Provinces* targetProvince, int scoutTurn)
{
	OF.debugFunction("Provinces, completeProvinceScoutReport");
	Provinces* t = targetProvince;
	/*Higher accuracy = more accurate scout log-- default is 50% accuracy (if
  there are 10 food resources in a province,
  the margin is 50%-- 5-15 units. 100 accuracy is the most accurate, 0 accuracy
  is the least accurate*/
	newAccuracy = (double)accuracy / 100;
	newAccuracy = (1 - newAccuracy)/2;//The most it will ever be off by is 50%

	//AllUnits info
	unitName = t->getUnitName();
	resourcesPresent = t->getAllResources();
	troopsPresent = t->getAllTroopsPresent();
	troopsInjured = t->getAllTroopsInjured();
	troopsLost = t->getAllTroopsLost();
	totalTroops = t->getTotalTroops();
	foodConsumption = t->getFoodConsumption();
	xCoord = t->getCoordinate('X');
	yCoord = t->getCoordinate('Y');
	participantIndex = t->getParticipantIndex();
	unitLevel = t->getLevel();
	unitName = t->getUnitName();
	CP = getEstimate(newAccuracy, t->getCP());

	maxGarrison = t->getMaxGarrison();
	maxInfirmaryCapacity = t->getMaxInfirmaryCapacity();
	resourceBuildingsLevels = t->getResourceBuildingLevels();
	resourceBuildingsProduction = t->getResourceBuildignsProduction();
	otherBuildingsLevels = t->getOtherBuildingsLevels();
	barracksCapacity = t->getBarracksCapacity();
	maxResources = t->getMaxResources();
	
	turn = scoutTurn;
	accuracy = accuracy;


}

int Provinces::getEstimate(int newAccuracy, int quantity)
{
	OF.debugFunction("Provinces, getEstimate");
	int margin = (int) (newAccuracy * quantity);
	int lowerBound = quantity - margin;
	int upperBound = quantity + margin;
	int scoutEstimate = rand() % lowerBound + upperBound;
	return scoutEstimate;
}

std::array<int,5> Provinces::getResourceBuildingLevels()
{
	OF.debugFunction("Provinces, getResourceBuildingLevels");
	return resourceBuildingsLevels;
}
std::array<int,5> Provinces::getResourceBuildignsProduction()
{
	OF.debugFunction("Provinces, getResourceBuildingsProduction");
	return resourceBuildingsProduction;
}
std::array<int,5> Provinces::getOtherBuildingsLevels()
{
	OF.debugFunction("Provinces, getOtherBuildingsLevels");
	return otherBuildingsLevels;
}
int Provinces::getBarracksCapacity()
{
	OF.debugFunction("Provinces, getBarracksCapacity");
	return *barracksLevel * 10;
}
std::array<int,5> Provinces::getMaxResources()
{
	OF.debugFunction("Provinces, getMaxResources");
	return maxResources;
}

void Provinces::printCommanders()
{
	OF.debugFunction("Provinces, printCommanders");
	for (it = commanders.begin(); it != commanders.end(); it++)
		std::cout << "- " << it->second->getUnitName();
}

bool Provinces::hasCommander(std::string name)
{
	OF.debugFunction("Provinces, hasCommander");
	for (it = commanders.begin(); it != commanders.end(); it++)
		if (it->second->getUnitName() == name)
			return true;
	return false;
}

int Provinces::getLinkedListNumber()
{
	OF.debugFunction("Provinces, getLinkedListNumber");
	return linkedListNumber;
}

void Provinces::assignLinkedListNumber (int number)
{
	OF.debugFunction("Provinces, assignLinkiedListNumber");
	linkedListNumber = number;
}

std::string Provinces::getLLCoordinates ()
{
	OF.debugFunction("Provinces, getLLCoordinates");
	int x = linkedListNumber % 5;
	int y = 5 - (int)(linkedListNumber / 5);
	std::string coordinatesString = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	return coordinatesString;
}