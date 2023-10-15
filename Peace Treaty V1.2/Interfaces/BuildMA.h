#ifndef BUILDMA_H
#define BUILDMA_H

class BuildMA
{
protected:
	//BuildMA() {};
	//~BuildMA() {};
	virtual void playerBuildFunction() = 0,
		upgradeBuildings() = 0,
		upgradeBuildings2(char buildingLetter, int buildingNumber, std::array<int, 5> requiredResources, std::vector<std::string> buildingLetterList) = 0,
		printInformation(int buildingNumber, std::array<int, 5> requiredResources, std::vector<std::string> buildingLetterList) = 0;
};

#endif